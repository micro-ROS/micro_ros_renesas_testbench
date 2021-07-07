#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <micro_ros_utilities/string_utilities.h>
#include <micro_ros_utilities/type_utilities.h>

#include <sensor_msgs/msg/camera_info.h>

void microros_app(void);

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create nodes
	rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	rclc_node_init_with_options(&node, "test_node", "", &support, &node_ops);

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CameraInfo),
        "test_pub");


    sensor_msgs__msg__CameraInfo msg;

    micro_ros_utilities_memory_conf_t conf = {0};
    micro_ros_utilities_memory_rule_t rules[] = {
        {"d", 30},
    };

    conf.rules = rules;
    conf.n_rules = sizeof(rules) / sizeof(rules[0]);

    static uint8_t static_buffer[2000];
    micro_ros_utilities_create_static_message_memory(
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CameraInfo),
        &msg,
        conf,
        static_buffer,
        sizeof(static_buffer)
    );

    msg.distortion_model = micro_ros_string_utilities_set(msg.distortion_model, "string_1");
    msg.header.frame_id = micro_ros_string_utilities_set(msg.header.frame_id, "string_2");

    for(size_t i = 0; i < msg.d.capacity; i++){
        msg.d.data[i] = i;
        msg.d.size++;
    }

    for(;;){
        rcl_publish(&publisher, &msg, NULL);
        sleep_ms(1000);
    }
}
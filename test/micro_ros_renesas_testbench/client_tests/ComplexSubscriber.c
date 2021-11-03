#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <micro_ros_utilities/string_utilities.h>
#include <micro_ros_utilities/type_utilities.h>

#include <sensor_msgs/msg/camera_info.h>
#include <std_msgs/msg/float64.h>

void microros_app(void);
void subscription_callback(const void * msgin);

rcl_publisher_t publisher;

void subscription_callback(const void * msgin)
{
    const sensor_msgs__msg__CameraInfo * msg = (const sensor_msgs__msg__CameraInfo *)msgin;

    bool check = true;

    check &= 0 == strcmp(msg->distortion_model.data, "string_1");
    check &= 0 == strcmp(msg->header.frame_id.data, "string_2");
    check &= 200 == msg->d.size;

    if(check){
        std_msgs__msg__Float64 out_msg;
        out_msg.data = 0;
        for(size_t i = 0; i < msg->d.size; i++){
           out_msg.data += msg->d.data[i];
        }
        rcl_publish(&publisher, &out_msg, NULL);
    }
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;

    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    rcl_init_options_init(&init_options, allocator);
    rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
    rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // create node
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

    // create publisher
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
        "test_aux_pub");

    // create subscriber
    rcl_subscription_t subscriber;
    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CameraInfo),
        "test_sub");

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    sensor_msgs__msg__CameraInfo msg;

    micro_ros_utilities_memory_conf_t conf = {
        .max_string_capacity = 30
    };

    micro_ros_utilities_memory_rule_t rules[] = {
        {"d", 220},
    };

    conf.rules = rules;
    conf.n_rules = sizeof(rules) / sizeof(rules[0]);

    static uint8_t static_buffer[5000];

    micro_ros_utilities_create_static_message_memory(
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CameraInfo),
        &msg,
        conf,
        static_buffer,
        sizeof(static_buffer)
    );

    rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA);

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(100);
    }
}
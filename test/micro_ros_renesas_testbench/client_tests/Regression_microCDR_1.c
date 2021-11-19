#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <tf2_msgs/msg/tf_message.h>

void microros_app(void);

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
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(tf2_msgs, msg, TFMessage),
        "test_pub");

    tf2_msgs__msg__TFMessage msg;

    size_t size = 30;

	msg.transforms.data = (geometry_msgs__msg__TransformStamped*) malloc(size * sizeof(geometry_msgs__msg__TransformStamped));
	msg.transforms.size = size;
	msg.transforms.capacity = size;

	for(size_t i = 0; i < size; i++)
	{
		msg.transforms.data[i].header.frame_id.data = (char *) malloc(sizeof(char) * 100);
		snprintf(msg.transforms.data[i].header.frame_id.data, 10, "frame_%ld", i);
		msg.transforms.data[i].header.frame_id.size = strlen(msg.transforms.data[i].header.frame_id.data);
		msg.transforms.data[i].header.frame_id.capacity = 100;

		msg.transforms.data[i].header.stamp.sec = i;
		msg.transforms.data[i].header.stamp.nanosec = i;

		msg.transforms.data[i].child_frame_id.data = (char *) malloc(sizeof(char) * 100);
		snprintf(msg.transforms.data[i].child_frame_id.data, 10, "child_%ld", i);
		msg.transforms.data[i].child_frame_id.size = strlen(msg.transforms.data[i].child_frame_id.data);
		msg.transforms.data[i].child_frame_id.capacity = 100;

		msg.transforms.data[i].transform.translation.x = i;
		msg.transforms.data[i].transform.translation.y = i;
		msg.transforms.data[i].transform.translation.z = i;

		msg.transforms.data[i].transform.rotation.x = i;
		msg.transforms.data[i].transform.rotation.y = i;
		msg.transforms.data[i].transform.rotation.z = i;
		msg.transforms.data[i].transform.rotation.w = i;
	}

    for(;;){
        rcl_publish(&publisher, &msg, NULL);
        sleep_ms(500);
    }
}
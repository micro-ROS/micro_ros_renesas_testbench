#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

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

    // create publisher reliable
    rcl_publisher_t publisher_reliable;
    rclc_publisher_init_default(
        &publisher_reliable,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_pub_reliable"
    );

    // create publisher best_effort
    rcl_publisher_t publisher_best_effort;
    rclc_publisher_init_best_effort(
        &publisher_best_effort,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_pub_best_effort");

    // create subscriber reliable
    rcl_subscription_t subscriber_reliable;
    rclc_subscription_init_default(
        &subscriber_reliable,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_sub_reliable");

    // create subscriber best_effort
    rcl_subscription_t subscriber_best_effort;
    rclc_subscription_init_best_effort(
        &subscriber_best_effort,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_sub_best_effort");

    for(;;){}
}
#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

void microros_app(void);
void subscription_callback(const void * msgin);

rcl_publisher_t publisher;

void subscription_callback(const void * msgin)
{
    const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;

    std_msgs__msg__Int32 out_msg;
    out_msg.data = msg->data * 10;
    rcl_publish(&publisher, &out_msg, NULL);
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
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_aux_pub");

    // create subscriber
    rcl_subscription_t subscriber;
    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_sub");

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    std_msgs__msg__Int32 msg;
    rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA);

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(100);
    }
}
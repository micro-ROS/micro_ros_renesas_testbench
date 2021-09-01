#include "config.h"
#include "./utils.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

#include <std_msgs/msg/int64.h>

#include <stdio.h>
#include <unistd.h>


void microros_app(void);
void subscription_callback(const void * msgin);

rcl_publisher_t publisher;
std_msgs__msg__Int64 out_msg;

int64_t time_start = 0;

void subscription_callback(const void * msgin)
{
    (void) msgin;

    // Calculate RTT time
    out_msg.data = rmw_uros_epoch_nanos() - time_start;
    rcl_publish(&publisher, &out_msg, NULL);
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // Create node
    rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	rclc_node_init_with_options(&node, "test_node", "", &support, &node_ops);

    // Create publisher
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int64),
        "test_RTT_pub");

    // Create subscriber
    rcl_subscription_t subscriber;
    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int64),
        "test_RTT_sub");

    // Create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    std_msgs__msg__Int64 msg;
    rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA);

    for(;;)
    {
        rmw_uros_sync_session(1000);
        if (0 == time_start){
            time_start = rmw_uros_epoch_nanos();
            out_msg.data = time_start;
            rcl_publish(&publisher, &out_msg, NULL);
        }

        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1000));

        sleep_ms(10);
    }
}

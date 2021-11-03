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

int64_t time_start;

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

    // Create init_options
    rclc_support_t support;

    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    rcl_init_options_init(&init_options, allocator);
    rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
    rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // Create node
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

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
        if (RMW_RET_OK == rmw_uros_sync_session(1000))
        {
            time_start = rmw_uros_epoch_nanos();
            out_msg.data = time_start;
            rcl_publish(&publisher, &out_msg, NULL);

            rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1000));
        }

        sleep_ms(10);
    }
}

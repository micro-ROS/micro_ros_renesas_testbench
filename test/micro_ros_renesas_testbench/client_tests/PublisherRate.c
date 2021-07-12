#include "hal_data.h"
#include "config.h"
#include "./utils.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include <std_msgs/msg/int32.h>

void microros_app(void);
void timer_callback(rcl_timer_t * timer, int64_t last_call_time);

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    (void) last_call_time;
    if (timer != NULL) {
        rcl_publish(&publisher, &msg, NULL);
        msg.data++;
    }
}

/* Thread micro-ROS entry function */
void microros_app(void)
{
    // micro-ROS app
    rcl_allocator_t allocator = rcl_get_default_allocator();

    // create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
	rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	rclc_node_init_with_options(&node, "test_node", "", &support, &node_ops);

    // create publisher
    rclc_publisher_init_best_effort(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_publisher"
    );

    // create timer,
    rcl_timer_t timer;
    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(PUBLISH_PERIOD_MS),
        timer_callback);

    // create executor
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    while(1){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1));
        sleep_ms(1);
    }
}

#include "hal_data.h"
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>

#include <stdio.h>
#include <unistd.h>

#define ARRAY_LEN 4096
static char msg_payload[ARRAY_LEN];

void microros_app(void);
void timer_callback(rcl_timer_t * timer, int64_t last_call_time);

rcl_publisher_t publisher;
std_msgs__msg__String msg;

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    (void) last_call_time;
    if (timer != NULL) {
        rcl_publish(&publisher, &msg, NULL);
    }
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rcl_node_t node;
    rclc_node_init_default(&node, "char_long_sequence_publisher_rcl", "", &support);

    // create publisher
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "test_publisher_fragment");

    // create timer,
    rcl_timer_t timer;
    const unsigned int timer_timeout = 1000;
    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback);

    // create executor
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    // Fill the array with a known sequence
    msg.data.data = msg_payload;
    msg.data.size = 0;
    msg.data.capacity = ARRAY_LEN;

    memset(msg.data.data,'z',ARRAY_LEN-1);
    msg.data.data[ARRAY_LEN-1] = '\0';
    msg.data.size = ARRAY_LEN;

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

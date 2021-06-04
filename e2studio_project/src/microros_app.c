#include "./leds.h"

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

void microros_app(void);
void timer_callback(rcl_timer_t * timer, int64_t last_call_time);

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    (void) last_call_time;
    (void) timer;

    rcl_publish(&publisher, &msg, NULL);
    msg.data++;
}

#include <time.h>
#include <microros_transports.h>

int clock_gettime( int clock_id, struct timespec * tp );

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rcl_node_t node;
    rclc_node_init_default(&node, "renesas_node", "", &support);

    // create publisher
    rclc_publisher_init_default(
      &publisher,
      &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
      "renesas_publisher");

    // create timer,
    rcl_timer_t timer;
    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(50), // 20 Hz
        timer_callback);

    // create executor
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    msg.data = 0;

    while (1)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
        sleep_ms(10);
    }

}
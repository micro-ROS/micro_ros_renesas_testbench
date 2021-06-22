#include "hal_data.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#include <stdio.h>

#include <rmw_microros/rmw_microros.h>

#include <time.h>
#include "config.h"

void microros_app(void);


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

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();
	rclc_support_t support;
	rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();

	rcl_init_options_init(&init_options, allocator);
	rmw_init_options_t* rmw_options = rcl_init_options_get_rmw_init_options(&init_options);

	// create init_options
	rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

	// create node
	rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	const char * node_name = "test_node_domain";
	rclc_node_init_with_options(&node, node_name, "", &support, &node_ops);

	// create publisher
	rclc_publisher_init_default(
		&publisher,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
		"test_publisher_domain");

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

	msg.data = 0;

  	for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rclc_parameter/rclc_parameter.h>

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
    rclc_support_init(&support, 0, NULL, &allocator);

    // create nodes
	rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	rclc_node_init_with_options(&node, "test_node", "", &support, &node_ops);

  	// Create parameter service
    rclc_parameter_server_t param_server;
    rclc_parameter_server_init_default(&param_server, &node);

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, RCLC_PARAMETER_EXECUTOR_HANDLES_NUMBER, &allocator);

    rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA);
    rclc_executor_add_parameter_server(&executor, &param_server, NULL);

    // Add parameters
    rclc_add_parameter(&param_server, "param1", RCLC_PARAMETER_BOOL);
    rclc_add_parameter(&param_server, "param2", RCLC_PARAMETER_INT);
    rclc_add_parameter(&param_server, "param3", RCLC_PARAMETER_DOUBLE);

    rclc_parameter_set_bool(&param_server, "param1", true);

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(100);
    }
}
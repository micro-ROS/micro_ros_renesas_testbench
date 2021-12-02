#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rclc_parameter/rclc_parameter.h>

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

  	// Create parameter service
    rclc_parameter_server_t param_server;
    rclc_parameter_server_init_default(&param_server, &node);

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, RCLC_PARAMETER_EXECUTOR_HANDLES_NUMBER, &allocator);
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
#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include "example_interfaces/srv/add_two_ints.h"

void microros_app(void);
void service_callback(const void * req, void * res);

void service_callback(const void * req, void * res){
  example_interfaces__srv__AddTwoInts_Request * req_in = (example_interfaces__srv__AddTwoInts_Request *) req;
  example_interfaces__srv__AddTwoInts_Response * res_in = (example_interfaces__srv__AddTwoInts_Response *) res;

  res_in->sum = req_in->a + req_in->b;
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rcl_node_t node;
    rcl_node_options_t node_ops = rcl_node_get_default_options();
    node_ops.domain_id = (size_t)(DOMAIN_ID);
    rclc_node_init_with_options(&node, "test_node", "", &support, &node_ops);

    // create service
    rcl_service_t service;
    rclc_service_init_default(&service, &node, ROSIDL_GET_SRV_TYPE_SUPPORT(example_interfaces, srv, AddTwoInts), "/test_add_two_ints");

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    example_interfaces__srv__AddTwoInts_Response res;
    example_interfaces__srv__AddTwoInts_Request req;
    rclc_executor_add_service(&executor, &service, &req, &res, service_callback);

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(10);
    }
}
#include "./utils.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include "std_msgs/msg/int64.h"
#include "example_interfaces/srv/add_two_ints.h"

void microros_app(void);
void client_callback(const void * msg);

rcl_publisher_t publisher;

void client_callback(const void * msg){
  example_interfaces__srv__AddTwoInts_Response * msgin = (example_interfaces__srv__AddTwoInts_Response * ) msg;

  std_msgs__msg__Int64 out_msg;
  out_msg.data = msgin->sum;
  rcl_publish(&publisher, &out_msg, NULL);
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

    // create publisher
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int64),
        "test_aux_pub");

    // create client
    rcl_client_t client;
    rclc_client_init_default(&client, &node, ROSIDL_GET_SRV_TYPE_SUPPORT(example_interfaces, srv, AddTwoInts), "/test_add_two_ints");

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    example_interfaces__srv__AddTwoInts_Response res;
    rclc_executor_add_client(&executor, &client, &res, client_callback);

    // Send request
    int64_t seq;
    example_interfaces__srv__AddTwoInts_Request req;
    req.a = 24;
    req.b = 42;

    sleep_ms(5000); // Sleep a while to ensure DDS matching before sending request

    rcl_send_request(&client, &req, &seq);

    for(;;){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(10);
    }
}
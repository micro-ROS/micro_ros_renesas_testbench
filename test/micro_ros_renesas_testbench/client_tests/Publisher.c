#include "./utils.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

void microros_app(void);

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create nodes
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_pub");

    std_msgs__msg__Int32 msg;
    msg.data = 0;

    for(;;){
        rcl_publish(&publisher, &msg, NULL);
        msg.data++;
    }
}
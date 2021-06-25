#include "hal_data.h"
#include "config.h"
#include "./utils.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include <std_msgs/msg/int32.h>

void microros_app(void);

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
	rclc_node_init_with_options(&node, "test_node_ping", "", &support, &node_ops);

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "test_publisher_ping");

    std_msgs__msg__Int32 msg;

    while(1)
    {
        if (RMW_RET_OK == rmw_uros_ping_agent(1000, 1))
        {
            rcl_publish(&publisher, &msg, NULL);
            msg.data++;
        }

        sleep_ms(500);
    }
}

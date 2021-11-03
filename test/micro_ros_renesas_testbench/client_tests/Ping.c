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

    // Create init_options
    rclc_support_t support;

    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    rcl_init_options_init(&init_options, allocator);
    rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
    rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // Create node
    rcl_node_t node;
    rclc_node_init_default(&node, "test_node_ping", "", &support);

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

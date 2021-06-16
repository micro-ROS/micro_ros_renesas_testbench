#include "hal_data.h"
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include <std_msgs/msg/int32.h>

#define SLEEP_PERIOD_MS 500

void microros_app(void);

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

void microros_app(void)
{
    // micro-ROS app
    allocator = rcl_get_default_allocator();

    rcl_ret_t ret;

    // create init_options
    ret = rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    ret = rclc_node_init_default(&node, "test_node_ping", "", &support);

    // create publisher
    rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "test_publisher_ping");

    while(1)
    {
        if (RMW_RET_OK == rmw_uros_ping_agent(1000, 1))
        {
            rcl_publish(&publisher, &msg, NULL);
            msg.data++;
        }
        
        R_BSP_SoftwareDelay(SLEEP_PERIOD_MS, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

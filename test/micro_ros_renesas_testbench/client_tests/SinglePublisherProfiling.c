#include "net_thread.h"

#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

extern size_t absoluteUsedMemory;
extern size_t usedMemory;

size_t measured_max_used_stack;
size_t measured_absoluteUsedMemory;
size_t measured_usedMemory;

void microros_app(void);

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

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_pub");

    std_msgs__msg__Int32 msg;
    msg.data = 0;

    for(uint8_t i = 0; i < 10; i++){
        rcl_publish(&publisher, &msg, NULL);
        msg.data++;
        sleep_ms(100);
    }

    rcl_publisher_fini(&publisher, &node);
    rcl_node_fini(&node);
    rclc_support_fini(&support);

    measured_max_used_stack = BSP_CFG_STACK_MAIN_BYTES - (uxTaskGetStackHighWaterMark(NULL)*4);
    measured_absoluteUsedMemory = absoluteUsedMemory;
    measured_usedMemory = usedMemory;
}
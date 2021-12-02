#include "net_thread.h"

#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#define ENTITY_NUMBER 10

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

	rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
	rcl_init_options_init(&init_options, allocator);
	rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
	rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

	// create node
	rcl_node_t node;
    rclc_node_init_default(&node, "test_node", "", &support);

    // create publishers
    rcl_publisher_t publishers[ENTITY_NUMBER];
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf[100];
        snprintf(buf, 100, "test_pub_%d", i);

        rclc_publisher_init_default(
            &publishers[i],
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
            buf);
    }

    std_msgs__msg__Int32 msg;
    msg.data = 0;

    for(uint8_t n = 0; n < 10; n++){
        for(uint8_t i = 0; i < ENTITY_NUMBER; i++){
            rcl_publish(&publishers[i], &msg, NULL);
            msg.data++;
            sleep_ms(10);
        }
    }

    for(size_t i = 0; i < ENTITY_NUMBER; i++)
    {
        rcl_publisher_fini(&publishers[i], &node);
    }

    rcl_node_fini(&node);
    rclc_support_fini(&support);
    rcl_init_options_fini(&init_options);

    measured_max_used_stack = BSP_CFG_STACK_MAIN_BYTES - (uxTaskGetStackHighWaterMark(NULL)*4);
    measured_absoluteUsedMemory = absoluteUsedMemory;
    measured_usedMemory = usedMemory;
}
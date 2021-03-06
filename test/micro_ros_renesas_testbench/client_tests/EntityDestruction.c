#include "hal_data.h"
#include "config.h"
#include "./utils.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#define ENTITY_NUMBER 5
rcl_node_t nodes[ENTITY_NUMBER];
rcl_publisher_t publishers[ENTITY_NUMBER];
rcl_subscription_t subscribers[ENTITY_NUMBER];

void microros_app(void);
void subscription_callback(const void * msgin);

bool spin_flag = true;

void subscription_callback(const void * msgin)
{
    (void) msgin;
    spin_flag = false;
}

void microros_app(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;

	rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
	rcl_init_options_init(&init_options, allocator);
	rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);
	rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // create nodes
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf_name[100];
        char buf_namespace[100];
        snprintf(buf_name, 100, "test_node_%d", i);
        snprintf(buf_namespace, 100, "ns_%d", i);

        // create node
        rclc_node_init_default(&nodes[i], buf_name, buf_namespace, &support);
    }

    // create publishers
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf[100];
        snprintf(buf, 100, "test_pub_%d", i);

        rclc_publisher_init_default(
            &publishers[i],
            &nodes[i],
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
            buf);
    }

    // create subscribers
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf[100];
        snprintf(buf, 100, "test_sub_%d", i);

        rclc_subscription_init_default(
            &subscribers[i],
            &nodes[i],
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
            buf);
    }

    // create test subscriber
    rcl_subscription_t test_subscriber;

    rclc_subscription_init_default(
        &test_subscriber,
        &nodes[0],
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_subscriber_delete");

    // create executor
    rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 1, &allocator);

    std_msgs__msg__Int32 msg;
    rclc_executor_add_subscription(&executor, &test_subscriber, &msg, &subscription_callback, ON_NEW_DATA);

    while(spin_flag){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(10);
    }

    for(size_t i = 0; i < ENTITY_NUMBER; i++)
    {
        rcl_publisher_fini(&publishers[i], &nodes[i]);
        rcl_subscription_fini(&subscribers[i], &nodes[i]);
	    rcl_node_fini(&nodes[i]);
    }
}
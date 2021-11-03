#include "./utils.h"
#include "config.h"

#include <time.h>

#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#define ENTITY_NUMBER 5

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

    // create nodes
    rcl_node_t nodes[ENTITY_NUMBER];
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf_name[100];
        char buf_namespace[100];
        snprintf(buf_name, 100, "test_node_%d", i);
        snprintf(buf_namespace, 100, "ns_%d", i);

        // create node
        rclc_node_init_default(&nodes[i], buf_name, buf_namespace, &support);
    }

    // create publishers
    rcl_publisher_t publishers[ENTITY_NUMBER];
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
    rcl_subscription_t subscribers[ENTITY_NUMBER];
    for(size_t i = 0; i < ENTITY_NUMBER; i++){
        char buf[100];
        snprintf(buf, 100, "test_sub_%d", i);

        rclc_subscription_init_default(
            &subscribers[i],
            &nodes[i],
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
            buf);
    }

    // create extra entities in node 0
    rcl_publisher_t extra_publisher;
    rcl_subscription_t extra_subscriber;

    rclc_publisher_init_default(
        &extra_publisher,
        &nodes[0],
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_pub_0_extra");

    rclc_subscription_init_default(
        &extra_subscriber,
        &nodes[0],
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "test_sub_0_extra");

    for(;;){
        sleep_ms(100);
    }
}
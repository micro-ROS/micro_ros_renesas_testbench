#include "hal_data.h"
#include "config.h"
#include "./utils.h"

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>

#include <stdio.h>
#include <unistd.h>

static char msg_payload[ARRAY_LEN];

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

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "test_publisher_fragment");

    // Fill the array with a known sequence
    std_msgs__msg__String msg;

    msg.data.data = msg_payload;
    msg.data.size = 0;
    msg.data.capacity = ARRAY_LEN;

    memset(msg.data.data,'z',ARRAY_LEN-1);
    msg.data.data[ARRAY_LEN-1] = '\0';
    msg.data.size = ARRAY_LEN;

    for(;;){
        rcl_publish(&publisher, &msg, NULL);
        sleep_ms(100);
    }
}

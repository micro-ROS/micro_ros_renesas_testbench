#include "net_thread.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_Sockets.h"

#include "config.h"
#include "./utils.h"

#include <microros_transports.h>
#include <microros_allocators.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcutils/allocator.h>
#include <rmw_microros/rmw_microros.h>

void microros_app(void);

#ifdef MICROROS_PROFILING
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/u_int32_multi_array.h>

#define RCCHECK(fn, led) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){bool a = 1;while(1){set_led_status(led, a = !a); sleep_ms(100);}}}

extern size_t measured_max_used_stack;
extern size_t measured_absoluteUsedMemory;
extern size_t measured_usedMemory;

void * microros_allocate_stub(size_t size, void * state);
void microros_deallocate_stub(void * pointer, void * state);
void * microros_reallocate_stub(void * pointer, size_t size, void * state);
void * microros_zero_allocate_stub(size_t number_of_elements, size_t size_of_element, void * state);
size_t get_block_data_size(void * pointer);
void send_micro_ros_profiling_data(void);

size_t absoluteUsedMemory = 0;
size_t usedMemory = 0;

#define heapBITS_PER_BYTE         ( ( size_t ) 8 )
size_t xBlockAllocatedBit = ( ( size_t ) 1 ) << ( ( sizeof( size_t ) * heapBITS_PER_BYTE ) - 1 );

size_t get_block_data_size(void * pointer){
    // Assuming size_t length at the end of the header struct
    if(NULL == pointer){
        return 0;
    }
    size_t *puc = (size_t *) pointer;
    puc--;

    return (*puc) & ~xBlockAllocatedBit;
}

void * microros_allocate_stub(size_t size, void * state){
    void * ptr = microros_allocate(size, state);
    absoluteUsedMemory += get_block_data_size(ptr);
    usedMemory += get_block_data_size(ptr);
    return ptr;
}

void microros_deallocate_stub(void * pointer, void * state){
    usedMemory -= get_block_data_size(pointer);
    return microros_deallocate(pointer, state);
}

void * microros_reallocate_stub(void * pointer, size_t size, void * state){
    usedMemory -= get_block_data_size(pointer);
    void * ptr = microros_reallocate(pointer, size, state);
    usedMemory += get_block_data_size(ptr);
    absoluteUsedMemory += get_block_data_size(ptr);
    return ptr;
}

void * microros_zero_allocate_stub(size_t number_of_elements, size_t size_of_element, void * state){
    void * ptr = microros_zero_allocate(number_of_elements, size_of_element, state);
    absoluteUsedMemory += get_block_data_size(ptr);
    usedMemory += get_block_data_size(ptr);
    return ptr;
}
#endif

void net_thread_entry(void *pvParameters)
{
    (void) pvParameters;

    struct freertos_sockaddr remote_addr;
    remote_addr.sin_family = FREERTOS_AF_INET;
    remote_addr.sin_port = FreeRTOS_htons(AGENT_IP_PORT);
    remote_addr.sin_addr = FreeRTOS_inet_addr(AGENT_IP_ADDRESS);

    rmw_uros_set_custom_transport(
          false,
          (void *) &remote_addr,
          renesas_e2_transport_open,
          renesas_e2_transport_close,
          renesas_e2_transport_write,
          renesas_e2_transport_read
        );

    rcl_allocator_t custom_allocator = rcutils_get_zero_initialized_allocator();

#ifdef MICROROS_PROFILING
    custom_allocator.allocate = microros_allocate_stub;
    custom_allocator.deallocate = microros_deallocate_stub;
    custom_allocator.reallocate = microros_reallocate_stub;
    custom_allocator.zero_allocate =  microros_zero_allocate_stub;
#else
    custom_allocator.allocate = microros_allocate;
    custom_allocator.deallocate = microros_deallocate;
    custom_allocator.reallocate = microros_reallocate;
    custom_allocator.zero_allocate =  microros_zero_allocate;
#endif

    if (!rcutils_set_default_allocator(&custom_allocator)) {
        printf("Error on default allocators (line %d)\n", __LINE__);
    }

    microros_app();

#ifdef MICROROS_PROFILING
    send_micro_ros_profiling_data();
#endif
}

#ifdef MICROROS_PROFILING
void send_micro_ros_profiling_data(void)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();

    //create init_options
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    // create nodes
	rcl_node_t node;
	rcl_node_options_t node_ops = rcl_node_get_default_options();
	node_ops.domain_id = (size_t)(DOMAIN_ID);
	rclc_node_init_with_options(&node, "profiling_node", "", &support, &node_ops);

    // create publisher
    rcl_publisher_t publisher;
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt32MultiArray),
        "profiling_output");

    std_msgs__msg__UInt32MultiArray msg;
    // Fill header
    msg.layout = (std_msgs__msg__MultiArrayLayout) {0};

    // Fill data
    uint32_t data[] = {measured_max_used_stack, measured_absoluteUsedMemory, measured_usedMemory};
    msg.data.data = data;
    msg.data.size = sizeof(data)/sizeof(data[0]);
    msg.data.capacity = msg.data.size;

    while(1){
        rcl_publish(&publisher, &msg, NULL);
        sleep_ms(500);
    }
}
#endif
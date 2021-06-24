#include "net_thread.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_Sockets.h"

#include "config.h"

#include <microros_transports.h>
#include <microros_allocators.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcutils/allocator.h>
#include <rmw_microros/rmw_microros.h>

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
    custom_allocator.allocate = microros_allocate;
    custom_allocator.deallocate = microros_deallocate;
    custom_allocator.reallocate = microros_reallocate;
    custom_allocator.zero_allocate =  microros_zero_allocate;

    if (!rcutils_set_default_allocator(&custom_allocator)) {
        printf("Error on default allocators (line %d)\n", __LINE__);
    }

    microros_app();
}

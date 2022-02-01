#include "config.h"
#include "./utils.h"

#include <micro_ros_thread.h>

#include <microros_transports.h>
#include <microros_allocators.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcutils/allocator.h>
#include <rmw_microros/rmw_microros.h>

void microros_app(void);

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void micro_ros_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    // Configure wifi network
    WIFINetworkParams_t network_conf = {
        .ucChannel                  = 0,
        .ucSSID                     = "eProsimaWifi_archer",
        .xPassword.xWPA.cPassphrase = "Micro-ROS",
        .xSecurity               = eWiFiSecurityWPA2,
    };

    // Configure agent address
    SocketsSockaddr_t socket_addr = {
         .ulAddress = AGENT_IP_ADDRESS,
         .usPort    = SOCKETS_htons(AGENT_IP_PORT)
    };

    // Add configuration to transport args
    custom_transport_args wifi_args = {
       .network_conf = &network_conf,
       .socket_addr = &socket_addr
    };

    rmw_uros_set_custom_transport(
          false,
          (void *) &wifi_args,
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

#include "thread_microros.h"

#include <microros_transports.h>
#include <microros_allocators.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcutils/allocator.h>
#include <rmw_microros/rmw_microros.h>

/* Thread micro-ROS entry function */
void thread_microros_entry(void)
{
    /* TODO: add your own code here */
    rmw_uros_set_custom_transport(
      false,
      (void *) NULL,
      renesas_e2_transport_open,
      renesas_e2_transport_close,
      renesas_e2_transport_write,
      renesas_e2_transport_read);

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

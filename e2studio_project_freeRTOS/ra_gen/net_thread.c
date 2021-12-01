/* generated thread source file - do not edit */
#include "net_thread.h"

#if 1
static StaticTask_t net_thread_memory;
#if defined(__ARMCC_VERSION)           /* AC6 compiler */
                static uint8_t net_thread_stack[5000] BSP_PLACE_IN_SECTION(BSP_UNINIT_SECTION_PREFIX ".stack.thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
                #else
static uint8_t net_thread_stack[5000] BSP_PLACE_IN_SECTION(BSP_UNINIT_SECTION_PREFIX ".stack.net_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
#endif
#endif
TaskHandle_t net_thread;
void net_thread_create(void);
static void net_thread_func(void *pvParameters);
void rtos_startup_err_callback(void *p_instance, void *p_data);
void rtos_startup_common_init(void);
agt_instance_ctrl_t g_timer0_ctrl;
const agt_extended_cfg_t g_timer0_extend =
{ .count_source = AGT_CLOCK_PCLKB,
  .agto = AGT_PIN_CFG_DISABLED,
  .agtoa = AGT_PIN_CFG_DISABLED,
  .agtob = AGT_PIN_CFG_DISABLED,
  .measurement_mode = AGT_MEASURE_DISABLED,
  .agtio_filter = AGT_AGTIO_FILTER_NONE,
  .enable_pin = AGT_ENABLE_PIN_NOT_USED,
  .trigger_edge = AGT_TRIGGER_EDGE_RISING, };
const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.0001 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x1388,
  .duty_cycle_counts = 0x9c4, .source_div = (timer_source_div_t) 0, .channel = 0, .p_callback = micro_ros_timer_cb,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &g_timer0_extend,
  .cycle_end_ipl = (15),
#if defined(VECTOR_NUMBER_AGT0_INT)
    .cycle_end_irq       = VECTOR_NUMBER_AGT0_INT,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_agt };
extern uint32_t g_fsp_common_thread_count;

const rm_freertos_port_parameters_t net_thread_parameters =
{ .p_context = (void*) NULL, };

void net_thread_create(void)
{
    /* Increment count so we will know the number of threads created in the RA Configuration editor. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

#if 1
    net_thread = xTaskCreateStatic (
#else
                    BaseType_t net_thread_create_err = xTaskCreate(
                    #endif
                                    net_thread_func,
                                    (const char*) "Net thread", 5000 / 4, // In words, not bytes
                                    (void*) &net_thread_parameters, //pvParameters
                                    2,
#if 1
                                    (StackType_t*) &net_thread_stack,
                                    (StaticTask_t*) &net_thread_memory
#else
                        & net_thread
                        #endif
                                    );

#if 1
    if (NULL == net_thread)
    {
        rtos_startup_err_callback (net_thread, 0);
    }
#else
                    if (pdPASS != net_thread_create_err)
                    {
                        rtos_startup_err_callback(net_thread, 0);
                    }
                    #endif
}
static void net_thread_func(void *pvParameters)
{
    /* Initialize common components */
    rtos_startup_common_init ();

    /* Initialize each module instance. */

#if (1 == BSP_TZ_NONSECURE_BUILD) && (1 == 1)
                    /* When FreeRTOS is used in a non-secure TrustZone application, portALLOCATE_SECURE_CONTEXT must be called prior
                     * to calling any non-secure callable function in a thread. The parameter is unused in the FSP implementation.
                     * If no slots are available then configASSERT() will be called from vPortSVCHandler_C(). If this occurs, the
                     * application will need to either increase the value of the "Process Stack Slots" Property in the rm_tz_context
                     * module in the secure project or decrease the number of threads in the non-secure project that are allocating
                     * a secure context. Users can control which threads allocate a secure context via the Properties tab when
                     * selecting each thread. Note that the idle thread in FreeRTOS requires a secure context so the application
                     * will need at least 1 secure context even if no user threads make secure calls. */
                     portALLOCATE_SECURE_CONTEXT(0);
                    #endif

    /* Enter user code for this thread. Pass task handle. */
    net_thread_entry (pvParameters);
}

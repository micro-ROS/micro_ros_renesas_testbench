/* generated thread source file - do not edit */
#include "thread_microros.h"

TX_THREAD thread_microros;
void thread_microros_create(void);
static void thread_microros_func(ULONG thread_input);
static uint8_t thread_microros_stack[5000] BSP_PLACE_IN_SECTION(".stack.thread_microros") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void thread_microros_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&thread_microros, (CHAR*) "microROS thread", thread_microros_func, (ULONG) NULL,
                            &thread_microros_stack, 5000, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread_microros, 0);
    }
}

static void thread_microros_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread_microros_entry ();
}

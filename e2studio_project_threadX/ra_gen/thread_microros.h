/* generated thread header file - do not edit */
#ifndef THREAD_MICROROS_H_
#define THREAD_MICROROS_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void thread_microros_entry(void);
                #else
extern void thread_microros_entry(void);
#endif
#include "r_agt.h"
#include "r_timer_api.h"
FSP_HEADER
/** AGT Timer Instance */
extern const timer_instance_t g_timer0;

/** Access the AGT instance using these structures when calling API functions directly (::p_api is not used). */
extern agt_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;

#ifndef micro_ros_timer_cb
void micro_ros_timer_cb(timer_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* THREAD_MICROROS_H_ */

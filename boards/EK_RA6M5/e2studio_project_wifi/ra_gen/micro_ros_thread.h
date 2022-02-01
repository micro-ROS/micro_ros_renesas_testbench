/* generated thread header file - do not edit */
#ifndef MICRO_ROS_THREAD_H_
#define MICRO_ROS_THREAD_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void micro_ros_thread_entry(void * pvParameters);
                #else
extern void micro_ros_thread_entry(void *pvParameters);
#endif
FSP_HEADER
FSP_FOOTER
#endif /* MICRO_ROS_THREAD_H_ */

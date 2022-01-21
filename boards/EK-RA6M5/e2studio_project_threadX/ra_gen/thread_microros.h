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
#include "nxd_dhcp_client.h"
FSP_HEADER
void g_dhcp_client0_quick_setup();
FSP_FOOTER
#endif /* THREAD_MICROROS_H_ */

/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "nx_api.h"
#include "r_ether_phy.h"
#include "r_ether_phy_api.h"
#include "r_ether.h"
#include "r_ether_api.h"
#include "rm_netxduo_ether.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#ifndef ETHER_PHY_LSI_TYPE_KIT_COMPONENT
#define ETHER_PHY_LSI_TYPE_KIT_COMPONENT ETHER_PHY_LSI_TYPE_DEFAULT
#endif

/** ether_phy on ether_phy Instance. */
extern const ether_phy_instance_t g_ether_phy0;

/** Access the Ethernet PHY instance using these structures when calling API functions directly (::p_api is not used). */
extern ether_phy_instance_ctrl_t g_ether_phy0_ctrl;
extern const ether_phy_cfg_t g_ether_phy0_cfg;
#if (BSP_FEATURE_TZ_HAS_TRUSTZONE == 1) && (BSP_TZ_SECURE_BUILD != 1) && (BSP_TZ_NONSECURE_BUILD != 1) && (BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE == 0)
#define ETHER_BUFFER_PLACE_IN_SECTION BSP_PLACE_IN_SECTION(".ns_buffer.eth")
#else
#define ETHER_BUFFER_PLACE_IN_SECTION
#endif

/** ether on ether Instance. */
extern const ether_instance_t g_ether0;

/** Access the Ethernet instance using these structures when calling API functions directly (::p_api is not used). */
extern ether_instance_ctrl_t g_ether0_ctrl;
extern const ether_cfg_t g_ether0_cfg;

#ifndef rm_netxduo_ether_callback
void rm_netxduo_ether_callback(ether_callback_args_t *p_args);
#endif
/* NetX Duo Ethernet Driver */
void g_netxduo_ether_0(NX_IP_DRIVER *driver_req_ptr);

/* Instance for storing state information for the Ethernet Driver. */
extern rm_netxduo_ether_instance_t g_netxduo_ether_0_instance;
#define G_PACKET_POOL0_PACKET_SIZE (1568)
#define G_PACKET_POOL0_PACKET_NUM  (16)
extern NX_PACKET_POOL g_packet_pool0;
extern uint8_t g_packet_pool0_pool_memory[(G_PACKET_POOL0_PACKET_NUM
		* (G_PACKET_POOL0_PACKET_SIZE + sizeof(NX_PACKET)))];

/* Quick Setup for g_packet_pool0 instance. */
void g_packet_pool0_quick_setup();
#define G_IP0_ADDRESS      (IP_ADDRESS(0,0,0,0))
#define G_IP0_SUBNET_MASK     (IP_ADDRESS(255,255,255,0))
#define G_IP0_GATEWAY_ADDRESS (IP_ADDRESS(0,0,0,0))
#define G_IP0_TASK_STACK_SIZE (2048)
#define G_IP0_TASK_PRIORITY   (3)
#define G_IP0_ARP_CACHE_SIZE (520 * 1)

#define RA_NOT_DEFINED 0xFFFFFFFF
#if (RA_NOT_DEFINED != g_netxduo_ether_0)
#define G_IP0_NETWORK_DRIVER g_netxduo_ether_0
#elif (RA_NOT_DEFINED != RA_NOT_DEFINED)
#define G_IP0_NETWORK_DRIVER rm_netxduo_wifi
#else
#define G_IP0_NETWORK_DRIVER nx_driver_ewf_adapter
#endif
#undef RA_NOT_DEFINED

void g_ip0_quick_setup();
void g_ip0_error_handler(UINT status);

#ifndef NX_DISABLE_IPV6
extern NXD_ADDRESS g_ip0_ipv6_global_address;
extern NXD_ADDRESS g_ip0_ipv6_link_local_address;
#endif
/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */

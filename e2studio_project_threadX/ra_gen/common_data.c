/* generated common source file - do not edit */
#include "common_data.h"

ether_phy_instance_ctrl_t g_ether_phy0_ctrl;

const ether_phy_cfg_t g_ether_phy0_cfg =
{

.channel = 0,
  .phy_lsi_address = 0, .phy_reset_wait_time = 0x00020000, .mii_bit_access_wait_time = 8, .flow_control =
          ETHER_PHY_FLOW_CONTROL_DISABLE,
  .mii_type = ETHER_PHY_MII_TYPE_MII, .p_context = NULL, .p_extend = NULL,

};
/* Instance structure to use this module. */
const ether_phy_instance_t g_ether_phy0 =
{ .p_ctrl = &g_ether_phy0_ctrl, .p_cfg = &g_ether_phy0_cfg, .p_api = &g_ether_phy_on_ether_phy };
ether_instance_ctrl_t g_ether0_ctrl;

uint8_t g_ether0_mac_address[6] =
{ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };

__attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_tx_descriptors[4] ETHER_BUFFER_PLACE_IN_SECTION;
__attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_rx_descriptors[4] ETHER_BUFFER_PLACE_IN_SECTION;

const ether_cfg_t g_ether0_cfg =
{ .channel = 0, .zerocopy = ETHER_ZEROCOPY_ENABLE, .multicast = ETHER_MULTICAST_ENABLE, .promiscuous =
          ETHER_PROMISCUOUS_DISABLE,
  .flow_control = ETHER_FLOW_CONTROL_DISABLE, .padding = ETHER_PADDING_2BYTE, .padding_offset = 14, .broadcast_filter =
          0,
  .p_mac_address = g_ether0_mac_address,

  .p_rx_descriptors = g_ether0_rx_descriptors,
  .p_tx_descriptors = g_ether0_tx_descriptors,

  .num_tx_descriptors = 4,
  .num_rx_descriptors = 4,

  .pp_ether_buffers = NULL,

  .ether_buffer_size = 1536,

#if defined(VECTOR_NUMBER_EDMAC0_EINT)
                .irq                = VECTOR_NUMBER_EDMAC0_EINT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif

  .interrupt_priority = (12),

  .p_callback = rm_netxduo_ether_callback,
  .p_ether_phy_instance = &g_ether_phy0, .p_context = &g_netxduo_ether_0_instance, .p_extend = NULL, };

/* Instance structure to use this module. */
const ether_instance_t g_ether0 =
{ .p_ctrl = &g_ether0_ctrl, .p_cfg = &g_ether0_cfg, .p_api = &g_ether_on_ether };
static NX_PACKET *g_netxduo_ether_0_tx_packets[4];
static NX_PACKET *g_netxduo_ether_0_rx_packets[4];

static rm_netxduo_ether_ctrl_t g_netxduo_ether_0_ctrl;
static rm_netxduo_ether_cfg_t g_netxduo_ether_0_cfg =
{ .p_ether_instance = &g_ether0, .mtu = 1500, .p_tx_packets = g_netxduo_ether_0_tx_packets, .p_rx_packets =
          g_netxduo_ether_0_rx_packets };

rm_netxduo_ether_instance_t g_netxduo_ether_0_instance =
{ .p_ctrl = &g_netxduo_ether_0_ctrl, .p_cfg = &g_netxduo_ether_0_cfg };

/*
 * NetX Duo Driver: g_netxduo_ether_0
 * Passes rm_netxduo_ether instance and driver request into the rm_netxduo_ether driver.
 */
void g_netxduo_ether_0(NX_IP_DRIVER *driver_req_ptr)
{
    rm_netxduo_ether (driver_req_ptr, &g_netxduo_ether_0_instance);
}
#ifndef NX_DISABLE_IPV6
NXD_ADDRESS g_ip0_ipv6_global_address =
{ .nxd_ip_version = NX_IP_VERSION_V6, .nxd_ip_address.v6 =
{ ((0x2001 << 16) | 0x0), ((0x0 << 16) | 0x0), ((0x0 << 16) | 0x0), ((0x0 << 16) | 0x1) } };

NXD_ADDRESS g_ip0_ipv6_link_local_address =
{ .nxd_ip_version = NX_IP_VERSION_V6, .nxd_ip_address.v6 =
{ ((0x0 << 16) | 0x0), ((0x0 << 16) | 0x0), ((0x0 << 16) | 0x0), ((0x0 << 16) | 0x0) } };

#endif
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };

void g_common_init(void)
{
}

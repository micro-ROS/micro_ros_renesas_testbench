/* generated HAL source file - do not edit */
#include "hal_data.h"
agt_instance_ctrl_t g_timer0_ctrl;
const agt_extended_cfg_t g_timer0_extend =
		{ .count_source = AGT_CLOCK_PCLKB, .agto = AGT_PIN_CFG_DISABLED,
				.agtoa = AGT_PIN_CFG_DISABLED, .agtob = AGT_PIN_CFG_DISABLED,
				.measurement_mode = AGT_MEASURE_DISABLED, .agtio_filter =
						AGT_AGTIO_FILTER_NONE, .enable_pin =
						AGT_ENABLE_PIN_NOT_USED, .trigger_edge =
						AGT_TRIGGER_EDGE_RISING, };
const timer_cfg_t g_timer0_cfg = { .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.0001 seconds. Actual duty: 50%. */.period_counts =
		(uint32_t) 0x1388, .duty_cycle_counts = 0x9c4, .source_div =
		(timer_source_div_t) 0, .channel = 0, .p_callback = micro_ros_timer_cb,
/** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
		.p_context = &NULL,
#endif
		.p_extend = &g_timer0_extend, .cycle_end_ipl = (12),
#if defined(VECTOR_NUMBER_AGT0_INT)
    .cycle_end_irq       = VECTOR_NUMBER_AGT0_INT,
#else
		.cycle_end_irq = FSP_INVALID_VECTOR,
#endif
		};
/* Instance structure to use this module. */
const timer_instance_t g_timer0 = { .p_ctrl = &g_timer0_ctrl, .p_cfg =
		&g_timer0_cfg, .p_api = &g_timer_on_agt };
usb_instance_ctrl_t g_basic0_ctrl;

#if !defined(g_usb_descriptor)
extern usb_descriptor_t g_usb_descriptor;
#endif
#define RA_NOT_DEFINED (1)
const usb_cfg_t g_basic0_cfg = { .usb_mode = USB_MODE_PERI, .usb_speed =
		USB_SPEED_FS, .module_number = 0, .type = USB_CLASS_PCDC,
#if defined(g_usb_descriptor)
                .p_usb_reg = g_usb_descriptor,
#else
		.p_usb_reg = &g_usb_descriptor,
#endif
		.usb_complience_cb = NULL,
#if defined(VECTOR_NUMBER_USBFS_INT)
                .irq       = VECTOR_NUMBER_USBFS_INT,
#else
		.irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_RESUME)
                .irq_r     = VECTOR_NUMBER_USBFS_RESUME,
#else
		.irq_r = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_FIFO_0)
                .irq_d0    = VECTOR_NUMBER_USBFS_FIFO_0,
#else
		.irq_d0 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBFS_FIFO_1)
                .irq_d1    = VECTOR_NUMBER_USBFS_FIFO_1,
#else
		.irq_d1 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
                .hsirq     = VECTOR_NUMBER_USBHS_USB_INT_RESUME,
#else
		.hsirq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_FIFO_0)
                .hsirq_d0  = VECTOR_NUMBER_USBHS_FIFO_0,
#else
		.hsirq_d0 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_USBHS_FIFO_1)
                .hsirq_d1  = VECTOR_NUMBER_USBHS_FIFO_1,
#else
		.hsirq_d1 = FSP_INVALID_VECTOR,
#endif
		.ipl = (12), .ipl_r = (12), .ipl_d0 = (12), .ipl_d1 = (12), .hsipl =
				(12), .hsipl_d0 = (12), .hsipl_d1 = (12),
#if (BSP_CFG_RTOS != 0)
                .p_usb_apl_callback = NULL,
#else
		.p_usb_apl_callback = NULL,
#endif
#if defined(NULL)
                .p_context = NULL,
#else
		.p_context = &NULL,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#else
                .p_transfer_tx = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
#else
                .p_transfer_rx = &RA_NOT_DEFINED,
#endif
		};
#undef RA_NOT_DEFINED

/* Instance structure to use this module. */
const usb_instance_t g_basic0 = { .p_ctrl = &g_basic0_ctrl, .p_cfg =
		&g_basic0_cfg, .p_api = &g_usb_on_usb, };

void g_hal_init(void) {
	g_common_init();
}

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
/* Actual period: 0.00001 seconds. Actual duty: 50%. */.period_counts =
		(uint32_t) 0x1f4, .duty_cycle_counts = 0xfa, .source_div =
		(timer_source_div_t) 0, .channel = 0, .p_callback = micro_ros_timer_cb,
/** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
		.p_context = &NULL,
#endif
		.p_extend = &g_timer0_extend, .cycle_end_ipl = (15),
#if defined(VECTOR_NUMBER_AGT0_INT)
    .cycle_end_irq       = VECTOR_NUMBER_AGT0_INT,
#else
		.cycle_end_irq = FSP_INVALID_VECTOR,
#endif
		};
/* Instance structure to use this module. */
const timer_instance_t g_timer0 = { .p_ctrl = &g_timer0_ctrl, .p_cfg =
		&g_timer0_cfg, .p_api = &g_timer_on_agt };
sci_uart_instance_ctrl_t g_uart0_ctrl;

baud_setting_t g_uart0_baud_setting = {
/* Baud rate calculated with 0.469% error. */.abcse = 0, .abcs = 0, .bgdm = 1,
		.cks = 0, .brr = 53, .mddr = (uint8_t) 256, .brme = false };

/** UART extended configuration for UARTonSCI HAL driver */
const sci_uart_extended_cfg_t g_uart0_cfg_extend = {
		.clock = SCI_UART_CLOCK_INT, .rx_edge_start =
				SCI_UART_START_BIT_FALLING_EDGE, .noise_cancel =
				SCI_UART_NOISE_CANCELLATION_DISABLE, .rx_fifo_trigger =
				SCI_UART_RX_FIFO_TRIGGER_MAX, .p_baud_setting =
				&g_uart0_baud_setting,
		.flow_control = SCI_UART_FLOW_CONTROL_RTS,
#if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
		.flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
		};

/** UART interface configuration */
const uart_cfg_t g_uart0_cfg = { .channel = 0, .data_bits = UART_DATA_BITS_8,
		.parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
				user_uart_callback, .p_context = NULL, .p_extend =
				&g_uart0_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
		.p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
		.p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
		.rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
#if defined(VECTOR_NUMBER_SCI0_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI0_RXI,
#else
		.rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI0_TXI,
#else
		.txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI0_TEI,
#else
		.tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI0_ERI,
#else
		.eri_irq = FSP_INVALID_VECTOR,
#endif
		};

/* Instance structure to use this module. */
const uart_instance_t g_uart0 = { .p_ctrl = &g_uart0_ctrl,
		.p_cfg = &g_uart0_cfg, .p_api = &g_uart_on_sci };
void g_hal_init(void) {
	g_common_init();
}

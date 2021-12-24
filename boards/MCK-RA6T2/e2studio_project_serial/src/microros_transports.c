#include <microros_transports.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <hal_data.h>

#include <uxr/client/transport.h>
#include <uxr/client/util/time.h>
#include <rmw_microxrcedds_c/config.h>

#ifdef RMW_UXRCE_TRANSPORT_CUSTOM

// --- micro-ROS Transports ---
#define UART_IT_BUFFER_SIZE 2048
static uint8_t it_buffer[UART_IT_BUFFER_SIZE];
static size_t it_head = 0, it_tail = 0;
bool g_write_complete = false;

void user_uart_callback (uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
            g_write_complete = true;
            break;

        case UART_EVENT_RX_COMPLETE:
            #if defined (BOARD_RA6T2_MCK)
                R_SCI_B_UART_Read(&g_uart0_ctrl, &it_buffer[0], UART_IT_BUFFER_SIZE);
            #else
                R_SCI_UART_Read(&g_uart0_ctrl, &it_buffer[0], UART_IT_BUFFER_SIZE);
            #endif
        	 break;

        default:
            break;
    }
}

bool renesas_e2_transport_open(struct uxrCustomTransport * transport){
    (void) transport;
    fsp_err_t err;

    #if defined (BOARD_RA6T2_MCK)
        R_SCI_B_UART_Open (&g_uart0_ctrl, &g_uart0_cfg);
        err = R_SCI_B_UART_Read(&g_uart0_ctrl, &it_buffer[0], UART_IT_BUFFER_SIZE);
    #else
        R_SCI_UART_Open (&g_uart0_ctrl, &g_uart0_cfg);
        err = R_SCI_UART_Read(&g_uart0_ctrl, &it_buffer[0], UART_IT_BUFFER_SIZE);
    #endif

    return err == FSP_SUCCESS;
}

bool renesas_e2_transport_close(struct uxrCustomTransport * transport){
    (void) transport;
    fsp_err_t err;

    #if defined (BOARD_RA6T2_MCK)
        err = R_SCI_B_UART_Close(&g_uart0_ctrl);
    #else
        err = R_SCI_UART_Close(&g_uart0_ctrl);
    #endif

    return err == FSP_SUCCESS;
}

size_t renesas_e2_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * error){
    (void) transport;
    (void) error;

    g_write_complete = false;
    fsp_err_t err;

    #if defined (BOARD_RA6T2_MCK)
        err = R_SCI_B_UART_Write(&g_uart0_ctrl, buf, len);
    #else
        err = R_SCI_UART_Write(&g_uart0_ctrl, buf, len);
    #endif

    if (err != FSP_SUCCESS)
    {
        return 0;
    }

    while(!g_write_complete)
    {
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
    }

    return len;
}

size_t renesas_e2_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* error){
    (void) transport;
    (void) error;

    int64_t start = uxr_millis();
    size_t wrote = 0;

    while ((uxr_millis() -  start) < timeout)
	{
    	it_tail = UART_IT_BUFFER_SIZE - g_uart0_ctrl.rx_dest_bytes;

    	if (it_head != it_tail)
    	{
    		while (it_head != it_tail && wrote < len)
    		{
				buf[wrote] = it_buffer[it_head];
				it_head = (it_head + 1) % UART_IT_BUFFER_SIZE;
				wrote++;
			}

    		break;
    	}

    	R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MICROSECONDS);
	}

    return wrote;
}

#endif //RMW_UXRCE_TRANSPORT_CUSTOM

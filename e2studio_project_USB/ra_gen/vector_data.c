/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
            [1] = usbfs_resume_handler, /* USBFS RESUME (USBFS resume interrupt) */
            [2] = usbfs_d0fifo_handler, /* USBFS FIFO 0 (DMA transfer request 0) */
            [3] = usbfs_d1fifo_handler, /* USBFS FIFO 1 (DMA transfer request 1) */
            [4] = usbhs_interrupt_handler, /* USBHS USB INT RESUME (USBHS interrupt) */
            [5] = usbhs_d0fifo_handler, /* USBHS FIFO 0 (DMA transfer request 0) */
            [6] = usbhs_d1fifo_handler, /* USBHS FIFO 1 (DMA transfer request 1) */
            [7] = agt_int_isr, /* AGT0 INT (AGT interrupt) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_USBFS_INT), /* USBFS INT (USBFS interrupt) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_USBFS_RESUME), /* USBFS RESUME (USBFS resume interrupt) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_0), /* USBFS FIFO 0 (DMA transfer request 0) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_1), /* USBFS FIFO 1 (DMA transfer request 1) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME), /* USBHS USB INT RESUME (USBHS interrupt) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_0), /* USBHS FIFO 0 (DMA transfer request 0) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_1), /* USBHS FIFO 1 (DMA transfer request 1) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_AGT0_INT), /* AGT0 INT (AGT interrupt) */
        };
        #endif

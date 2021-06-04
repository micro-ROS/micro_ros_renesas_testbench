/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (12)
#endif
/* ISR prototypes */
void usbfs_interrupt_handler(void);
void usbfs_resume_handler(void);
void usbfs_d0fifo_handler(void);
void usbfs_d1fifo_handler(void);
void usbhs_interrupt_handler(void);
void usbhs_d0fifo_handler(void);
void usbhs_d1fifo_handler(void);
void sci_uart_rxi_isr(void);
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);
void sci_uart_eri_isr(void);
void agt_int_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_USBFS_INT ((IRQn_Type) 0) /* USBFS INT (USBFS interrupt) */
#define VECTOR_NUMBER_USBFS_RESUME ((IRQn_Type) 1) /* USBFS RESUME (USBFS resume interrupt) */
#define VECTOR_NUMBER_USBFS_FIFO_0 ((IRQn_Type) 2) /* USBFS FIFO 0 (DMA transfer request 0) */
#define VECTOR_NUMBER_USBFS_FIFO_1 ((IRQn_Type) 3) /* USBFS FIFO 1 (DMA transfer request 1) */
#define VECTOR_NUMBER_USBHS_USB_INT_RESUME ((IRQn_Type) 4) /* USBHS USB INT RESUME (USBHS interrupt) */
#define VECTOR_NUMBER_USBHS_FIFO_0 ((IRQn_Type) 5) /* USBHS FIFO 0 (DMA transfer request 0) */
#define VECTOR_NUMBER_USBHS_FIFO_1 ((IRQn_Type) 6) /* USBHS FIFO 1 (DMA transfer request 1) */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 7) /* SCI0 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 8) /* SCI0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 9) /* SCI0 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 10) /* SCI0 ERI (Receive error) */
#define VECTOR_NUMBER_AGT0_INT ((IRQn_Type) 11) /* AGT0 INT (AGT interrupt) */
typedef enum IRQn
{
    Reset_IRQn = -15,
    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn = -11,
    UsageFault_IRQn = -10,
    SecureFault_IRQn = -9,
    SVCall_IRQn = -5,
    DebugMonitor_IRQn = -4,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,
    USBFS_INT_IRQn = 0, /* USBFS INT (USBFS interrupt) */
    USBFS_RESUME_IRQn = 1, /* USBFS RESUME (USBFS resume interrupt) */
    USBFS_FIFO_0_IRQn = 2, /* USBFS FIFO 0 (DMA transfer request 0) */
    USBFS_FIFO_1_IRQn = 3, /* USBFS FIFO 1 (DMA transfer request 1) */
    USBHS_USB_INT_RESUME_IRQn = 4, /* USBHS USB INT RESUME (USBHS interrupt) */
    USBHS_FIFO_0_IRQn = 5, /* USBHS FIFO 0 (DMA transfer request 0) */
    USBHS_FIFO_1_IRQn = 6, /* USBHS FIFO 1 (DMA transfer request 1) */
    SCI0_RXI_IRQn = 7, /* SCI0 RXI (Receive data full) */
    SCI0_TXI_IRQn = 8, /* SCI0 TXI (Transmit data empty) */
    SCI0_TEI_IRQn = 9, /* SCI0 TEI (Transmit end) */
    SCI0_ERI_IRQn = 10, /* SCI0 ERI (Receive error) */
    AGT0_INT_IRQn = 11, /* AGT0 INT (AGT interrupt) */
} IRQn_Type;
#endif /* VECTOR_DATA_H */

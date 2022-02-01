/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (5)
#endif
/* ISR prototypes */
void agt_int_isr(void);
void canfd_error_isr(void);
void canfd_channel_tx_isr(void);
void canfd_rx_fifo_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_AGT0_INT ((IRQn_Type) 0) /* AGT0 INT (AGT interrupt) */
#define AGT0_INT_IRQn          ((IRQn_Type) 0) /* AGT0 INT (AGT interrupt) */
#define VECTOR_NUMBER_CAN1_CHERR ((IRQn_Type) 1) /* CAN1 CHERR (Channel error) */
#define CAN1_CHERR_IRQn          ((IRQn_Type) 1) /* CAN1 CHERR (Channel error) */
#define VECTOR_NUMBER_CAN1_TX ((IRQn_Type) 2) /* CAN1 TX (Transmit interrupt) */
#define CAN1_TX_IRQn          ((IRQn_Type) 2) /* CAN1 TX (Transmit interrupt) */
#define VECTOR_NUMBER_CAN_GLERR ((IRQn_Type) 3) /* CAN GLERR (Global error) */
#define CAN_GLERR_IRQn          ((IRQn_Type) 3) /* CAN GLERR (Global error) */
#define VECTOR_NUMBER_CAN_RXF ((IRQn_Type) 4) /* CAN RXF (Global recieve FIFO interrupt) */
#define CAN_RXF_IRQn          ((IRQn_Type) 4) /* CAN RXF (Global recieve FIFO interrupt) */
#endif /* VECTOR_DATA_H */

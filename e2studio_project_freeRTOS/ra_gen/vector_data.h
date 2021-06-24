/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (2)
#endif
/* ISR prototypes */
void ether_eint_isr(void);
void agt_int_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_EDMAC0_EINT ((IRQn_Type) 0) /* EDMAC0 EINT (EDMAC 0 interrupt) */
#define VECTOR_NUMBER_AGT0_INT ((IRQn_Type) 1) /* AGT0 INT (AGT interrupt) */
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
    EDMAC0_EINT_IRQn = 0, /* EDMAC0 EINT (EDMAC 0 interrupt) */
    AGT0_INT_IRQn = 1, /* AGT0 INT (AGT interrupt) */
} IRQn_Type;
#endif /* VECTOR_DATA_H */

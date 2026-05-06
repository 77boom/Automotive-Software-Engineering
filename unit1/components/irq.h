
#ifndef IRQ_H
#define IRQ_H

#define IRQ_HANDLER(id) (void id(void))

#define IRQ_BASE 33

#define IRQ_PIT_CH0 (IRQ_BASE + 1)
#define IRQ_PIT_CH1 (IRQ_BASE + 2)
#define IRQ_PIT_CH2 (IRQ_BASE + 3)
#define IRQ_PIT_CH3 (IRQ_BASE + 4)

#define IRQ_CAN_RX (IRQ_BASE + 10)

#endif // IRQ_H

#include "conf.h"
#include "init.h"
#include "adc.h"
#include "can.h"
#include "xpc56el.h"
/* Global variables **********************************************************/
uint32_t systemBlink = 0;

VRegisters VREG;
IRQ_Table IRQ;

void __can_receive()
{
  CANRxFrame frame;
  fill_can_rx_frame(&frame);

  // call user IRQ handler
  can_receive(frame);

  // reset interrupt flag
  CAN_0.IFRL.R = 0;
}

/*
 * @brief	MCU peripherals initialization function
 *
 * @param	void
 * @retval	void
 */
void peripheralsInit()
{

  // componentsInit();

  /* Enable Interrupts */
  // irqIsrEnable();

  /* Pit Init */
  PIT_Init();
  /*SIu Init*/
  SIU_Init();
  SIU.PCR[45].R = 0x0200;
  /*Init ADC*/
  // ADC0_Init();
  // ADC1_Init();
  /*  Activates the CAN driver 1. */

  IRQ.can_rcv = __can_receive;

  CAN_Init();

  // setup can message filter
  CAN_0.RXGMASK.R = (vuint32_t)CAN_MASK_REGISTER;
  CAN_0.RXGACCEPT.R = (vuint32_t)CAN_ACCEPTANCE_REGISTER;
}

/*
 * @brief	System internal function calls and blink
 *
 * @param	void
 * @retval	void
 */
void systemFunction(void)
{
  ADC0_StartConversion();
  ADC1_StartConversion();

  if (systemBlink < 24)
  {
    systemBlink++;
  }
  else
  {
    SIU.GPDO[45].R = ~SIU.GPDO[45].R;
    systemBlink = 0;
  }
}

#include "pit.h"
#include "init.h"
#include "xpc56el.h"

/* Configure the timer channels with a specific frequency */
void PIT_ConfigureTimer(uint8_t channel, uint32_t frequency)
{
    uint32_t reg;
    /* PIT frequency (PIT uses the Peripheral set 0 clock = SYS_CLK / SYSCLK_DIVIDER. */
    // reg = SPCGetSystemClock() / (frequency) - 1U;
    reg = 60000 * frequency;
    /* Define the timer load value */
    PIT.CHANNEL[channel].LDVAL.R = reg;
    /* Define the timer current value  */
    PIT.CHANNEL[channel].CVAL.R = reg;
    /* Interrupt timer flag cleared */
    PIT.CHANNEL[channel].TFLG.R = 1U;
}

/* Enable timer */
void PIT_StartTimer(uint8_t channel)
{
    PIT.CHANNEL[channel].TCTRL.R = 3U;
}

/* Disable timer */
void PIT_StopTimer(uint8_t channel)
{
    PIT.CHANNEL[channel].TCTRL.R = 0U;
}

/* Initialize the timer module */
void PIT_Init(void)
{
    // setup IRQ handlers
    IRQ.pit_ch0 = PIT_Channel_0;
    IRQ.pit_ch1 = PIT_Channel_1;
    IRQ.pit_ch2 = PIT_Channel_2;
    IRQ.pit_ch3 = PIT_Channel_3;
}

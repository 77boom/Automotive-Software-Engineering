/**
 * HLE layer for the Programmable Interval Timers (PIT)
 * of the vECU
 **/

#ifndef PIT_H
#define PIT_H

// #include "xpc56el.h"
#include "typedefs.h"

void PIT_ConfigureTimer(uint8_t channel, uint32_t frequency);
void PIT_StartTimer(uint8_t channel);
void PIT_StopTimer(uint8_t channel);
void PIT_Init(void);

#endif

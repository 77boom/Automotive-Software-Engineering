/**
* HLE layer for the OSAL
* of the vECU
**/

#include "osal.h"
#include "pit.h"
#include "siu.h"

uint8_t sleep_elapsed = 1;

void pit_sleep(uint32_t msec)
{
    if (sleep_elapsed) {
        sleep_elapsed = 0;
        PIT_ConfigureTimer(0, msec);
        PIT_StartTimer(0);

        while (!sleep_elapsed) {
            // wait for timer interrupt
        }
    }
}

void PIT_Channel_0(void){
    PIT_StopTimer(0);
    sleep_elapsed = 1;
}

void osalThreadDelaySeconds(uint32_t sec)
{
    pit_sleep(sec*1000);
}

void osalThreadDelayMilliseconds(uint32_t msec)
{
    pit_sleep(msec);
}

void osalThreadDelayMicroseconds(uint32_t usec)
{
    pit_sleep(usec / 1000);
}

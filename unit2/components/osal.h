/**
* Operating system abstraction layer (OSAL)
**/

#ifndef OSAL_H
#define OSAL_H

#include "typedefs.h"

/**
 * @brief   Delays for the specified number of seconds.
 */
#define sysWaitSeconds(sec) osalThreadDelaySeconds(sec)

/**
 * @brief   Delays for the specified number of milliseconds.
 */
#define sysWaitMilliseconds(msec) osalThreadDelayMilliseconds(msec)

/**
 * @brief   Delays for the specified number of microseconds.
 */
#define sysWaitMicroseconds(usec) osalThreadDelayMicroseconds(usec)

void osalThreadDelaySeconds(uint32_t sec);
void osalThreadDelayMilliseconds(uint32_t msec);
void osalThreadDelayMicroseconds(uint32_t usec);

void PIT_Channel_0(void);

#endif // OSAL_H

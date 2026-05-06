#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*
 * Derived generic types.
 */
 // volatile
typedef  int8_t     vint8_t;        /**< Volatile signed 8 bits.    */
typedef  uint8_t    vuint8_t;       /**< Volatile unsigned 8 bits.  */
typedef  int16_t    vint16_t;       /**< Volatile signed 16 bits.   */
typedef  uint16_t   vuint16_t;      /**< Volatile unsigned 16 bits. */
typedef  int32_t    vint32_t;       /**< Volatile signed 32 bits.   */
typedef  uint32_t   vuint32_t;      /**< Volatile unsigned 32 bits. */
typedef  uint64_t   vuint64_t;      /**< Volatile unsigned 64 bits. */

#endif

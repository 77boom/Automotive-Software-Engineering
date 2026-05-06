#ifndef _CAN_LLD_H_
#define _CAN_LLD_H_

#include "spc5_flexcan.h"

#include "typedefs.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

extern CANDriver CAND1;

/**
 * @name    CAN status flags
 * @{
 */
/**
 * @brief   Errors rate warning.
 */
#define CAN_LIMIT_WARNING 1U
/**
 * @brief   Errors rate error.
 */
#define CAN_LIMIT_ERROR 2U
/**
 * @brief   Bus off condition reached.
 */
#define CAN_BUS_OFF_ERROR 4U
/**
 * @brief   Framing error of some kind on the CAN bus.
 */
#define CAN_FRAMING_ERROR 8U
/**
 * @brief   Overflow in receive queue.
 */
#define CAN_OVERFLOW_ERROR 16U
/** @} */

/**
 * @brief   Special mailbox identifier.
 */
#define CAN_ANY_MAILBOX 0U

/**
 * @brief   FIFO operation identifier.
 */
#define CAN_FIFO 0xFFU

/**
 * @brief   This switch defines whether the driver implementation supports
 *          a low power switch mode with an automatic wakeup feature.
 */
#define CAN_SUPPORTS_SLEEP FALSE

/**
 * @brief   This implementation supports eight FIFO receive filters.
 */
#define SPC5_CAN_MAX_FILTERS 8U

/**
 * @brief   Enable filters.
 */
#define SPC5_CAN_FILTER_ON 1U

/**
 * @brief   Disable filters.
 */
#define SPC5_CAN_FILTER_OFF 0U

/**
 * @name    CAN registers helper macros
 * @{
 */
#define CAN_MCR_MAXMB(n) (uint32_t)(n)
#define CAN_MCR_AEN (1UL << 12)
#define CAN_MCR_LPRIO_EN (1UL << 13)
#define CAN_MCR_BCC (1UL << 16)
#define CAN_MCR_SRX_DIS (1UL << 17)
#define CAN_MCR_LPM_ACK (1UL << 20)
#define CAN_MCR_WRN_EN (1UL << 21)
#define CAN_MCR_SUPV (1UL << 23)
#define CAN_MCR_FRZ_ACK (1UL << 24)
#define CAN_MCR_WAK_MSK (1UL << 26)
#define CAN_MCR_NOT_RDY (1UL << 27)
#define CAN_MCR_HALT (1UL << 28)
#define CAN_MCR_FEN (1UL << 29)
#define CAN_MCR_FRZ (1UL << 30)
#define CAN_MCR_MDIS (1UL << 31)

#define CAN_CTRL_PROPSEG(n) (uint32_t)(n)
#define CAN_CTRL_LOM (1UL << 3)
#define CAN_CTRL_TSYN (1UL << 5)
#define CAN_CTRL_BOFF_REC (1UL << 6)
#define CAN_CTRL_SMP (1UL << 7)
#define CAN_CTRL_RWRN_MSK (1UL << 10)
#define CAN_CTRL_TWRN_MSK (1UL << 11)
#define CAN_CTRL_LPB (1UL << 12)
#define CAN_CTRL_CLK_SRC (1UL << 13)
#define CAN_CTRL_ERR_MSK (1UL << 14)
#define CAN_CTRL_BOFF_MSK (1UL << 15)
#define CAN_CTRL_PSEG2(n) ((uint32_t)(n) << 16)
#define CAN_CTRL_PSEG1(n) ((uint32_t)(n) << 19)
#define CAN_CTRL_RJW(n) ((uint32_t)(n) << 22)
#define CAN_CTRL_PRESDIV(n) ((uint32_t)(n) << 24)

#define CAN_IDE_STD 0U /**< @brief Standard id.    */
#define CAN_IDE_EXT 1U /**< @brief Extended id.    */

#define CAN_RTR_DATA 0U   /**< @brief Data frame.     */
#define CAN_RTR_REMOTE 1U /**< @brief Remote frame.   */

#define CAN_ESR_ERR_INT (1UL << 1)
#define CAN_ESR_BOFF_INT (1UL << 2)
#define CAN_ESR_TWRN_INT (1UL << 17)
#define CAN_ESR_RWRN_INT (1UL << 16)

#define CAN_RX_FIFO_FORMAT_A 0x00U
#define CAN_RX_FIFO_FORMAT_B 0x01U
#define CAN_RX_FIFO_FORMAT_C 0x02U
#define CAN_RX_FIFO_FORMAT_D 0x03U
/** @} */

/**
 * @brief   Macro for compatibility with MCAN driver.
 */
#define CAN_ANY_RXBUFFER CAN_ANY_MAILBOX
#define CAN_ANY_TXBUFFER CAN_ANY_MAILBOX
#define CAN_ID_STD CAN_IDE_STD
/** @} */

/**
 * @brief  canmsg_t constant
 */
#define CAN_MSG_OK (1UL << 1)     /**< @brief message OK.    		  */
#define CAN_MSG_WAIT (1UL << 2)   /**< @brief mailbox is non empty. wait   */
#define CAN_MSG_NOFIFO (1UL << 3) /**< @brief FIFO not enabled */

void can_lld_start(CANDriver *canp, CANConfig *config);

void fill_can_rx_frame(CANRxFrame *target);

#endif // _CAN_LLD_H_

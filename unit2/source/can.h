/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef CAN_H_
#define CAN_H_

/* Includes ******************************************************************/
#include "can_lld.h"
#include "can_lld_cfg.h"


/* TO-DO: your task implementations ******************************************/

/* Macro definitions *********************************************************/
#define	CAN_MASK_REGISTER			0x7FE // 0 -> ignore all bits (i.e. accept all messages)
#define	CAN_ACCEPTANCE_REGISTER  	0x010


/*****************************************************************************/


/* Function prototypes *******************************************************/
void CAN_Init(void);
void CAN_TxMessage(CANTxFrame txMsg, canmbx_t mbx);

#endif /* CAN_H_ */

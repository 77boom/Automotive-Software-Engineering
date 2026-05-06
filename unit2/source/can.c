/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "can.h"
#include "xpc56el.h"

/*
 * @brief	CAN0 initialization function
 *
 * @param	void
 * @retval	void
 */
void CAN_Init(void){
	can_lld_start(&CAND1, &can_config_cfg0);


	/* TO-DO: pre-configure message buffer(s) for sending here ***********************/

	CAN_0.BUF[8].MSG_CS.B.IDE = CAN_IDE_EXT;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */
	CAN_0.BUF[8].MSG_ID.B.STD_ID = 0;		/* Message ID for standard frame */
	CAN_0.BUF[8].MSG_ID.B.EXT_ID = 0xDA0;		/* Message ID for extended frame*/
	CAN_0.BUF[8].MSG_CS.B.RTR = CAN_RTR_DATA;		/* Remote Transmission Request; 0 = Data Frame */
	CAN_0.BUF[8].MSG_CS.B.LENGTH = 0;			/* Length of Payload, 0 - 8*/

	CAN_0.BUF[8].MSG_CS.B.SRR = 1;    // substitute remote request  can拓展帧里的一个控制位，can_buffer里定义，若发送拓展帧，ssr必须定义为1

	/*************************************************************************/

	//for speed
	CAN_0.BUF[9].MSG_CS.B.IDE = CAN_IDE_EXT;
	CAN_0.BUF[9].MSG_CS.B.SRR = 1;
	CAN_0.BUF[9].MSG_ID.B.STD_ID = 0;
	CAN_0.BUF[9].MSG_ID.B.EXT_ID = 0x5A0;
	CAN_0.BUF[9].MSG_CS.B.RTR = CAN_RTR_DATA;	
	CAN_0.BUF[9].MSG_CS.B.LENGTH = 1;


	// for rpm
	CAN_0.BUF[10].MSG_CS.B.IDE = CAN_IDE_EXT;
	CAN_0.BUF[10].MSG_CS.B.SRR = 1;
	CAN_0.BUF[10].MSG_ID.B.STD_ID = 0;
	CAN_0.BUF[10].MSG_ID.B.EXT_ID = 0x280;
	CAN_0.BUF[10].MSG_CS.B.RTR = CAN_RTR_DATA;
	CAN_0.BUF[10].MSG_CS.B.LENGTH = 2;

	// for lights
	CAN_0.BUF[11].MSG_CS.B.IDE = CAN_IDE_EXT;
	CAN_0.BUF[11].MSG_CS.B.SRR = 1;
	CAN_0.BUF[11].MSG_ID.B.STD_ID = 0;
	CAN_0.BUF[11].MSG_ID.B.EXT_ID = 0x470;
	CAN_0.BUF[11].MSG_CS.B.RTR = CAN_RTR_DATA;
	CAN_0.BUF[11].MSG_CS.B.LENGTH = 1;

}


/*
 * @brief	CAN message transmit function
 *
 * @param	CANTxFrame	txMsg
 * @param	canmbx_t	mbx
 * @retval	void
 */
void CAN_TxMessage(CANTxFrame txMsg, canmbx_t mbx){
	// nop
}

/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"


/* Global variables **********************************************************/
int speed = 0;
int rpm = 8000;
int rpm_direction = -1;

/*
rpm = 8000：从 8000 开始
rpm_direction = -1：一开始往下减
后面如果到 0，就把方向改成 1
如果到 8000，就把方向改成 -1

*/

int can_send_counter = 0;
int engine_on = 0;  // 0 is mean the engine is off when beginning of the program

int blink_counter = 0;
int blink_state = 0;
/*
blink_counter：用来数 100ms 消息次数
blink_state：0/1 反转，用来实现闪烁。     */


void can_send_engine_on(void){

	/* TO-DO: your task implementations **************************************/

    // set payload bytes, if necessary
    // CAN_0.BUF[...].DATA.B[...] = ...;
		// 0xDA0 payload is 0

	// write the correct CODE value to this register to instruct the CAN controller to transmit the CAN message
	// CAN_0.BUF[...].CS.B.CODE = ...;
	CAN_0.BUF[8].MSG_ID.B.STD_ID = 0;
	CAN_0.BUF[8].MSG_ID.B.EXT_ID = 0xDA0;

	CAN_0.BUF[8].MSG_CS.B.CODE = 0xC;

	LED_Tx = !LED_Tx;   // to check if it really sending

	
}

void can_send_speed(int value){
	/* TO-DO: your task implementations **************************************/

	speed = value * 240 / 4095;			//把 POT 的 0-4095 映射成 0-240。

    CAN_0.BUF[9].DATA.B[0] = speed;		//把速度值放进 payload 第 1 个字节。

    CAN_0.BUF[9].MSG_CS.B.CODE = 0xC;	//触发发送。

}

void can_send_rpm(int value){
	/* TO-DO: your task implementations **************************************/
	CAN_0.BUF[10].DATA.B[0] = value & 0xFF;
    CAN_0.BUF[10].DATA.B[1] = (value >> 8) & 0xFF;

    CAN_0.BUF[10].MSG_CS.B.CODE = 0xC;

	//把一个 int rpm 拆成低字节和高字节

}

// rules for indicator function 
void can_send_lights(void){
    /* TO-DO: your task implementations **************************************/

    int light_value = 0;

    if ((SW1 == 0) && (SW2 == 0))
    {
        light_value = 0x00;
        LED_U1 = 0;
        LED_U3 = 0;
    }
    else if ((SW1 == 0) && (SW2 == 1))
    {
        light_value = 0x01;
        LED_U1 = blink_state;
        LED_U3 = 0;
    }
    else if ((SW1 == 1) && (SW2 == 0))
    {
        light_value = 0x02;
        LED_U1 = 0;
        LED_U3 = blink_state;
    }
    else
    {
        light_value = 0x03;
        LED_U1 = blink_state;
        LED_U3 = blink_state;
    }

    CAN_0.BUF[11].DATA.B[0] = light_value;
    CAN_0.BUF[11].MSG_CS.B.CODE = 0xC;
}


void can_send(void){

	/* TO-DO: your task implementations **************************************/

	if (engine_on == 0)
	{
		return;     // if the engine didn't start, then quit can_send directly, and dont send any CAN message
	}				// 没收到start engine 消息前不发送 0xDA0


	can_send_counter++;

	if (can_send_counter >= 10)
	{
		can_send_counter = 0;

		blink_counter++;
		if (blink_counter >= 5)   
    	{
        	blink_counter = 0;
        	blink_state = !blink_state;
    	}
	/*为什么是 5？

	因为这个代码块每 100ms 执行一次。数 5 次就是：
	5 * 100ms = 500ms
	所以转向灯大约每半秒亮灭一次，比较像真实闪烁
	*/
		

		can_send_engine_on();    // 只发送engine on
		can_send_speed(POT);	 // 只发送speed
		can_send_rpm(rpm);
		can_send_lights();
	}


}


/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization */
	peripheralsInit();



	/* TO-DO: your task implementations **************************************/

	/* Configure and start timer channels */
	/* PIT timer channel 1, period = 1000 ms */
	PIT_ConfigureTimer(1, 1000);
	PIT_StartTimer(1);


	/*************************************************************************/


	/* main program */
	while(1){
		/* System function */
		systemFunction();

		/* TO-DO: your task implementations **********************************/

		can_send();

		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	CAN receive interrupt
 *
 * @param   CANDriver   canp	The CAN controller which received a message
 * @param	CANRxFrame	crfp	The message which was received
 * @retval	void
 */
void can_receive(CANRxFrame crfp) {
    if(crfp.IDE == CAN_IDE_STD) // a standard message frame has been received
    {
		LED_Rx = ! LED_Rx;
		
		if (crfp.SID == 0x11)
		{
			LED_U1 = !LED_U1;

			LED_P = 1;   // the red light, indicate the engine states
			engine_on = 1;  // turn on engine
		}

		if (crfp.SID == 0x10)
		{
			LED_P = 0;
			LED_U1 = 0;
			LED_U3 = 0;
			engine_on = 0;   // turn off engine
		}
		
        /* TO-DO: your task implementations ******************************/

        //if (crfp.SID == ...) // check the Message ID
        //{	
			//如果收到的是标准 CAN 帧：
    		//	Rx 灯闪一下/反转一下

   		 	//如果这条消息 ID 是 0x11：
       		//	U1 灯也闪一下/反转一下

        //}
		


    }
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */

/*
每 1 秒进入一次 PIT_Channel_1()
rpm 减 250
减到 0 后开始加
加到 8000 后开始减
*/
void PIT_Channel_1(void){
    /* TO-DO: your task implementations **************************************/

    rpm = rpm + (rpm_direction * 250);

    if (rpm <= 0)
    {
        rpm = 0;
        rpm_direction = 1;
    }

    if (rpm >= 8000)
    {
        rpm = 8000;
        rpm_direction = -1;
    }
}


/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void){
	/* TO-DO: your task implementations **************************************/

}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){
	/* TO-DO: your task implementations **************************************/


}

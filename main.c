/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-1
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"

#include "xpc56el.h"
#include "siu.h"


/* Global variables **********************************************************/

// put any global variables you need here

/* Task-1 implementation *****************************************************/
void task_pot(int x){

	if (x < 682)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 0;	//D9, Rx
		SIU.GPDO[58].R = 0;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
	}

	else if (682 <= x < 1364)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 0;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
	}

	else if (1364 <= x < 2046)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
	}

	else if (2046 <= x < 2728)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 1;	//A6, U3
	}
	
	else if (2728 <= x < 3410)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 1;	//C11, U2
		SIU.GPDO[6].R = 1;	//A6, U3
	}

	else
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 1;	//D11, U1
		SIU.GPDO[43].R = 1;	//C11, U2
		SIU.GPDO[6].R = 1;	//A6, U3
	}
	
	
	

}





/* Task-2 implementation *****************************************************/
void task_ldr(int x){

	task_pot(x); 	//reuse the leds rules function
	
}

/* Task-3 implementation *****************************************************/
void task_counter(void){

	/* TO-DO: your task implementations **************************************/

	/*************************************************************************/
}

/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization, do not remove */
	peripheralsInit();


	/* TO-DO: your task implementations **************************************/


	/* Configure and start timer channels */	
    // PIT_ConfigureTimer(<channel>, <interval in milliseconds>);

	/*************************************************************************/

	/* main program */
	while(1){
		/* System function, do not remove */
		systemFunction();
		/* TO-DO: your task implementations **********************************/
        


		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void all_leds_off(void){
		SIU.GPDO[56].R = 0;	//D8, P
		SIU.GPDO[57].R = 0;	//D9, Rx
		SIU.GPDO[58].R = 0;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
}

//** SIU.PCR 配置这个引脚怎么工作； 
//SIU.GPDO 是给已经配置成输出的引脚写输出值； 
//SIU.GPDI 是从已经配置成输入的引脚 读输入值


void PIT_Channel_1(void){
	while (1)
	{
		int SW1 = SIU.GPDI[52].R;    //read SW1
		int x = (ADC0.CDR[5].R & 0x00000FFF);   //read POT

		if (SW1 == 1)
		{
			task_pot(x);
		}
		else
		{
			all_leds_off();
		}
		
		
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


	/*************************************************************************/
}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){

	/* TO-DO: your task implementations **************************************/


	/*************************************************************************/
}

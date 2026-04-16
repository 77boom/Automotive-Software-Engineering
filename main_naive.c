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
int counter_value = 0;   // value 0-7, means the current counter value
int count_up = 1;  //1 = count up, 0 = count down, means the count direction , 


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

	else if (x >= 682 && x < 1364)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 0;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
	}

	else if (x >= 1364 && x < 2046)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
	}

	else if (x >= 2046 && x < 2728)
	{
		SIU.GPDO[56].R = 1;	//D8, P
		SIU.GPDO[57].R = 1;	//D9, Rx
		SIU.GPDO[58].R = 1;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 1;	//A6, U3
	}
	
	else if (x >= 2728 && x < 3410)
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
void task_ldr(int x){    // light sensor

	task_pot(x); 	//reuse the leds rules function
	
}

/* Task-3 implementation *****************************************************/
void task_counter(void){

	/* TO-DO: your task implementations **************************************/

	SIU.GPDO[56].R = 0;   /* P  */
	SIU.GPDO[57].R = 0;   /* Rx */
	SIU.GPDO[58].R = 0;   /* Tx */ // turn off P/Rx/Tx before switch task 3


	if (counter_value == 0)
	{
		SIU.GPDO[59].R = 0;  //U1
		SIU.GPDO[43].R = 0;  //U2
		SIU.GPDO[6].R = 0;  //U3
	}
	else if (counter_value == 1)
	{
		SIU.GPDO[59].R = 0;  //U1
		SIU.GPDO[43].R = 0;  //U2
		SIU.GPDO[6].R = 1;  //U3
	}
	else if (counter_value == 2)
	{
		SIU.GPDO[59].R = 0;  //U1
		SIU.GPDO[43].R = 1;  //U2
		SIU.GPDO[6].R = 0;  //U3
	}
	else if (counter_value == 3)
	{
		SIU.GPDO[59].R = 0;  //U1
		SIU.GPDO[43].R = 1;  //U2
		SIU.GPDO[6].R = 1;  //U3
	}
	else if (counter_value == 4)
	{
		SIU.GPDO[59].R = 1;  //U1
		SIU.GPDO[43].R = 0;  //U2
		SIU.GPDO[6].R = 0;  //U3
	}
	else if (counter_value == 5)
	{
		SIU.GPDO[59].R = 1;  //U1
		SIU.GPDO[43].R = 0;  //U2
		SIU.GPDO[6].R = 1;  //U3
	}
	else if (counter_value == 6)
	{
		SIU.GPDO[59].R = 1;  //U1
		SIU.GPDO[43].R = 1;  //U2
		SIU.GPDO[6].R = 0;  //U3
	}
	else
	{
		SIU.GPDO[59].R = 1;  //U1
		SIU.GPDO[43].R = 1;  //U2
		SIU.GPDO[6].R = 1;  //U3
	}
	
	
	
	
	
	
	/*************************************************************************/
}



void all_leds_off(void){
		SIU.GPDO[56].R = 0;	//D8, P
		SIU.GPDO[57].R = 0;	//D9, Rx
		SIU.GPDO[58].R = 0;	//D10, Tx
		SIU.GPDO[59].R = 0;	//D11, U1
		SIU.GPDO[43].R = 0;	//C11, U2
		SIU.GPDO[6].R = 0;	//A6, U3
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

	PIT_ConfigureTimer(1, 1000); //channel 1, 1000 ms = 1 second;
	PIT_StartTimer(1);


	/* TO-DO: your task implementations **************************************/


	/* Configure and start timer channels */	
    // PIT_ConfigureTimer(<channel>, <interval in milliseconds>);

	/*************************************************************************/

	/* main program */
	while(1){
		/* System function, do not remove */
		systemFunction();
		/* TO-DO: your task implementations **********************************/
        
		int SW1 = SIU.GPDI[52].R;    //read SW1
		int x = (ADC0.CDR[5].R & 0x00000FFF);   //read POT

		int SW2 = SIU.GPDI[53].R;
		int ldr_value = (ADC1.CDR[3].R & 0x00000FFF);

		int SW3 = SIU.GPDI[54].R; // read SW3

		if (SW1 == 1)
		{
			task_pot(x);
		}
		else if (SW1 == 0 && SW2 == 1)   // task2 3.4. to read ldr_value
		{
			task_ldr(ldr_value);
		}
		else if (SW1 == 0 && SW2 == 0 && SW3 == 1)
		{
			task_counter();
		}
		else
		{
			all_leds_off();
		}



		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}



//** SIU.PCR 配置这个引脚怎么工作； 
//SIU.GPDO 是给已经配置成输出的引脚写输出值； 
//SIU.GPDI 是从已经配置成输入的引脚 读输入值


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */

void PIT_Channel_1(void){

    int BT1 = SIU.GPDI[60].R;    //button 1
    int BT2 = SIU.GPDI[62].R;    //button 2
    int SW4 = SIU.GPDI[55].R;

	if (BT1 == 1)
	{
		count_up = 1;  //
	}
	else if (BT2 == 1)
	{
		count_up = 0; 
	}
	

	if (SW4 == 1)  //only update counter when SW4 is ON.  the counter value itself should only be updated(increased or decreased) when SW4 is ON. 计数器本身是否更新
	{
		if (count_up == 1)
		{
			counter_value++;
			if (counter_value > 7)
			{
				counter_value = 0;
			}
			
		}
		else
		{
			counter_value--;
			if (counter_value < 0)
			{
				counter_value = 7;
			}
			
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

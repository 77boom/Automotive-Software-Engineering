/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: siu.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "siu.h"
#include "xpc56el.h"

/*
 * @brief	SIU pin configuration function
 *
 * @param	void
 * @retval	void
 */
void SIU_Init(void)
{
	// Configure all pins which are required for your task here

	/* Input pin configurations */

	//SIU.PCR[...].R = ...;

	SIU.PCR[52].R = 0x100;	//D4, task1's input

	SIU.PCR[53].R = 0x100; // D5, task2's input


	SIU.PCR[60].R = 0x100; // BT1, D12 task3‘s input
	SIU.PCR[62].R = 0x100; //d14  BT2
	SIU.PCR[54].R = 0x100;   /* SW3 -> D[6]  */
	SIU.PCR[55].R = 0x100;   /* SW4 -> D[7]  */



/* 	SIU.GPDO[x].R = <value>;

	value = SIU.GPDI[x].R; */

	/* Output pin configurations */

	//SIU.PCR[...].R = ...;
	
	SIU.PCR[56].R = 0x200;	//D8
	SIU.PCR[57].R = 0x200;	//D9
	SIU.PCR[58].R = 0x200;	//D10
	SIU.PCR[59].R = 0x200;	//D11
	SIU.PCR[43].R = 0x200;	//C11
	SIU.PCR[6].R = 0x200;	//A6
	


	/* Analog pin configurations */

	//SIU.PCR[...].R = ...;

		
	SIU.PCR[66].R = 0x2500; //E2,POT,task1's analog input

	SIU.PCR[32].R = 0x2500; // C0, LDR, task2's analog input

	

	/*************************************************************************/
}

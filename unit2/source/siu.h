/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: siu.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef SIU_H_
#define SIU_H_

/* Includes ******************************************************************/
#include "xpc56el.h"

/* Macro definitions *********************************************************/
/* PCR number definitions */

/* TO-DO: your task implementations */


#define	PCR_LED_P		56		/* PD8 */
#define	PCR_LED_Rx		57		/* PD9 */
#define	PCR_LED_Tx		58		/* PD10 */
#define	PCR_LED_U1		59		/* PD11 */
#define	PCR_LED_U2		43		/* PC11 */
#define	PCR_LED_U3		6		/* PA6 */

#define	PCR_BT1			60		/* PD12 */
#define	PCR_BT2			62		/* PD14 */
#define	PCR_SW1			52		/* PD4 */
#define	PCR_SW2			53		/* PD5 */
#define	PCR_SW3			54		/* PD6 */
#define	PCR_SW4			55		/* PD7 */

#define	PCR_POT			66		/* PE2 */
#define	PCR_LDR			32		/* PC0 */


/* Output pin definitions */
#define	LED_P		SIU.GPDO[PCR_LED_P].R
#define	LED_Rx		SIU.GPDO[PCR_LED_Rx].R
#define	LED_Tx		SIU.GPDO[PCR_LED_Tx].R
#define	LED_U1		SIU.GPDO[PCR_LED_U1].R
#define	LED_U2		SIU.GPDO[PCR_LED_U2].R
#define	LED_U3		SIU.GPDO[PCR_LED_U3].R

/* Input pin definitions */
#define	BT1				SIU.GPDI[PCR_BT1].R
#define	BT2				SIU.GPDI[PCR_BT2].R
#define	SW1				SIU.GPDI[PCR_SW1].R
#define	SW2				SIU.GPDI[PCR_SW2].R
#define	SW3				SIU.GPDI[PCR_SW3].R
#define	SW4				SIU.GPDI[PCR_SW4].R

/* Analog pin definitions */
#define	POT				(ADC0.CDR[5].R & 0x00000FFF)	/* PE2 */
#define	LDR				(ADC1.CDR[3].R & 0x00000FFF)	/* PC0 */


/* Function prototypes *******************************************************/
void SIU_Init(void);

#endif /* SIU_H_ */

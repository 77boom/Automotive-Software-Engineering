
#ifndef XPC56EL_H
#define XPC56EL_H

#include "conf.h"
#include "typedefs.h"

#include "spc5_flexcan.h"

// align structs with vECU structs (no padding)
#pragma pack(push, 1)

typedef union
{ /* GPDO - GPIO Pad Data Output Register */
  vuint8_t R;
  struct
  {
    vuint8_t : 7;
    vuint8_t PDO : 1; // Pad Data Out
  } B;
} SIUL_GPDO_8B_tag;

typedef union
{ /* GPDI - GPIO Pad Data Input Register */
  vuint8_t R;
  struct
  {
    vuint8_t : 7;
    vuint8_t PDO : 1; // Pad Data Out
  } B;
} SIUL_GPDI_8B_tag;

/* Register layout for all registers PCR... */

typedef union
{ /* PCR - Pad Configuration Register */
  vuint16_t R;
  struct
  {
    vuint16_t : 1;
#ifndef USE_FIELD_ALIASES_SIUL
    vuint16_t SMC : 1; /* Safe Mode Control */
#else
    vuint16_t SME : 1; /* deprecated name - please avoid */
#endif
    vuint16_t APC : 1; /* Analog Pad Control */
    vuint16_t : 1;
    vuint16_t PA : 2;  /* Pad Output Assignment */
    vuint16_t OBE : 1; /* Output Buffer Enable */
    vuint16_t IBE : 1; /* Input Buffer Enable */
#ifndef USE_FIELD_ALIASES_SIUL
    vuint16_t DSC : 2; /* Drive Strength Control */
#else
    vuint16_t DCS : 2; /* deprecated name - please avoid */
#endif
    vuint16_t ODE : 1; /* Open Drain Output Enable */
    vuint16_t HYS : 1; /* Input Hysteresis */
    vuint16_t SRC : 2; /* Slew Rate Control */
    vuint16_t WPE : 1; /* Weak Pull Up/Down Enable */
    vuint16_t WPS : 1; /* Weak Pull Up/Down Select */
  } B;
} SIUL_PCR_16B_tag;

typedef union
{ /* PSMI - Pad Selection for Multiplexed Inputs */
  vuint8_t R;
  struct
  {
    vuint8_t : 4;
    vuint8_t PADSEL : 4; /* Pad selection for pin */
  } B;
} SIUL_PSMI_8B_tag;

typedef struct
{
  /* GPDO - GPIO Pad Data Output Register */
  SIUL_GPDO_8B_tag GPDO[512];
  SIUL_GPDI_8B_tag GPDI[512];
  SIUL_PCR_16B_tag PCR[512];

  /* PSMI - Pad Selection for Multiplexed Inputs */
  SIUL_PSMI_8B_tag PSMI[256]; /* offset: 0x0500  (0x0001 x 256) */
} SIUL;

/****************************************************************/
/*                                                              */
/* Module: PIT_RTI  */
/*                                                              */
/****************************************************************/

typedef union
{ /* PIT_RTI_PITMCR - PIT Module Control Register */
  vuint32_t R;
  struct
  {
    vuint32_t : 30;
    vuint32_t MDIS : 1; /* Module Disable. Disable the module clock */
    vuint32_t FRZ : 1;  /* Freeze. Allows the timers to be stopped when the device enters debug mode */
  } B;
} PIT_RTI_PITMCR_32B_tag;

/* Register layout for all registers LDVAL... */

typedef union
{ /* PIT_RTI_LDVAL - Timer Load Value Register */
  vuint32_t R;
  struct
  {
    vuint32_t TSV : 32; /* Time Start Value Bits */
  } B;
} PIT_RTI_LDVAL_32B_tag;

/* Register layout for all registers CVAL... */

typedef union
{ /* PIT_RTI_CVAL - Current Timer Value Register */
  vuint32_t R;
  struct
  {
    vuint32_t TVL : 32; /* Current Timer Value Bits */
  } B;
} PIT_RTI_CVAL_32B_tag;

/* Register layout for all registers TCTRL... */

typedef union
{ /* PIT_RTI_TCTRL - Timer Control Register */
  vuint32_t R;
  struct
  {
    vuint32_t : 30;
    vuint32_t TIE : 1; /* Timer Interrupt Enable Bit */
    vuint32_t TEN : 1; /* Timer Enable Bit */
  } B;
} PIT_RTI_TCTRL_32B_tag;

/* Register layout for all registers TFLG... */

typedef union
{ /* PIT_RTI_TFLG - Timer Flag Register */
  vuint32_t R;
  struct
  {
    vuint32_t : 31;
    vuint32_t TIF : 1; /* Timer Interrupt Flag Bit */
  } B;
} PIT_RTI_TFLG_32B_tag;

typedef struct PIT_RTI_CHANNEL_struct_tag
{

  /* PIT_RTI_LDVAL - Timer Load Value Register */
  PIT_RTI_LDVAL_32B_tag LDVAL; /* relative offset: 0x0000 */
                               /* PIT_RTI_CVAL - Current Timer Value Register */
  PIT_RTI_CVAL_32B_tag CVAL;   /* relative offset: 0x0004 */
                               /* PIT_RTI_TCTRL - Timer Control Register */
  PIT_RTI_TCTRL_32B_tag TCTRL; /* relative offset: 0x0008 */
                               /* PIT_RTI_TFLG - Timer Flag Register */
  PIT_RTI_TFLG_32B_tag TFLG;   /* relative offset: 0x000C */

} PIT_RTI_CHANNEL_tag;

typedef struct PIT_RTI_struct_tag
{                                /* start of PIT_RTI_tag */
                                 /* PIT_RTI_PITMCR - PIT Module Control Register */
  PIT_RTI_PITMCR_32B_tag PITMCR; /* offset: 0x0000 size: 32 bit */
  // int8_t PIT_RTI_reserved_0004_C[252];
  /*  Register set CHANNEL */
  PIT_RTI_CHANNEL_tag CHANNEL[4]; /* offset: 0x0100  (0x0010 x 4) */
} PIT_RTI_tag;

/****************************************************************/
/*                                                              */
/* Module: ADC  */
/*                                                              */
/****************************************************************/

typedef union
{ /* CHANNEL DATA REGS */
  vuint32_t R;
  struct
  {
    vuint32_t : 12;
    vuint32_t VALID : 1;  /* validity of data */
    vuint32_t OVERW : 1;  /* overwrite data */
    vuint32_t RESULT : 2; /* reflects mode conversion */
    vuint32_t : 6;
    vuint32_t CDATA : 10; /* Channel 0 converted data */
  } B;
} ADC_CDR_32B_tag;

typedef struct ADC_struct_tag
{
  ADC_CDR_32B_tag CDR[96];
} ADC_tag;

typedef struct
{
  SIUL SIU;
  PIT_RTI_tag PIT;
  ADC_tag ADC0;
  ADC_tag ADC1;

  struct spc5_flexcan CAN_0;
} VRegisters;

#pragma pack(pop)

typedef void (*irq_handler)(void);

typedef struct
{
  irq_handler pit_ch0;
  irq_handler pit_ch1;
  irq_handler pit_ch2;
  irq_handler pit_ch3;

  irq_handler can_rcv;
} IRQ_Table;

// Definitions of registers
extern VRegisters VREG;

#define SIU VREG.SIU
#define ADC0 VREG.ADC0
#define ADC1 VREG.ADC1
#define PIT VREG.PIT
#define CAN_0 VREG.CAN_0

extern IRQ_Table IRQ;

#endif

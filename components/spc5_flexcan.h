#ifndef SPC5_FLEXCAN_H
#define SPC5_FLEXCAN_H

#include "typedefs.h"

// align structs with vECU structs (no padding)
#pragma pack(push, 1)

typedef union
{
  vuint32_t R;
  struct {
      vuint32_t:4;
      vuint32_t CODE:4;
      vuint32_t:1;
      vuint32_t SRR:1;
      vuint32_t IDE:1;
      vuint32_t RTR:1;
      vuint32_t LENGTH:4;
      vuint32_t TIMESTAMP:16;
  } B;
} FLEXCAN_MSG_CS_32B_tag;

typedef union {   /* Message Buffer Identifier Field */
  vuint32_t R;
  struct {
     vuint32_t  PRIO:3;            /* Local Priority */
     vuint32_t STD_ID:11;
     vuint32_t EXT_ID:18;
  } B;
} FLEXCAN_MSG_ID_32B_tag;

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
/* PPC register definitions not compatible with MISRA rules on bit-fields
   (Rules 6.1). */
/*lint -e46 */
/**
 * @brief   SPC5 FlexCAN registers block.
 * @note    Redefined from the SPC5 headers because the non uniform
 *          declaration of the SubModules registers among the various
 *          sub-families.
 */
struct FLEXCAN_BUFFER_t {
  union {
     /* Message Buffer Control and Status */
     FLEXCAN_MSG_CS_32B_tag MSG_CS;   /* relative offset: 0x0000 */
     FLEXCAN_MSG_CS_32B_tag CS;       /* deprecated - please avoid */
  };

  union {
     /* Message Buffer Identifier Field */
     FLEXCAN_MSG_ID_32B_tag MSG_ID;   /* relative offset: 0x0004 */
     FLEXCAN_MSG_ID_32B_tag ID;       /* deprecated - please avoid */
  };

  union {
      vuint8_t  B[8]; /* Data buffer in Bytes (8 bits) */
  } DATA;

};                          /* end of FLEXCAN_BUF_t */

struct FLEXCAN_RXFIFO_BUFFER_t {
  union {
      vuint32_t R;
      struct {
          vuint32_t:9;
          vuint32_t SRR:1;
          vuint32_t IDE:1;
          vuint32_t RTR:1;
          vuint32_t LENGTH:4;
          vuint32_t TIMESTAMP:16;
      } B;
  } CS;

  union {
      vuint32_t R;
      struct {
  vuint32_t:3;
          vuint32_t STD_ID:11;
          vuint32_t EXT_ID:18;
      } B;
  } ID;

  union {
      vuint8_t  B[8]; /* Data buffer in Bytes (8 bits) */
  } DATA;

  //uint32_t FLEXCAN_RXFIFO_reserved[20];   /* {0x00E0-0x0090}/0x4 = 0x14 */

  union {
      vuint32_t R;
  } IDTABLE[8];

};                          /* end of FLEXCAN_RXFIFO_t */

struct spc5_flexcan {
  union {
      vuint32_t R;
      struct {
          vuint32_t MDIS:1;
          vuint32_t FRZ:1;
          vuint32_t FEN:1;
          vuint32_t HALT:1;
          vuint32_t NOTRDY:1;
          vuint32_t WAKMSK:1;
          vuint32_t SOFTRST:1;
          vuint32_t FRZACK:1;
          vuint32_t SUPV:1;
          vuint32_t SLFWAK:1;
          vuint32_t WRNEN:1;
          vuint32_t LPMACK:1;
          vuint32_t WAKSRC:1;
          vuint32_t:1;
          vuint32_t SRXDIS:1;
          vuint32_t BCC:1;
            vuint32_t:2;
          vuint32_t LPRIO_EN:1;
          vuint32_t AEN:1;
            vuint32_t:2;
          vuint32_t IDAM:2;
            vuint32_t:2;
          vuint32_t MAXMB:6;
      } B;
  } MCR;                  /* Module Configuration Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t PRESDIV:8;
          vuint32_t RJW:2;
          vuint32_t PSEG1:3;
          vuint32_t PSEG2:3;
          vuint32_t BOFFMSK:1;
          vuint32_t ERRMSK:1;
          vuint32_t CLKSRC:1;
          vuint32_t LPB:1;
          vuint32_t TWRNMSK:1;
          vuint32_t RWRNMSK:1;
          vuint32_t:2;
          vuint32_t SMP:1;
          vuint32_t BOFFREC:1;
          vuint32_t TSYN:1;
          vuint32_t LBUF:1;
          vuint32_t LOM:1;
          vuint32_t PROPSEG:3;
      } B;
  } CR;                   /* Control Register */

  union {
      vuint32_t R;
  } TIMER;                /* Free Running Timer */

  //uint32_t FLEXCAN_reserved1;

  union {
      vuint32_t R;
      struct {
          vuint32_t MI:32;
      } B;
  } RXGMASK;              /* RX Global Mask */

  union {
      vuint32_t R;
      struct {
          vuint32_t MI:32;
      } B;
  } RXGACCEPT;             /* RX Global Acceptance */

  union {
      vuint32_t R;
      struct {
          vuint32_t MI:32;
      } B;
  } RX15MASK;             /* RX 15 Mask */

  union {
      vuint32_t R;
      struct {
          vuint32_t:16;
          vuint32_t RXECNT:8;
          vuint32_t TXECNT:8;
      } B;
  } ECR;                  /* Error Counter Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t:14;
          vuint32_t TWRNINT:1;
          vuint32_t RWRNINT:1;
          vuint32_t BIT1ERR:1;
          vuint32_t BIT0ERR:1;
          vuint32_t ACKERR:1;
          vuint32_t CRCERR:1;
          vuint32_t FRMERR:1;
          vuint32_t STFERR:1;
          vuint32_t TXWRN:1;
          vuint32_t RXWRN:1;
          vuint32_t IDLE:1;
          vuint32_t TXRX:1;
          vuint32_t FLTCONF:2;
            vuint32_t:1;
          vuint32_t BOFFINT:1;
          vuint32_t ERRINT:1;
          vuint32_t WAKINT:1;
      } B;
  } ESR;                  /* Error and Status Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t BUF63M:1;
          vuint32_t BUF62M:1;
          vuint32_t BUF61M:1;
          vuint32_t BUF60M:1;
          vuint32_t BUF59M:1;
          vuint32_t BUF58M:1;
          vuint32_t BUF57M:1;
          vuint32_t BUF56M:1;
          vuint32_t BUF55M:1;
          vuint32_t BUF54M:1;
          vuint32_t BUF53M:1;
          vuint32_t BUF52M:1;
          vuint32_t BUF51M:1;
          vuint32_t BUF50M:1;
          vuint32_t BUF49M:1;
          vuint32_t BUF48M:1;
          vuint32_t BUF47M:1;
          vuint32_t BUF46M:1;
          vuint32_t BUF45M:1;
          vuint32_t BUF44M:1;
          vuint32_t BUF43M:1;
          vuint32_t BUF42M:1;
          vuint32_t BUF41M:1;
          vuint32_t BUF40M:1;
          vuint32_t BUF39M:1;
          vuint32_t BUF38M:1;
          vuint32_t BUF37M:1;
          vuint32_t BUF36M:1;
          vuint32_t BUF35M:1;
          vuint32_t BUF34M:1;
          vuint32_t BUF33M:1;
          vuint32_t BUF32M:1;
      } B;
  } IMRH;                 /* Interrupt Masks Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t BUF31M:1;
          vuint32_t BUF30M:1;
          vuint32_t BUF29M:1;
          vuint32_t BUF28M:1;
          vuint32_t BUF27M:1;
          vuint32_t BUF26M:1;
          vuint32_t BUF25M:1;
          vuint32_t BUF24M:1;
          vuint32_t BUF23M:1;
          vuint32_t BUF22M:1;
          vuint32_t BUF21M:1;
          vuint32_t BUF20M:1;
          vuint32_t BUF19M:1;
          vuint32_t BUF18M:1;
          vuint32_t BUF17M:1;
          vuint32_t BUF16M:1;
          vuint32_t BUF15M:1;
          vuint32_t BUF14M:1;
          vuint32_t BUF13M:1;
          vuint32_t BUF12M:1;
          vuint32_t BUF11M:1;
          vuint32_t BUF10M:1;
          vuint32_t BUF09M:1;
          vuint32_t BUF08M:1;
          vuint32_t BUF07M:1;
          vuint32_t BUF06M:1;
          vuint32_t BUF05M:1;
          vuint32_t BUF04M:1;
          vuint32_t BUF03M:1;
          vuint32_t BUF02M:1;
          vuint32_t BUF01M:1;
          vuint32_t BUF00M:1;
      } B;
  } IMRL;                 /* Interrupt Masks Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t BUF63I:1;
          vuint32_t BUF62I:1;
          vuint32_t BUF61I:1;
          vuint32_t BUF60I:1;
          vuint32_t BUF59I:1;
          vuint32_t BUF58I:1;
          vuint32_t BUF57I:1;
          vuint32_t BUF56I:1;
          vuint32_t BUF55I:1;
          vuint32_t BUF54I:1;
          vuint32_t BUF53I:1;
          vuint32_t BUF52I:1;
          vuint32_t BUF51I:1;
          vuint32_t BUF50I:1;
          vuint32_t BUF49I:1;
          vuint32_t BUF48I:1;
          vuint32_t BUF47I:1;
          vuint32_t BUF46I:1;
          vuint32_t BUF45I:1;
          vuint32_t BUF44I:1;
          vuint32_t BUF43I:1;
          vuint32_t BUF42I:1;
          vuint32_t BUF41I:1;
          vuint32_t BUF40I:1;
          vuint32_t BUF39I:1;
          vuint32_t BUF38I:1;
          vuint32_t BUF37I:1;
          vuint32_t BUF36I:1;
          vuint32_t BUF35I:1;
          vuint32_t BUF34I:1;
          vuint32_t BUF33I:1;
          vuint32_t BUF32I:1;
      } B;
  } IFRH;                 /* Interrupt Flag Register */

  union {
      vuint32_t R;
      struct {
          vuint32_t BUF31I:1;
          vuint32_t BUF30I:1;
          vuint32_t BUF29I:1;
          vuint32_t BUF28I:1;
          vuint32_t BUF27I:1;
          vuint32_t BUF26I:1;
          vuint32_t BUF25I:1;
          vuint32_t BUF24I:1;
          vuint32_t BUF23I:1;
          vuint32_t BUF22I:1;
          vuint32_t BUF21I:1;
          vuint32_t BUF20I:1;
          vuint32_t BUF19I:1;
          vuint32_t BUF18I:1;
          vuint32_t BUF17I:1;
          vuint32_t BUF16I:1;
          vuint32_t BUF15I:1;
          vuint32_t BUF14I:1;
          vuint32_t BUF13I:1;
          vuint32_t BUF12I:1;
          vuint32_t BUF11I:1;
          vuint32_t BUF10I:1;
          vuint32_t BUF9I:1;
          vuint32_t BUF8I:1;
          vuint32_t BUF7I:1;
          vuint32_t BUF6I:1;
          vuint32_t BUF5I:1;
          vuint32_t BUF4I:1;
          vuint32_t BUF3I:1;
          vuint32_t BUF2I:1;
          vuint32_t BUF1I:1;
          vuint32_t BUF0I:1;
      } B;
  } IFRL;                 /* Interruput Flag Register */

  //uint32_t FLEXCAN_reserved2[19]; /* {0x0080-0x0034}/0x4 = 0x13 */

  /* Standard Buffer Structure */
  struct FLEXCAN_BUFFER_t BUF[64];

  //uint32_t FLEXCAN_reserved3[256];        /* {0x0880-0x0480}/0x4 = 0x100 */

  union {
      vuint32_t R;
      struct {
          vuint32_t MI:32;
      } B;
  } RXIMR[64];            /* RX Individual Mask Registers */

  };

  /**
 * @brief   CAN received frame.
 * @note    Accessing the frame data as word16 or word32 is not portable because
 *          machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {
    uint16_t TIME;                         /**< @brief Time stamp.         */
  union{
    uint8_t  DLC;                          /**< @brief Data Length C       */
	uint8_t  LENGTH;                       /**< @brief Data length.        */
  };
  uint8_t    RTR;                          /**< @brief Frame type.         */
  union {
    uint8_t  TYPE;                         /**< @brief Id type. STD or XTD */
    uint8_t  IDE;                          /**< @brief Id type. STD or XTD */
  };
  union {
    uint32_t  SID;                         /**< @brief Standard identifier.*/
    uint32_t  EID;                         /**< @brief Extended identifier.*/
	uint32_t  ID;	                       /**< @brief identifier.*/
  };
  union {
    uint8_t   data8[8];                    /**< @brief Frame data.         */
    uint16_t  data16[4];                   /**< @brief Frame data.         */
    uint32_t  data32[2];                   /**< @brief Frame data.         */
  };
} CANRxFrame;

#pragma pack(pop)

// stub typedefs for API compatibility

typedef uint8_t CANDriver;
typedef uint8_t CANConfig;
typedef uint8_t CANTxFrame;
typedef uint8_t canmbx_t;

#endif


#include "xpc56el.h"
#include "can_lld.h"

CANDriver CAND1;
CANConfig can_config_cfg0;

void fill_can_rx_frame(CANRxFrame *target)
{
    // currently, only buffer 5 is configured as Rx buffer
    target->TIME = CAN_0.BUF[5].CS.B.LENGTH;
    target->IDE = CAN_0.BUF[5].CS.B.IDE;
    target->DLC = CAN_0.BUF[5].CS.B.LENGTH;
    if (target->IDE == CAN_IDE_STD)
    {
        target->SID = CAN_0.BUF[5].ID.B.STD_ID;
    }
    else
    {
        target->EID = CAN_0.BUF[5].ID.B.EXT_ID;
    }
}

void can_lld_start(CANDriver *canp, CANConfig *config)
{
    // nop
}

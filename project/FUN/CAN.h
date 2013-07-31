#ifndef _CAN_H
#define _CAN_H



extern void CanBus_Init(void);
extern void Can_Send(CanTxMsg TxMessage);
extern void Can_STD_Send(uint32_t StdId,uint8_t Datalen,uint8_t* pData);





#endif


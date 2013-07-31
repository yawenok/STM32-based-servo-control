#ifndef _uart_H_
#define _uart_H_

#include "stdint.h"
#include "STD.h"

extern void Uart1_Init(uint32_t BaudRate);
extern void Uart2_Init(uint32_t BaudRate);
extern void Uart4_Init(uint32_t BaudRate);
extern void Uart5_Init(uint32_t BaudRate);
extern void USARTx_Send(USART_TypeDef* USARTx, uint8_t Data );
extern void SendDataBuf(USART_TypeDef* USARTx,u8 *Data,u8 len);
extern void SendData(short n1,short n2);
#endif

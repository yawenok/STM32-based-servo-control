#include "STD.h"

void USARTxinteInit(USART_TypeDef* USARTx,uint32_t baudRate)
{
   USART_InitTypeDef    USART_InitStruct;
   USART_ClockInitTypeDef USART_ClockInitStruct ;

   USART_InitStruct.USART_BaudRate=baudRate;
   USART_InitStruct.USART_WordLength=USART_WordLength_8b;
   USART_InitStruct.USART_StopBits=USART_StopBits_1;
   USART_InitStruct.USART_Parity=USART_Parity_No;
   USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
   USART_InitStruct.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
  
   USART_Init(USARTx,&USART_InitStruct) ;

   USART_ClockInitStruct.USART_Clock=USART_Clock_Disable;
   USART_ClockInitStruct.USART_CPOL= USART_CPOL_Low;
   USART_ClockInitStruct.USART_CPHA=USART_CPHA_2Edge;
   USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;
   USART_ClockInit(USARTx,&USART_ClockInitStruct);


   USART_Cmd(USARTx,ENABLE);
   	 	
   USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);
  
}
void Uart1_Init(uint32_t BaudRate)
{
  GPIO_InitTypeDef GPIO_Initstruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);

  /*Enable the USART1 gloabal Interrupt*/ 
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);   
  

  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_9;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA,&GPIO_Initstruct);

  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_10;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_Initstruct);

  
  USARTxinteInit(USART1,BaudRate);	  
}
void Uart2_Init(uint32_t BaudRate)
{
  GPIO_InitTypeDef GPIO_Initstruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_GPIOA,ENABLE);

  /*Enable the USART2 gloabal Interrupt*/ 
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);   
  
  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA,&GPIO_Initstruct);

  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_3;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_Initstruct);
 
  USARTxinteInit(USART2,BaudRate);	

}
void Uart4_Init(uint32_t BaudRate)
{
  GPIO_InitTypeDef GPIO_Initstruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART4|RCC_APB2Periph_GPIOC,ENABLE);

  /*Enable the USART4 gloabal Interrupt*/ 
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);   
  
  
  GPIO_Initstruct.GPIO_Pin = GPIO_Pin_10; 
  GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_Initstruct);

  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_11;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC,&GPIO_Initstruct); 

  USARTxinteInit(UART4,BaudRate);
 
}
void Uart5_Init(uint32_t BaudRate)
{
  GPIO_InitTypeDef GPIO_Initstruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART5|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);

  /*Enable the USART5 gloabal Interrupt*/ 
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);   
  
  
  /*usart5*/
  GPIO_Initstruct.GPIO_Pin=GPIO_Pin_12;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&GPIO_Initstruct);

  GPIO_Initstruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD,&GPIO_Initstruct);
  
  USARTxinteInit(UART5,BaudRate);
}
void USART1_IRQHandler(void)
{
  u16 RxData = 0;

  if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	RxData=USART_ReceiveData(USART1);
    DELWAMING(RxData);
  }

}
void USART2_IRQHandler(void)
{   
  u16 RxData = 0;

  if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
  {
    USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	RxData=USART_ReceiveData(USART2);
	DELWAMING(RxData);
  }

}
void UART4_IRQHandler(void)
{
  u16 RxData=0;

  if(USART_GetITStatus(UART4,USART_IT_RXNE)==SET)
  {
    USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	RxData = USART_ReceiveData(UART4);
	DELWAMING(RxData);
  }

}
void UART5_IRQHandler(void)
{
  u16 RxData=0;
  
  if(USART_GetITStatus(UART5,USART_IT_RXNE)==SET)
  {
    USART_ClearITPendingBit(UART5,USART_IT_RXNE);
	RxData = USART_ReceiveData(UART5); 
	DELWAMING(RxData);
  }
  
}
void USARTx_Send(USART_TypeDef* USARTx , uint8_t Data )
{
    
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	
} 
void SendDataBuf(USART_TypeDef* USARTx,u8 *Data,u8 len)
{
    
   	u8 parity = 0,length = len + 4,count = 0;
	USARTx_Send(USARTx,0XAA);
	USARTx_Send(USARTx,length);
	parity ^= length;
	for(count = 0;count < len; count++)
	{
	 USARTx_Send(USARTx,*(Data+count));
	 parity ^= *(Data+count);
	}
	USARTx_Send(USARTx,parity);
	USARTx_Send(USARTx,0X55);
}
void SendData(short n1,short n2)
{
  BYTE data[5];
  //根据相关信息修改
  data[0] = 0x01;
  data[1] = LBYTE(n1);
  data[2] = HBYTE(n1);
  data[3] = LBYTE(n2);
  data[4] = HBYTE(n2);

  SendDataBuf(UART4,data,5); 
  
}


#include "STD.h"
void ELV_Port_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure; 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);       
   //使能端口A,B,C,D,E,F,G所使用折的APB2外设时钟			     
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   

   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
   GPIO_Init(GPIOC, &GPIO_InitStructure);   

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   
   //关闭电磁阀
   GPIO_ResetBits(GPIOB, GPIO_Pin_1);
   GPIO_ResetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13);		

}

void ElectValve_Action(BYTE ElectValve)
{    
   if(ElectValve&BIT(0))   GPIO_SetBits(GPIOC, GPIO_Pin_5);
   else					   GPIO_ResetBits(GPIOC, GPIO_Pin_5);

   if(ElectValve&BIT(1))   GPIO_SetBits(GPIOC, GPIO_Pin_4);
   else					   GPIO_ResetBits(GPIOC, GPIO_Pin_4);

   if(ElectValve&BIT(2))   GPIO_SetBits(GPIOB, GPIO_Pin_1);
   else					   GPIO_ResetBits(GPIOB, GPIO_Pin_1);

   if(ElectValve&BIT(3))   GPIO_SetBits(GPIOC, GPIO_Pin_13);
   else					   GPIO_ResetBits(GPIOC, GPIO_Pin_13);

}


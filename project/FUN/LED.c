#include"STD.h"


#define LED1_OFF GPIO_SetBits(GPIOC, GPIO_Pin_1);  
#define LED1_ON GPIO_ResetBits(GPIOC, GPIO_Pin_1); 

#define LED2_OFF GPIO_SetBits(GPIOC, GPIO_Pin_2);  
#define LED2_ON GPIO_ResetBits(GPIOC, GPIO_Pin_2);

#define LED3_OFF GPIO_SetBits(GPIOA, GPIO_Pin_4);  
#define LED3_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_4);


void Work_Led1(void)
{
 static char b = 0;
 if(b) 
 {
  LED1_OFF;
 }
 else  
 {
   LED1_ON;
 }
 b = !b;
}
void Work_Led2(void)
{
 static char b = 0;
 if(b) 
 {
  LED2_OFF;
 }
 else  
 {
   LED2_ON;
 }
 b = !b;
}
void Work_Led3(void)
{
 static char b = 0;
 if(b) 
 {
  LED3_OFF;
 }
 else  
 {
   LED3_ON;
 }
 b = !b;
}

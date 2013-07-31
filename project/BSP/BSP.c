#include "STD.h"
void GPIO_Config(void);
void NVIC_Configuration(void);
void RCC_Configuration(void);
void BSP_Init(void);

void GPIO_Config(void)
{

  GPIO_InitTypeDef GPIO_InitStructure; 
  DELWAMING(GPIO_InitStructure);
  //使能端口A,B,C,D,E,F,G所使用折的APB2外设时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC
  						|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF
						|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO, ENABLE);       
}
void RCC_Configuration(void)
{   
  
    ErrorStatus HSEStartUpStatus;
  /* RCC system reset(for debug purpose) */
  
    RCC_DeInit();
  
  /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK1 = HCLK/2 */
     RCC_PCLK1Config(RCC_HCLK_Div2);
	 
	 /* PCLK2 = HCLK */
     RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* Flash 2 wait state */
     FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
     FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
     RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
     RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
     while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }	

    /* Select PLL as system clock source */
     RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
	/* Enable the FSMC Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	/* Enable AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1 , ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 , ENABLE); 
   }
}

void NVIC_Configuration(void)
{

#if defined (VECT_TAB_RAM)
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#elif defined(VECT_TAB_FLASH_IAP)
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 

}

void BSP_Init(void)
{
	RCC_Configuration();
	GPIO_Config();		
	//液晶屏初始化		
	LCD_Init();
	//CAN总线
	CanBus_Init();
	ELV_Port_Init();
	Uart4_Init(38400);
	//驱动硬件初始化
	Hard_Ware_Init();
	//全局变量初始化					    
	G_Var_Init();
	//电机参数CAN
	M_PID_Init();
	NVIC_Configuration();
}




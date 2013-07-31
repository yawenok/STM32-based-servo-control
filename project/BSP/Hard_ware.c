#include "STD.h"

void Driver_Coll_GPIO_Config(void)
{

   GPIO_InitTypeDef GPIO_InitStructure; 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC
  						 |RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE
						 |RCC_APB2Periph_AFIO, ENABLE);       
   //使能端口A,B,C,D,E,F,G所使用折的APB2外设时钟			     
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //口线翻转速度为50MHz

   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //将端口配置为通用推挽输出  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;//PD2.PD3
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
   GPIO_Init(GPIOC, &GPIO_InitStructure);              //初始化外设GPIOD寄存器


   //编码器引脚
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC,&GPIO_InitStructure);

   GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);	  //TIM3

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_InitStructure);  	          //TIM5 	TIM1
   

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD,&GPIO_InitStructure);

   GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);		  //TIM4

   //驱动与非门引脚
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOE,&GPIO_InitStructure);

}
void NVIC_TIMER(void) 
{ 
  NVIC_InitTypeDef NVIC_InitStructure;
  //先占优先级1位(2级),从优先级为3位(8级)
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 	  
  /* Enable the TIM2 gloabal Interrupt*/ 
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 
}
void TIM2_Init(void)
{ 
   /*每1ms发生一次更新事件(进入中断服务程序)。
   RCC_Configuration()的SystemInit()的RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2表明TIM3CLK为72MHz。
   因此，每次进入中断服务程序间隔时间为
   ((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*(1+9)=1ms
   */ 
   TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStruct;	
   //设置TIM2时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   TIM_DeInit(TIM2);
   //自动重装载寄存器周期的值(计数值)
   //累计 TIM_Period个频率后产生一个更新或者中断
   TIM_TimeBaseInitStruct.TIM_Period=9;
   TIM_TimeBaseInitStruct.TIM_Prescaler=7199;
   //采样分频
   TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    
   //向上计数模式
   TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   
   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
   //清除溢出中断标志
   TIM_ClearFlag(TIM2, TIM_FLAG_Update);       
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);	 
   //开启时钟
   TIM_Cmd(TIM2, ENABLE);         
}

//TIM8_PWM
void TIM8_Init(void)
{
  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
   
  //开启TIM8时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 		
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOA Configuration: BKIN pin */   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  TIM_DeInit(TIM8);
  //不分平 72M
  TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   
  //时钟分割       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  //向上计数模式
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD - 1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);
 
  //设置缺省值
  TIM_OCStructInit(&TIM_OCInitStructure);
  //PWM 2输出
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  //输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;                 
  //设置占空比
  //(CCRx/ARR) &(TIM_Plus/TIM_Period)  
  TIM_OCInitStructure.TIM_Pulse = 0x0000;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  //极高比较性
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;        
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;         
 
  //通道1
  TIM_OCInitStructure.TIM_Pulse = 0x0;
  TIM_OC1Init(TIM8,&TIM_OCInitStructure);
  //通道2
  TIM_OCInitStructure.TIM_Pulse = 0x0;
  TIM_OC2Init(TIM8,&TIM_OCInitStructure);
  //通道3
  TIM_OCInitStructure.TIM_Pulse = 0x0;
  TIM_OC3Init(TIM8,&TIM_OCInitStructure);
  //通道4
  TIM_OCInitStructure.TIM_Pulse = 0x0;
  TIM_OC4Init(TIM8,&TIM_OCInitStructure);
 
  //定时器死区
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime =  0x75;	
  //刹车失能
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;			   
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM8,&TIM_BDTRInitStructure);
  //定时器使能
  TIM_Cmd(TIM8,ENABLE);
}

//IWDG独立看门狗
void IWDG_Config(void)
{
	/* 写入0x5555,用于允许狗狗寄存器写入功能 */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	/* 狗狗时钟分频,40K/256=156HZ(6.4ms)*/
	IWDG_SetPrescaler(IWDG_Prescaler_256);
     //喂狗时间 （单位 ms ） = （预分频系数 /4 ） *0.1*RLR （重装载值）
	 //RLR(重装载值) = 喂狗时间(ms)/((预分频系数 /4)*0.1)
	/* 喂狗时间 5s/6.4MS=781 .注意不能大于0xfff*/
	IWDG_SetReload(781);

	/* 喂狗*/
	IWDG_ReloadCounter();

	/* 使能狗狗*/
	IWDG_Enable();
}
void EncoderInit(TIM_TypeDef* TIMx)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  	TIM_ICInitTypeDef  TIM_ICInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5, ENABLE); 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_DeInit(TIMx);
	//NO TIM_Prescaler
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD - 1;	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIMx,TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

 	TIM_ICStructInit(&TIM_ICInitStructure);
	//ICx_FILTER;
	TIM_ICInitStructure.TIM_ICFilter = 0x06;

	TIM_ICInit(TIMx, &TIM_ICInitStructure);

	//Reset counter
	TIMx->CNT = 0;
	TIM_Cmd(TIMx, ENABLE);	
}
void Hard_Ware_Init(void)
{	
	//(一定要注意顺序)
    Driver_Coll_GPIO_Config();
	NVIC_TIMER();
    EncoderInit(TIM3);				//编码器初始化
	EncoderInit(TIM4);
	EncoderInit(TIM5);
	EncoderInit(TIM1);
   	TIM2_Init();                	//TIM2定时器  
	TIM8_Init();
	IWDG_Config();					//独立看门狗初始化
}



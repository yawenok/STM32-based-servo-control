#include"STD.h"


long   Read_A_Rate(void);
long   Read_B_Rate(void);
long   Read_C_Rate(void);
long   Get_Counter_A(void);
long   Get_Counter_B(void);
long   Get_Counter_C(void);

static BOOL  bMeasureTime = FALSE;
static long  nTimeCount = 0;
static long  ASpeed = 0;
static long  BSpeed = 0;
static long  CSpeed = 0;

void TIM2_IRQHandler(void)
{ 
 if(TIM_GetFlagStatus(TIM2 , TIM_FLAG_Update)!= RESET)
 {
	TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); 
	g_SysTime ++;
	nTimeCount ++;
	g_LedTime ++;
	g_S ++;
	if(nTimeCount >= MEASURETIME)
	{
	 bMeasureTime = TRUE;
	 nTimeCount = 0;
	 ASpeed = Get_Counter_A();
	 g_APlus += ASpeed;

	 BSpeed = Get_Counter_B();
	 g_BPlus += BSpeed;

	 CSpeed = Get_Counter_C();
	 g_CPlus += CSpeed;
	}
 }	
}
//work around方法
long Get_Counter_A(void)
{
	static long Lastcounter = 0;
	#if(TIM1_PCB)
	u16 Curcounter = TIM1->CNT;
	#else
	u16 Curcounter = TIM4->CNT;
	#endif

	s32	dCounter =   Curcounter - Lastcounter;
	if(dCounter >= MAX_COUNT)
    {
			dCounter -= ENCODER_TIM_PERIOD;
	}
	else if(dCounter <= -MAX_COUNT)
	{
			dCounter += ENCODER_TIM_PERIOD;
	}
	Lastcounter = Curcounter;
	return (long)dCounter;
}
//work around方法
long Get_Counter_B(void)
{
	static long Lastcounter = 0;
	u16 Curcounter = TIM3->CNT;
	s32	dCounter =   Curcounter - Lastcounter;
	if(dCounter >= MAX_COUNT)
    {
			dCounter -= ENCODER_TIM_PERIOD;
	}
	else if(dCounter <= -MAX_COUNT)
	{
			dCounter += ENCODER_TIM_PERIOD;
	}
	Lastcounter = Curcounter;
	return (long)dCounter;
}
//work around方法
long Get_Counter_C(void)
{
	static long Lastcounter = 0;
	u16 Curcounter = TIM5->CNT;
	s32	dCounter =   Curcounter - Lastcounter;
	if(dCounter >= MAX_COUNT)
    {
			dCounter -= ENCODER_TIM_PERIOD;
	}
	else if(dCounter <= -MAX_COUNT)
	{
			dCounter += ENCODER_TIM_PERIOD;
	}
	Lastcounter = Curcounter;
	return (long)dCounter;
}
long Read_A_Rate(void)
{
	return ASpeed;
}
long Read_B_Rate(void)
{
	return BSpeed;
}
long Read_C_Rate(void)
{
	return CSpeed;
}
BOOL IsLEDTime(void)
{
 if(g_LedTime >= LEDTIME) 
 {				   
  g_LedTime = 0;
  return TRUE;
 }
 return FALSE;
}
BOOL Is_Sampling_Time(void)
{
  if(bMeasureTime)
  {
   bMeasureTime = FALSE;
   return TRUE;
  }
  return bMeasureTime;
}


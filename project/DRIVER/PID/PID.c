#include"STD.h"
#include"PID.h"
//PID参数初始化
void PID_Init(PID *pPIDDATA,double P,double I,double D)
{
 pPIDDATA->nSet_Point = 0.0f; 	
 pPIDDATA->nOutput = 0.0f;					
 pPIDDATA->nPrev_Error = 0.0f;		
 pPIDDATA->nLast_Error = 0.0f; 
 
 pPIDDATA->Proportion = P; 
 pPIDDATA->Integral = I; 		
 pPIDDATA->Derivative = D;
}

//增量式PID控制
long IncPIDCalc(PID *pPIDDATA,long goal,long FeedBack)
{
 
 register long nError = 0,nIncpid = 0; 
 pPIDDATA->nSet_Point = goal;
 //当前误差 
 nError = pPIDDATA->nSet_Point - FeedBack; 
 //增量计算 
 nIncpid = pPIDDATA->Proportion    * nError                    //E[k]项 
            - pPIDDATA->Integral   * pPIDDATA->nLast_Error     //E[k－1]项 
            + pPIDDATA->Derivative * pPIDDATA->nPrev_Error;    //E[k－2]项 
 //存储误差，用于下次计算 
 pPIDDATA->nPrev_Error = pPIDDATA->nLast_Error; 
 pPIDDATA->nLast_Error = nError;
 //返回增量值 
 return(long)(nIncpid);
 
}
//位置式PID控制设计 
long LocPIDCalc(PID *pPIDDATA,long goal,long FeedBack) 
{ 

  register long  dError = 0,iError = 0; 
  pPIDDATA->nSet_Point = goal;
  iError = pPIDDATA->nSet_Point - FeedBack;            //偏差 
  pPIDDATA->nSum_Error += iError;                      //积分 
  dError = iError - pPIDDATA->nLast_Error;             //微分 
  pPIDDATA->nLast_Error = iError; 

  return (long)(pPIDDATA->Proportion * iError          //比例项 
         + pPIDDATA->Integral * pPIDDATA->nSum_Error   //积分项 
         + pPIDDATA->Derivative * dError);             //微分

} 
short  Motor_LimitValue(long nLimitValue)
{
  nLimitValue = fabs( nLimitValue ) < MAX_OUT_PUT ? nLimitValue 
  	                   : (nLimitValue < 0 ? -MAX_OUT_PUT : MAX_OUT_PUT ) ;
  				 
  return (short)nLimitValue;
}
short  LimitValue(long nLimitValue,long nMax)
{
  nLimitValue = fabs( nLimitValue ) < nMax ? nLimitValue 
  	                   : (nLimitValue < 0 ? -nMax : nMax ) ;
  				 
  return (short)nLimitValue;
}
void   PID_Output(int Output,int nID)
{
 if(Output < -PWM_LOW)	
 {
  if(Output < -PWM_TOP) Output = -PWM_TOP;
  switch(nID)
  {
   case 1:
    MOTOR_A_GO_BACK;
    TIM_SetCompare1(TIM8,-Output);
   break;
   case 2:
    MOTOR_B_GO_BACK;
    TIM_SetCompare2(TIM8,-Output);
   break;
   case 3:
    MOTOR_C_GO_BACK;
    TIM_SetCompare3(TIM8,-Output);
   break;
   case 4:
    MOTOR_D_GO_BACK;
    TIM_SetCompare4(TIM8,-Output);
   break;
  }		
 }	
 else if(Output > PWM_LOW)
 {
  if(Output > PWM_TOP) Output = PWM_TOP;
  switch(nID)
  {
   case 1:
    MOTOR_A_GO_AHEAD;
    TIM_SetCompare1(TIM8,Output);
   break;
   case 2:
    MOTOR_B_GO_AHEAD;
    TIM_SetCompare2(TIM8,Output);
   break;
   case 3:
    MOTOR_C_GO_AHEAD;
    TIM_SetCompare3(TIM8,Output);
   break;
   case 4:
    MOTOR_D_GO_AHEAD;
    TIM_SetCompare4(TIM8,Output);
   break;
  }	
 }
 else 
 {
  switch(nID)
  {
   case 1:
	MOTOR_A_STOP;
	break;
   case 2:
	MOTOR_B_STOP;
	break;
   case 3:
	MOTOR_C_STOP;
   break;
   case 4:
	MOTOR_D_STOP;
   break;
	default:
   break;
  }
 }
}
void PWM_TESTA(unsigned short u1,unsigned short u2,unsigned short u3)
{
  MOTOR_B_GO_BACK;
  TIM_SetCompare2(TIM8,u1);
  MOTOR_C_GO_BACK;
  TIM_SetCompare3(TIM8,u2);
  MOTOR_D_GO_BACK;
  TIM_SetCompare4(TIM8,u3);
}
void PWM_TESTB(unsigned short u1,unsigned short u2,unsigned short u3)
{
  MOTOR_B_GO_AHEAD;
  TIM_SetCompare2(TIM8,u1);
  MOTOR_C_GO_AHEAD;
  TIM_SetCompare3(TIM8,u2);
  MOTOR_D_GO_AHEAD;
  TIM_SetCompare4(TIM8,u3);
}




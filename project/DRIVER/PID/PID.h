#ifndef _PID_H
#define _PID_H

//PID参数设计						
typedef struct tagPID
{				
	  long nSum_Error;         //  误差累计
	  long nSet_Point;         //  设定目标 
	  long nOutput;			   //  PID运算输出值	
	 					
      double Proportion;       //  比例常数 	 
	  double Integral;         //  积分常数 	 		
      double Derivative;       //  微分常数  
	 
	  long nPrev_Error;        //  当前误差			
      long nLast_Error;        //  上次误差	
}PID,*pPID;
//PID参数初始化
extern void   PID_Init(PID *pPIDDATA,double P,double I,double D);
//增量式PID控制 
extern long   IncPIDCalc(PID *pPIDDATA,long goal,long FeedBack);
//位置式PID控制设计 
extern long   LocPIDCalc(PID *pPIDDATA,long goal,long FeedBack); 
//计算限制
extern short  Motor_LimitValue(long nLimitValue);
extern short  LimitValue(long nLimitValue,long nMax);

extern void   PID_Output(int Output,int nID);
extern void   PWM_TESTA(unsigned short u1,unsigned short u2,unsigned short u3);
extern void   PWM_TESTB(unsigned short u1,unsigned short u2,unsigned short u3);
#endif


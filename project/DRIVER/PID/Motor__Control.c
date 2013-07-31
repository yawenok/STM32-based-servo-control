#include "STD.h"
#include "PID.h"


void M_PID_Init(void);
void AM_Control(int target);
void BM_Control(int target);
void CM_Control(int target);
void AM_DW_Control(long target);
void BM_DW_Control(long target);
void CM_DW_Control(long target);


void M_PID_Init(void)
{
  //速度式控制
  PID_Init(&g_PID_A,4.5f,0.25f,0.25f);
  PID_Init(&g_PID_B,3.5f,0.25f,0.25f);
  PID_Init(&g_PID_C,2.5f,0.25f,0.25f);

  //限位式控制(I 要为 0)
  PID_Init(&g_PID_DW_A,0.005f,0.0f,0.35f);
  PID_Init(&g_PID_DW_B,0.005f,0.0f,0.35f);
  PID_Init(&g_PID_DW_C,0.005f,0.0f,0.35f);

}
//速度式控制
void AM_Control(int target)
{
  g_PID_A.nOutput += IncPIDCalc(&g_PID_A,target,-Read_A_Rate());
  g_PID_A.nOutput = LimitValue(g_PID_A.nOutput,PWM_TOP);
  PID_Output(g_PID_A.nOutput,2);
}
void BM_Control(int target)
{
  g_PID_B.nOutput += IncPIDCalc(&g_PID_B,target,-Read_B_Rate());
  g_PID_B.nOutput = LimitValue(g_PID_B.nOutput,PWM_TOP);
  PID_Output(g_PID_B.nOutput,3);
}
void CM_Control(int target)
{
  g_PID_C.nOutput += IncPIDCalc(&g_PID_C,target,Read_B_Rate());
  g_PID_C.nOutput = LimitValue(g_PID_C.nOutput,PWM_TOP);
  PID_Output(-g_PID_C.nOutput,4);
} 
//限位式控制
void AM_DW_Control(long target)
{
  g_PID_DW_A.nOutput = LocPIDCalc(&g_PID_DW_A,target,g_APlus);
  AM_Control(-LimitValue(g_PID_DW_A.nOutput,200));
}
void BM_DW_Control(long target)
{
  g_PID_DW_B.nOutput = LocPIDCalc(&g_PID_DW_B,target,g_BPlus);
  BM_Control(-LimitValue(g_PID_DW_B.nOutput,200));
}
void CM_DW_Control(long target)
{
  g_PID_DW_C.nOutput = LocPIDCalc(&g_PID_DW_C,target,g_CPlus);
  CM_Control(-LimitValue(g_PID_DW_C.nOutput,200));
} 














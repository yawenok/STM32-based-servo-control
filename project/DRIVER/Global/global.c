#include"STD.h"




SPEED         g_Speed = { 0 };
PID           g_PID_A = { 0 };
PID           g_PID_B = { 0 };
PID           g_PID_C = { 0 };


PID           g_PID_DW_A = { 0 };
PID           g_PID_DW_B = { 0 };
PID           g_PID_DW_C = { 0 };


volatile long g_SysTime = 0;
volatile long g_LedTime = 0;
volatile long g_S = 0;
volatile long g_APlus = 0;
volatile long g_BPlus = 0;   
volatile long g_CPlus = 0;   
   
void G_Var_Init(void)
{
 memset(&g_PID_A,0,sizeof(PID));
 memset(&g_PID_B,0,sizeof(PID));
 memset(&g_PID_C,0,sizeof(PID));


 memset(&g_PID_DW_A,0,sizeof(PID));
 memset(&g_PID_DW_B,0,sizeof(PID));
 memset(&g_PID_DW_C,0,sizeof(PID));	

 g_Speed.A = 0;
 g_Speed.B = 0;
 g_Speed.C = 0;
 g_Speed.Mode = 0XFF;
 g_Speed.Elecmd = 0X00;

}


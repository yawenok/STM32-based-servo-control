#ifndef _GLOBAL_H
#define _GLOBAL_H




extern SPEED         g_Speed;
extern PID           g_PID_A;
extern PID           g_PID_B;
extern PID           g_PID_C;


extern PID           g_PID_DW_A;
extern PID           g_PID_DW_B;
extern PID           g_PID_DW_C;


extern volatile long g_SysTime;
extern volatile long g_LedTime;
extern volatile long g_S;
extern volatile long g_APlus;
extern volatile long g_BPlus;   
extern volatile long g_CPlus;
   
extern void          G_Var_Init(void);

#endif


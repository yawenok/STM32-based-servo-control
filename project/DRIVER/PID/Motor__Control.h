#ifndef _MOTOR__CONTROL_H_
#define _MOTOR__CONTROL_H_

extern void M_PID_Init(void);
//速度式控制
extern void AM_Control(int target);
extern void BM_Control(int target);
extern void CM_Control(int target);
//限位式控制
extern void AM_DW_Control(long target);
extern void BM_DW_Control(long target);
extern void CM_DW_Control(long target);

#endif 








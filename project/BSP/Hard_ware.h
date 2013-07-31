#ifndef __HARDWARE_H
#define __HARDWARE_H
#include <stm32f10x_lib.h>	


#define MOTOR_A_GO_BACK  		{GPIO_ResetBits(GPIOE,GPIO_Pin_0);GPIO_SetBits(GPIOE,GPIO_Pin_2);}
#define MOTOR_A_GO_AHEAD  		{GPIO_SetBits(GPIOE,GPIO_Pin_0);GPIO_ResetBits(GPIOE,GPIO_Pin_2);}
#define MOTOR_A_STOP			{GPIO_ResetBits(GPIOE,GPIO_Pin_0);GPIO_ResetBits(GPIOE,GPIO_Pin_2);}

#define MOTOR_B_GO_BACK  		{GPIO_ResetBits(GPIOE,GPIO_Pin_0);GPIO_SetBits(GPIOE,GPIO_Pin_2);}
#define MOTOR_B_GO_AHEAD  		{GPIO_SetBits(GPIOE,GPIO_Pin_0);GPIO_ResetBits(GPIOE,GPIO_Pin_2);}
#define MOTOR_B_STOP			{GPIO_ResetBits(GPIOE,GPIO_Pin_0);GPIO_ResetBits(GPIOE,GPIO_Pin_2);}

#define MOTOR_C_GO_BACK  		{GPIO_ResetBits(GPIOE,GPIO_Pin_3);GPIO_SetBits(GPIOE,GPIO_Pin_4);}
#define MOTOR_C_GO_AHEAD  		{GPIO_SetBits(GPIOE,GPIO_Pin_3);GPIO_ResetBits(GPIOE,GPIO_Pin_4);}
#define MOTOR_C_STOP			{GPIO_ResetBits(GPIOE,GPIO_Pin_3);GPIO_ResetBits(GPIOE,GPIO_Pin_4);}

#define MOTOR_D_GO_BACK  		{GPIO_ResetBits(GPIOE,GPIO_Pin_5);GPIO_SetBits(GPIOE,GPIO_Pin_6);}
#define MOTOR_D_GO_AHEAD  		{GPIO_SetBits(GPIOE,GPIO_Pin_5);GPIO_ResetBits(GPIOE,GPIO_Pin_6);}
#define MOTOR_D_STOP			{GPIO_ResetBits(GPIOE,GPIO_Pin_5);GPIO_ResetBits(GPIOE,GPIO_Pin_6);}

extern void Hard_Ware_Init(void);

#endif










/*=========================================================*
*   声明库说明：SP027 段显液晶模块驱动库函数               *
*   版本：1.0                                                      *
*   作者：w.j                                                      *
*   创建日期：2009/1/18                                    *
* -------------------------------------------------------- *
*  [硬件说明]                                              *
*     			VSS     CLK      DI    VDD                 *
*              电源地  时钟信号  数据  电源正              *
*  注意: 应在写完一次数据后在末尾加上一个时钟跳变沿(Paulse)*
*   处理器：                                                            *
*   系统时钟：                                                        *
* ---------------------------------------------------------------- *
*  [使用说明]                                              *
*=========================================================*/

/*==================*
* 头 文 件 配 置 区 *
*==================*/
#include "stm32f10x.h" 
#include "stm32f10x_gpio.h"
#include "math.h"
#include "Hard_ware.h"
/*==================*
*   常 数 宏 定 义  *
*==================*/
#define   DI0          GPIO_WriteBit(GPIOD,GPIO_Pin_3,Bit_RESET); //P2
#define   DI1          GPIO_WriteBit(GPIOD,GPIO_Pin_3,Bit_SET);
#define   CLK0         GPIO_WriteBit(GPIOD, GPIO_Pin_2,Bit_RESET);//P3
#define   CLK1         GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_SET);

#define   Wrt1         {CLK0;Delay(4);CLK1;Delay(4);DI1;Delay(4);DI0;Delay(4);}              //写数据"1"
#define   Wrt0         {CLK0;Delay(4);CLK1;Delay(4);DI0;Delay(4);DI1;Delay(4);}              //写数据"0" 
#define   Paulse       {CLK0;Delay(3);CLK1;Delay(3);}                      //一个跳变沿
#define   GO           0x01
#define   Ready        0x02

/*==================*
*  模块结构体定义区 *
*==================*/

/*==================*
*   函 数 声 明 区  *
*==================*/
void Display_Onechar(uint8_t Data);

/*==================*
*   模块函数声明区  *
*==================*/
void CLS(void);
void DisplayINTNum_SP027(int32_t Number);
void DisplayFloatNum_SP027(float Num);

/*==================*
*   模块变量声明区  *
*==================*/
const uint8_t SP027DisplayCode[] = {0x09,0xcf,0x91,0x85,0x47,0x25,0x21,0x8f,0x01,0x05,
                         	 0x03,0x61,0x39,0xc1,0x31,0x33,0x29,0x43,0x7b,0xc9,
						 	 0x79,0xe1,0x13,0xf3,0x49,0xf7,0xfd,0xff};
							 /*{0~F,G,H,I,J,L,O,P,r,U,_,-}*/ 
						 
/*==================*
*   全局变量声明区  *
*==================*/

/*=========================================================*
*   函数功能：清屏函数                                     *
*   输    入：    无                                       *
*   输    出：    无                                       *
* -------------------------------------------------------- *
*  [使用说明]                                              *
*=========================================================*/
void CLS(void)
{
   uint8_t k = 0; 
   for(k=0;k<41;k++)
   {
      Wrt0;
   }	   
}                       

/*=========================================================*
*   函数功能：十进制数据显示函数                           *
*   输    入：要显示的数(long)                             *
*   输    出：    无                                       *
* -------------------------------------------------------- *
*  [使用说明]                                              *
*=========================================================*/
void DisplayINTNum_SP027(int32_t Number)
{	
	s8 lcv_Counter = 0;
    //uint8_t cNonce_BIT_Number = 0;
	uint8_t tmpNumber[5] = {0};
	uint8_t isNegative = FALSE;

	if(Number<0)
	{
		isNegative = TRUE;
	}
	Number = fabs(Number);
	CLS();	//清屏
	
	do
	{   
		if(lcv_Counter+isNegative>=5)
		{
			tmpNumber[0] &=~(1<<0);	//误操作
			break;
		}
		tmpNumber[lcv_Counter] = SP027DisplayCode[Number%10];   //计算当前位上的数字Number%10
		Number=Number/10;    //计算比当前位更高位上的数字
		lcv_Counter ++;
	}while(Number);
	if(isNegative)
	{
		tmpNumber[lcv_Counter]=0xF7;	//负号
		lcv_Counter++;
	}
	while(lcv_Counter--)
	{
		Display_Onechar(tmpNumber[lcv_Counter]);	//显示
	}
    Paulse;   
}    

/*=========================================================*
*   函数功能：Float数据显示函数                            *
*   输    入：要显示的数(float)                            *
*   输    出：    无                                       *
* -------------------------------------------------------- *
*  [使用说明]                                              *
*=========================================================*/
void DisplayFloatNum_SP027(float Num)
{
    s8 lcv_Counter = 0;
    //uint8_t cNonce_BIT_Number = 0;
	uint8_t tmpNumber[5] = {0};
	s32 Number = 0;
	uint8_t isNegative = FALSE;
	
	if(Num<0)
	{
		isNegative = TRUE;
	}
	Number =fabs((s32)(Num*100));
	CLS();	//清屏
	
	do
	{   
		if(lcv_Counter+isNegative>=5)
		{
			tmpNumber[0] &=~(1<<0);	//误操作
			break;
		}
		tmpNumber[lcv_Counter] = SP027DisplayCode[Number%10];   //计算当前位上的数字Number%10
		Number=Number/10;    //计算比当前位更高位上的数字
		lcv_Counter ++;
	}while(Number||(lcv_Counter<=2));
	tmpNumber[2] &=~(1<<0);	//小数点
	if(isNegative)
	{
		tmpNumber[lcv_Counter]=0xF7;	//负号
		lcv_Counter++;
	}
	while(lcv_Counter--)
	{
		Display_Onechar(tmpNumber[lcv_Counter]);	//显示
	}
    Paulse;
}    

/*=========================================================*
*   函数功能：写单个数字                                   *
*   输    入：要显示的数(UINT8)                            *
*   输    出：    无                                       *
* -------------------------------------------------------- *
*  [使用说明]                                              *
*=========================================================*/
void Display_Onechar(uint8_t Data)
{
   uint8_t CharLength = 0;
   uint8_t NumTemp = 0;
   
   for (CharLength=0;CharLength<8;CharLength++)
   {
	  NumTemp = ((Data>>(7-CharLength))&0x01);
	  if (NumTemp == 0)
	  {
		 Wrt1;
	  }
	  else
	  {
	     Wrt0;
	  }	  
   }         
}


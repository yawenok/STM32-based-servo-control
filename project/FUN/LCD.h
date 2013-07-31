#ifndef LCD_H
#define LCD_H
#include"stdint.h"

#define DATAOUT(x)      GPIOA->ODR=(GPIOA->ODR&0xffffff00)|(x&0xff);	  

#define RED	            0XF800
#define GREEN           0X07E0
#define BLUE            0X001F  
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define BLACK           0
#define WHITE           0XFFFF  
#define YELLOW          0XFFF0

extern void LCD_Init(void);
extern void Set_Font_Color(u16 Color);
extern void Set_Back_Color(u16 Color);
extern void TFT_Clear(u8 x,u16 y,u8 len,u16 wid);
extern void TFT_ShowString(u8 x,u16 y,const u8 *p);
extern void TFT_ShowNum(u8 x,u16 y,long num);
extern void TFT_ShowFloat(u8 x,u16 y,float fnum);
extern void TFT_ShowBmp(u8 x,u16 y,u8 lenth,u16 wide,const u8 *p);
extern void TFT_DrawLine(u8 x1, u16 y1, u8 x2, u16 y2);

#endif


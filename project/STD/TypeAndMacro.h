#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_


/*=========================================================*
*   静态宏定义                                             *
*=========================================================*/
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef PI
#define PI 3.1415926
#endif
#ifndef NULL
#define NULL 0
#endif
//周期映射到[0，_MAX]
#define MOD_GAME( VALUE, MAX )  ( fmodf( ( float ) ( fmodf( ( float )(VALUE), ( float ) (MAX) )+ (MAX) ),  ( float )(MAX) ))	
#define DELWAMING(x)            { x = x ;}


/*=========================================================*
*   数据类型定义                                           *
*=========================================================*/

typedef unsigned short uint16;
typedef unsigned short UINT;
typedef unsigned short uint;
typedef unsigned short UINT16;
typedef unsigned short WORD;
typedef unsigned short word;
typedef short          int16;
typedef short          INT16;
typedef int            INT;
typedef unsigned long  uint32;
typedef unsigned long  UINT32;
typedef unsigned long  DWORD;
typedef unsigned long  dword;
typedef long           int32;
typedef long           INT32;

typedef signed   char int8;
typedef signed   char INT8;
typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef unsigned char uint8;
typedef unsigned char BOOL;


/*=========================================================*
*   结构体定义                                             *
*=========================================================*/

typedef struct tagSpeed
{
   short A;
   short B;
   short C;
   BYTE  Mode;
   BYTE  Elecmd;
}SPEED,*pSPEED;



/*=========================================================*
*  功能宏定义                                            *
*=========================================================*/


#ifndef BIT
 #define BIT(x)         (1<<x)
#endif

#define LBYTE(w)        ((BYTE)((WORD)(w) & 0xff ))
#define HBYTE(w)        ((BYTE)((WORD)(w) >> 8 ))


/*=========================================================*
*  参数宏定义                                              *
*=========================================================*/
#define PWM_PERIOD          6000		 
#define PWM_TOP             5000
#define PWM_LOW             0
#define MAX_OUT_PUT         30000

#define MEASURETIME         1    
#define LEDTIME             100

#define MAX_COUNT		    1200
#define ENCODER_TIM_PERIOD  (MAX_COUNT*3)


#endif


#include"STD.h"


int main(void)
{
	BSP_Init();
   	while(TRUE)						   
	{ 	
      //喂狗
      IWDG_ReloadCounter(); 
	  if(Is_Sampling_Time())
	  {
	    //AM_Control(g_Speed.A);
		AM_DW_Control(10000);
        BM_Control(g_Speed.B);
        CM_Control(g_Speed.C);
	  }
	  //通信保护
	  if(g_S > 100)      g_Speed.A = g_Speed.B = g_Speed.C = 0;
	  if(IsLEDTime())	 Work_Led1(); 
	  
	  ElectValve_Action(g_Speed.Elecmd); 
  	}
}










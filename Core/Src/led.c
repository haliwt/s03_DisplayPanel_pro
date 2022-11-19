#include "led.h"
#include "run.h"
#include "lcd.h"
#include "delay.h"
void (*panel_led_fun)(void);


/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Breath_Led(void)
{
//    TURN_ON_LED() ;
//	delay_ms(500);
//	TURN_OFF_LED() ;
//	delay_ms(500);

	static uint32_t k;
   
    k++;

	if(k<40000){

	POWER_ON_LED() ;//LED_POWER_ON();



	}
          

	if(k>40000 && k <80000){

	   POWER_OFF_LED() ; //LED_POWER_OFF();

	}
	if(k>80000 && k< 120000){

	  POWER_TOGGLE();


	}

	if(k>120000){

        k=0;
	}


}
/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Lcd_PowerOn_Fun(void)
{
    POWER_ON_LED()	;//key of led turn On
    LED_MODEL_ON();
	LCD_BACK_LIGHT_ON();

}


void Lcd_PowerOff_Fun(void)
{

	POWER_OFF_LED()  ;
	LED_MODEL_OFF();
	LCD_BACK_LIGHT_OFF();



}


/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Panel_Led_OnOff_Function(void)
{
	
	 #if 0
	  if(run_t.gAi==0){
//		  AI_LED_OnOff(0)  ;
//        DRY_LED_OnOff(0);
//        STER_LED_OnOff(0);
	  }
	  else{
	  	  if(run_t.gFan_RunContinue==1)
	  	  	// AI_LED_OnOff(0)  ;
	  	  else
		    AI_LED_OnOff(1)  ;

	  }
	  
     if(run_t.gAi == 1){ //WT.EDIT .2022.09.01
		  if(run_t.gDry==0 )
			  DRY_LED_OnOff(0);
		  else 
			 DRY_LED_OnOff(1);
		 
		  if(run_t.gPlasma==0)
			STER_LED_OnOff(0); 
		  else
			 STER_LED_OnOff(1); 
	 }


    if(run_t.gWifi == 1){

         LED_WIFI_OFF();

	}
	 
 #endif 
}

/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void))
{

	 panel_led_fun= panelledHandler;
}


#include "run.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "display.h"
#include "lcd.h"

RUN_T run_t;

uint8_t tim3,tim14;
void Power_Off(void);





/**********************************************************************
*
*Functin Name: void Power_Off(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Power_Off(void)
{
    	 if(run_t.gPower_On ==0){

         run_t.gPower_On =0xff;
    
        
         run_t.gModel =0;
        
         run_t.gPlasma=0;
         run_t.gDry=0;
        
        run_t.gTimer_Cmd=0; //timer of command "1"->timer is start
        
        run_t.gTemperature_timer_flag=0;
    
        run_t.gDht11_flag=0; //the first power on display "00"
        
    

          run_t.gTimer_fan_counter=0;
          Lcd_PowerOff_Fun();
				
				
		}
		Breath_Led();
        if(run_t.gFan_RunContinue==1){

		      if(run_t.fan_off_60s > 60){
                run_t.gFan_RunContinue=0;
                
              }
			  else{

			   
							
           }

		 }
}



/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function call back function
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0;
    
   if(htim->Instance==TIM3){
    
    tm0++;  //10ms
	
    tim3++;
    lcd_t.gTimer_wifi_500ms++;
	lcd_t.gTimer_fan_10ms++;
	run_t.gTimer_numbers_one_two_blink++;

    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
		run_t.fan_off_60s++;
     
		run_t.dispTime_seconds++;
	    if(run_t.dispTime_seconds >59){//60s ->1 minute 
	      run_t.dispTime_seconds=0;
		  run_t.gTimer_minute_Counter ++;
		 
		 }
     

   }
	
   }


}
	

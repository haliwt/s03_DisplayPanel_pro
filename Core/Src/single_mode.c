#include "single_mode.h"
#include "run.h"
#include "display.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "key.h"
#include "lcd.h"



uint8_t decade_hour;
uint8_t unit_hour;

void (*single_ai_fun)(uint8_t cmd);
void (*single_add_fun)(void);
void (*single_buzzer_fun)(void);
void (*sendAi_usart_fun)(uint8_t senddat);


static void RunKeyOrder_Handler(void);

/*******************************************************************************
	 * 
	 * Function Name :void Single_RunMode(void)
	 * Function :main in single run process
	 * Input Reference:No
	 * Return Reference :NO
	 *
*******************************************************************************/
void Scan_KeyModel(void)
{
   
     static uint8_t keypower;
      //   decade_hour,unit_hour;
        if(POWER_KEY_VALUE() ==KEY_DOWN ){ //power on KEY
          HAL_Delay(20);
		 while(POWER_KEY_VALUE()  ==KEY_DOWN);
		  single_buzzer_fun();//SendData_Buzzer();

             run_t.wifiCmd[0]=0;//rx wifi command 
			  if(run_t.gPower_On == 0 || run_t.gPower_On == 0xff){
			  	  run_t.gTimes_hours_temp=12;
	              run_t.gPower_On=1;
	          
				  run_t.power_key =1;
				  run_t.gFan_RunContinue=0;
				 
				  run_t.gAi =0; //WT.EDIT 2022.09.01
				  run_t.gPlasma=0;
				  run_t.gDry =0;
				  run_t.gWifi =0;
				   SendData_PowerOff(1);
				  
	             
			  }
			  else{
                  

					run_t.power_key =2;
				    run_t.gFan_RunContinue=1;
		            run_t.gPower_On=0;
					run_t.fan_off_60s =0;
					SendData_PowerOff(0);
					
		           
              }

     }
     else if(MODE_KEY_VALUE()==KEY_DOWN){ //Mode key 
	 	    
	     	 HAL_Delay(20);
	         while(MODE_KEY_VALUE()==KEY_DOWN);
	 	  
			if(run_t.gPower_On ==1){
				
			run_t.gKeyTimer_mode = run_t.gKeyTimer_mode ^ 0x01; //the same is "0",and differenct is "1"

			if(run_t.gKeyTimer_mode == 1){ //timing of function.
                
				run_t.gTimer_key_5s =0;
				run_t.temperature_flag =0;
		    }
            else{ //temperature of function adjust ref .
               run_t.gKeyTimer_mode=0;
			 
			   run_t.temperature_flag =1;
			 
            }
			single_buzzer_fun();//SendData_Buzzer();
           
	     }
		
		  
     }
     else if(DEC_KEY_VALUE()==KEY_DOWN){ //"-" KEY
	 	
		  HAL_Delay(20);
        while(DEC_KEY_VALUE()==KEY_DOWN);
		if(run_t.gPower_On ==1){
		 if(run_t.gKeyTimer_mode==1){//times, is timer is 
                    
			 	    run_t.dispTime_hours--;
					

					 if(run_t.dispTime_hours <0){
                           run_t.dispTime_hours=24;

					 }

					 decade_hour = run_t.dispTime_hours / 10 %10;
					 unit_hour = run_t.dispTime_hours % 10; //
                       
					 lcdNumber5_Low[decade_hour];  //
					lcdNumber5_High[decade_hour];
					
					lcdNumber6_Low[unit_hour];
					lcdNumber6_High[unit_hour];
						 
					run_t.gTimer_key_5s=0;//run_t.gTimer_5s_start =1; //timer is 5s start be pressed key 
				    run_t.temperature_flag =0;
		}
		else{ //setup temperature value 
                    
					 run_t.temperature_flag =1;
				    //setup temperature of value,minimum 20,maximum 40
					 run_t.gTemperature --;
					 if(run_t.gTemperature<20) run_t.gTemperature=40;
					  
					  
					   if(run_t.gTemperature >20)run_t.temperature_set_flag = 1;//run_t.gTemperature_timer_flag =1;
			            else run_t.temperature_set_flag=0;
						
					
					    run_t.gTimer_key_4s=0;
				        run_t.gTimer_key_60s=0;
						run_t.gTimer_set_temperature=0;
			}
              single_buzzer_fun();//SendData_Buzzer();
		}	
		
             
     }  
	else if(ADD_KEY_VALUE()==KEY_DOWN){ //"+" KEY
	 	 HAL_Delay(20);

		  while(ADD_KEY_VALUE()==KEY_DOWN);
		  	 
	     	  if(run_t.gPower_On ==1){
			 	  
				if(run_t.gKeyTimer_mode==1){ //timing of timers is times 
                     run_t.gTimer_key_5s =0;
				
					 run_t.dispTime_hours++;
				     
				    if(run_t.dispTime_hours >24){
						run_t.dispTime_hours=0;
					}

					decade_hour = run_t.dispTime_hours / 10 %10;
					 unit_hour = run_t.dispTime_hours % 10; //
					 
					run_t.temperature_flag =0;
					run_t.gTimer_key_5s =0;
                    
					lcdNumber5_Low[decade_hour];  //
					lcdNumber5_High[decade_hour];
					
					lcdNumber6_Low[unit_hour];
					lcdNumber6_High[unit_hour];
					
                    
                    
				 }
				 else{ //temperature of value
				      run_t.temperature_flag =1;
					  //setup temperature minimum 20, maximum 40
				     run_t.gTemperature ++;
                     if(run_t.gTemperature < 20)run_t.gTemperature= 20;
					 else if(run_t.gTemperature >40) run_t.gTemperature=20;
                     
                      
				     if(run_t.gTemperature >20)run_t.temperature_set_flag = 1;//run_t.gTemperature_timer_flag =1;
			            else run_t.temperature_set_flag=0;

			
				        run_t.gTimer_key_4s=0;
						run_t.gTimer_key_60s=0;
						run_t.gTimer_set_temperature=0;
					
				 }
				single_buzzer_fun();//SendData_Buzzer();
            }
			
	}
	
    
	 
  }

static void RunKeyOrder_Handler(void)
{
	
    if(run_t.gPower_On ==1 ){


	 Lcd_PowerOn_Fun();
	 DisplayPanel_Ref_Handler();
    
         
	 }
	 
}

/******************************************************************************
*
*Function Name:void Single_RunCmd(void)
*Funcion: handle of receive by usart data
*
*
******************************************************************************/
void RunCommand_Handler(void)
{
   if(run_t.gPower_On ==1 ){
        Decode_Function();
		RunKeyOrder_Handler();
   }
  
    
   if(run_t.gWifi ==0) //wifi function turn 0n 
        Wifi_Receive_Cmd(run_t.wifiCmd[0]);

    if(run_t.gPower_On ==0 || run_t.gPower_On == 0xff){
	 	
	      Breath_Led();
		  Power_Off();
     }
}

/**********************************************************************************************************
**
*Function Name:static void notifyStatusToHost(uint8_t lightNum,uint8_t filterNum,uint8_t unionNum)
*Function : 
*Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
*Return Ref:NO
*
*********************************************************************************************************/
void Decode_Function(void)
{
   if(run_t.decodeFlag ==1){
   
       run_t.decodeFlag =0;
       
       Display_DHT11_Value();
    }
}

/****************************************************************
 * 
 * Function Name:
 * Function :function of pointer 
 * 
 * 
****************************************************************/
void Single_Add_RunCmd(void(*addHandler)(void))
{
    single_add_fun = addHandler;   

}

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void))
{
	single_buzzer_fun = buzzerHandler;

}
void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat))
{
    sendAi_usart_fun = sendaiHandler;

}




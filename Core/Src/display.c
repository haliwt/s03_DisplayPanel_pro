#include "display.h"
#include "cmd_link.h"
#include "run.h"
#include "key.h"
#include "led.h"
#include "single_mode.h"
#include "lcd.h"


/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Display_Temperature_Humidity_Value(void)
{
     static uint8_t m,n,p,q;
    if(run_t.gPower_On==1){

		
		panel_led_fun();

	    m = (run_t.dispTime_hours/10) ;
		n=	(run_t.gTime_hours%10); 
		p = (run_t.dispTime_minutes/10);
		q=  (run_t.dispTime_minutes%10);

        //hours
		 lcd_t.number5_high = m;
		 lcd_t.number5_low = m;

		  lcd_t.number6_high = n;
		 lcd_t.number6_low = n;

		 //minutes 
		 lcd_t.number7_high = p;
		 lcd_t.number7_low = p;

		  lcd_t.number8_high = q;
		 lcd_t.number8_low = q;

		 DisplayPanel_Ref_Handler();
		

   }

		   
}


/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Display_DHT11_Value(void)
{
    
  static uint8_t hum1,hum2,time[1],temp[1]; 
  static uint8_t m,n,p,q,temp1,temp2;
 

    switch(run_t.single_data){
    
       case PANEL_DATA:
	   	run_t.single_data=0;
    
        hum1 =  run_t.gReal_humtemp[0]/10 %10;  //Humidity 
        hum2 =  run_t.gReal_humtemp[0]%10;
        
        temp1 = run_t.gReal_humtemp[1]/10 %10;  // temperature
        temp2 = run_t.gReal_humtemp[1]%10;

         //temperature 
		 lcd_t.number1_high = temp1;
		 lcd_t.number1_low = temp1;

		  lcd_t.number2_high = temp2;
		 lcd_t.number2_low = temp2;

		 //humidity
		 
		 lcd_t.number3_high = hum1;
		 lcd_t.number3_low = hum1;
		 
		 lcd_t.number4_high = hum2;
		 lcd_t.number4_low = hum2;

		 DisplayPanel_Ref_Handler();
		 
      break;

      case WIFI_TIME: //GMT time 
          if(run_t.wifi_connect_flag ==1){
		  	run_t.single_data=0;
		  	
          if(run_t.gInputCmd[0] > 0){


		     if(time[0] != run_t.gInputCmd[0]){

			      time[0] = run_t.gInputCmd[0];

	             
	               run_t.wifisetTime[0]= run_t.gInputCmd[0];
			       run_t.dispTime_hours=run_t.wifisetTime[0];
			 
			      run_t.dispTime_minute = 0;

	              run_t.gTimer_Cmd=1;	 
			    
			      run_t.gTimer_setup_zero=0;
		       	}
			}
          else{
          
           run_t.gTimer_Cmd=0;	
           run_t.dispTime_minute = 0;
           run_t.dispTime_hours=0;
          
          }

		        m = run_t. dispTime_hours /10%10 ;
			    n=	run_t. dispTime_hours %10; 
	            if(run_t.dispTime_minute ==0 ){ 
					p=0;
					q=0;

	            }
				else{
				   p = run_t. dispTime_minute /10 %10;
				   q=  run_t. dispTime_minute %10;
				}

                //hours
				 lcd_t.number5_high = m;
				 lcd_t.number5_low = m;

				  lcd_t.number6_high = n;
				 lcd_t.number6_low = n;

				 //minutes 
				 lcd_t.number7_high = p;
				 lcd_t.number7_low = p;

				  lcd_t.number8_high = q;
				 lcd_t.number8_low = q;
						
			   DisplayPanel_Ref_Handler();
           
        } 
        
      break;

         
      case  WIFI_TEMP:
           if(run_t.wifi_connect_flag ==1){
		   	run_t.single_data=0;
           if(run_t.gInputCmd[0] >19 && run_t.gInputCmd[0] <41){ //setup temperature 

		        if(temp[0] !=run_t.gInputCmd[0]){
				    temp[0]  =run_t.gInputCmd[0];

				 run_t.temperature_set_flag=1;
	       	     run_t.gTemperature = run_t.gInputCmd[0];

		        }
                
             }

		   	      temp1 = run_t.gTemperature/10 %10;
	              temp2 = run_t.gTemperature%10;

				   //temperature 
					 lcd_t.number1_high = temp1;
					 lcd_t.number1_low = temp1;

					  lcd_t.number2_high = temp2;
					 lcd_t.number2_low = temp2;

					    
				  DisplayPanel_Ref_Handler();
                    
         }
		
      break;

	 

     }
}  






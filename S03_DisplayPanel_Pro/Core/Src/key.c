#include "key.h"
#include "gpio.h"
#include "run.h"





/********************************************************************************************************
 	*
 	* Function Name:void SplitDispose_Key(uint8_t value)
 	* Function : Touch key handler function 
 	* Input Reference:NO
 	* Return Reference:NO
 	* 
*********************************************************************************************************/
void SplitDispose_Key(uint8_t value)
{
    static uint8_t plasma,wifi,dry,ai;
	
    
    switch(value){
        
       case 0x80: //Power On
        //   powerKey = powerKey ^ 0x01;
        //  if(powerKey ==1){
              run_t.wifiCmd[0]=0;
			  if(run_t.gPower_On == 0 || run_t.gPower_On == 0xff){
			  	  run_t.gTimes_hours_temp=12;
	              run_t.gPower_On=1;
	          
				  run_t.power_key =1;
				  run_t.gFan_RunContinue=0;
				 
				  run_t.gAi =0; //WT.EDIT 2022.09.01
				  run_t.gPlasma=0;
				  run_t.gDry =0;
				  run_t.gWifi =0;
	              // run_t.wifi_turn_off++;
			  }
			  else{
                  
				  	run_t.power_key =2;
				    run_t.gFan_RunContinue=1;
		            run_t.gPower_On=0;
					run_t.fan_off_60s =0;
		           //  run_t.wifi_turn_on++;
		          //   Smg_AllOff();
              }
        //  }
         
       
        break;
       
       case 0x40: //Mode On -> set time and timer 
           if(run_t.gPower_On ==1){
				
			run_t.gKeyTimer_mode = run_t.gKeyTimer_mode ^ 0x01; //the same is "0",and differenct is "1"

			if(run_t.gKeyTimer_mode == 1){
                
				run_t.gTimer_key_5s =0;
				run_t.temperature_flag =0;
		    }
            else{
               run_t.gKeyTimer_mode=0;
			 
			   run_t.temperature_flag =1;
			 
            }
           
	     }
		   
        break;
        
        case 0x20: //CIN3 -> DEC KEY
             if(run_t.gPower_On ==1){
			
			 	 if(run_t.gKeyTimer_mode==1){//times, is timer is 
                    
			 	     run_t.dispTime_hours--;
				    if(run_t.dispTime_hours <0){
						run_t.dispTime_hours=24;
					}
					
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
              
				
		
             
             }
           
             
         break;
        
        case 0x10: //CIN2 ->ADD KEY
             if(run_t.gPower_On ==1){
			 	  
				if(run_t.gKeyTimer_mode==1){
                     run_t.gTimer_key_5s =0;
				
					 run_t.dispTime_hours++;
				    if(run_t.dispTime_hours >24){
						run_t.dispTime_hours=0;
					}
				
					run_t.temperature_flag =0;
					run_t.gTimer_key_5s =0;
					
					
                    
                    
				 }
				 else{
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

             }
            
         break;
         
         case 0x08: //CIN4 -> AI  KEY 
               if(run_t.gPower_On ==1){
                   
                ai = ai ^ 0x01;
				if(ai==1){
 					run_t.gAi =1; //turon off AI mode
					
				}
				else{ //turn on AI mode
					run_t.gAi =0;
                    run_t.gDry =0;
                    run_t.gPlasma = 0;
				    

				}
				run_t.dry_key =3;
				run_t.ster_key =3;
				
              
			    
              }
            
         break;
         
         case 0x04: //CIN5  -> STERILIZATION KEY 
             if(run_t.gPower_On ==1){
			
               plasma = plasma ^ 0x01;
			   if(plasma ==1){  //turun off kill 
			   	
			       if(run_t.gPlasma ==1)
				       run_t.gPlasma = 0;
                   else
                       run_t.gPlasma = 1;
				   
		       }
			   else{
			   	  if(run_t.gPlasma ==1)
				       run_t.gPlasma = 0;
                   else
                       run_t.gPlasma = 1;
			   	}
               
                if( run_t.gPlasma==1 && run_t.gDry ==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		          }
		          else run_t.gFan_RunContinue =0;

			
             
             }
            
            
         break;
         
         case 0x02: //CIN6  ->DRY KEY 
               if(run_t.gPower_On ==1){
		
			    dry = dry^ 0x01;
				if(dry==1){ //turn off the first be pressed 
                   if(run_t.gDry== 1)
				       run_t.gDry =0;
                   else
                       run_t.gDry =1;
				  

				}
				else{ //the second be pressed key
                    
                   if(run_t.gDry== 1)
				       run_t.gDry =0;
                   else
                       run_t.gDry =1;
                    
					
				}
			

		           if( run_t.gPlasma==1 && run_t.gDry ==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		            }
		            else run_t.gFan_RunContinue =0;
			   
				 
               }
           
             
         break;
         
         case 0x01: //CIN7 -> wifi KEY
             if(run_t.gPower_On ==1){
			 

				wifi = wifi ^ 0x01;
				if(wifi==1){
 					run_t.gWifi =1; //tunr off wifi
					
				}
				else{
					run_t.gWifi =0; //turn on wifi
				   

				}
			
			}
                  
          break;
             
         default :
             
         
         break;
        
      }

}



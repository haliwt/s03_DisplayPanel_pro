#include "key.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"


key_types key_t;
uint8_t KEY_Scan(void)
{
   uint8_t  reval = 0;
  key_t.read = _KEY_ALL_OFF; //0xFF 
  
   if(POWER_KEY_VALUE ==KEY_DOWN )// high level
	{
		key_t.read &= ~0x01; // 0xff & 0xfe =  0xFE
	}
    else if(MODE_KEY_VALUE ==KEY_DOWN )
	{
		key_t.read &= ~0x02; // 0xFf & 0xfd =  0xFD
	}
    else if(DEC_KEY_VALUE==KEY_DOWN )
	{
		  key_t.read &= ~0x04; // 0xFf & 0xfB =  0xFB
	}
    else if(ADD_KEY_VALUE ==KEY_DOWN )
	{
		  key_t.read &= ~0x08; // 0x1f & 0xf7 =  0xF7
	 }

   

    switch(key_t.state )
	{
		case start:
		{
			if(key_t.read != _KEY_ALL_OFF)
			{
				key_t.buffer   = key_t.read; //??:key.buffer = 0xFE  POWER KEY 
				key_t.state    = first;
				key_t.on_time  = 0;
				key_t.off_time = 0;
                
			}
			break;
		}
		case first:
		{
			if(key_t.read == key_t.buffer) // adjust key be down ->continunce be pressed key
			{
				if(++key_t.on_time> 800) //1000  0.5us
				{
					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                        //key .value = 0xEF ^ 0XFF = 0X10
                   
					key_t.state   = second;
                   
                    
				}
			}
			else
			{
				key_t.state   = start;
			}
			break;
		}
		case second:
		{
			if(key_t.read == key_t.buffer) //again adjust key if be pressed down 
			{
				if(++key_t.on_time>50000)// 10000 long key be down
				{
					
					key_t.value = key_t.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key_t.on_time = 0;
					key_t.state   = finish;
                   
				}
			}
			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key_t.off_time>20) //30 don't holding key dithering
					{
						key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key_t.state   = finish; // loose hand
					}
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key_t.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key_t.state   = end;
         
			break;
		}
		case end:
		{
			if(key_t.read == _KEY_ALL_OFF)
			{
				if(++key_t.off_time>20)//50 //100
				{
					key_t.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key_t.state   = start;
         
			break;
		}
	}
	return  reval;


}

//°´¼ü´¦Àíº¯Êý
//·µ»Ø°´¼üÖµ
//mode:0,²»Ö§³ÖÁ¬Ðø°´;1,Ö§³ÖÁ¬Ðø°´;
//0£¬Ã»ÓÐÈÎºÎ°´¼ü°´ÏÂ
//1£¬WKUP°´ÏÂ WK_UP
//×¢Òâ´Ëº¯ÊýÓÐÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>KEY2>WK_UP!!
uint8_t  KEY_GPIO_Scan(uint8_t mode)
{
    static uint8_t key_up=1;     //release key flag
    if(mode==1)key_up=1;    // continuce to pressed
    if(key_up&&(POWER_KEY_VALUE==1||MODE_KEY_VALUE==1||DEC_KEY_VALUE==1||ADD_KEY_VALUE==1))
    {
        delay_ms(10);
        key_up=0;
        if(POWER_KEY_VALUE==0)         return KEY0_PRES;
        else if(MODE_KEY_VALUE==0)     return KEY1_PRES;
        else if(DEC_KEY_VALUE==0)      return KEY2_PRES;
        else if(ADD_KEY_VALUE==0)      return WKUP_PRES;          
    }else if(POWER_KEY_VALUE==0&&MODE_KEY_VALUE==0&&DEC_KEY_VALUE==0&&ADD_KEY_VALUE==0)key_up=1;
    return 0;   //ÎÞ°´¼ü°´ÏÂ
}

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
        
       case KEY_POWER: //Power On
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
		           
              }
       
         
       
        break;
       
       case KEY_MODE: //Mode On -> set time and timer 
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
        
        case KEY_DEC: //CIN3 -> DEC KEY
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
        
        case KEY_ADD: //CIN2 ->ADD KEY
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
         
         case KEY_LONG_POWER: // Open Wifi function to connect network
               if(run_t.gPower_On ==1){
                   
                   run_t.wifi_connect_label =1; //Wifi icon faster of blink.
              
			    }
            
         break;
         
        
         
        default :
             
         
         break;
        
      }

}

//ÖÐ¶Ï·þÎñ³ÌÐòÖÐÐèÒª×öµÄÊÂÇé
//ÔÚHAL¿âÖÐËùÓÐµÄÍâ²¿ÖÐ¶Ï·þÎñº¯Êý¶¼»áµ÷ÓÃ´Ëº¯Êý
//GPIO_Pin:ÖÐ¶ÏÒý½ÅºÅ
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

//  do{

//	run_t.readKeyValue = KEY_Scan();


//  	}while(VK36N4D_INT_Pin==1);

 }



#include "key.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "cmd_link.h"
#include "single_mode.h"


key_types key_t;


uint8_t KEY_Scan(void)
{

   uint8_t  reval = 0;
  key_t.read = _KEY_ALL_OFF; //0xFF 
  
   if(POWER_KEY_VALUE() ==KEY_DOWN )// high level
	{
		key_t.read &= ~0x01; // 0xff & 0xfe =  0xFE
	}
    else if(MODE_KEY_VALUE() ==KEY_DOWN )
	{
		key_t.read &= ~0x02; // 0xFf & 0xfd =  0xFD
	}
    else if(DEC_KEY_VALUE()==KEY_DOWN )
	{
		  key_t.read &= ~0x04; // 0xFf & 0xfB =  0xFB
	}
    else if(ADD_KEY_VALUE() ==KEY_DOWN )
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

				if(++key_t.on_time> 10000 &&  run_t.power_times==1) //1000  0.5us
				{
					
					run_t.power_times++ ;

					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                        //key .value = 0xEF ^ 0XFF = 0X10
                   
					key_t.state   = second;
					
                   
                 }
				 else if(++key_t.on_time>6){

					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                        //key .value = 0xEF ^ 0XFF = 0X10
                   
					key_t.state   = second;


				 }
			}
			else
			{
				key_t.on_time = 0; 
				key_t.state   = start;
			}
			break;
		}
		case second:
		{
			if(key_t.read == key_t.buffer) //again adjust key if be pressed down 
			{
				if(++key_t.on_time> 0x37 && run_t.power_times==2)// 500 long key be down
				{
					
					key_t.value = key_t.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key_t.on_time = 0;
					key_t.state   = finish;
                   
				}
			}
			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key_t.off_time>1) //30 don't holding key dithering
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
				if(++key_t.off_time>1)//50 //100
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







#include "key.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "cmd_link.h"
#include "single_mode.h"


key_types key_t;
 uint8_t  k1 ;
     uint8_t  k2 ;
	 uint8_t k3;
     uint16_t cnt;
      uint8_t value;
//uint32_t wifi_key_counter;

//uint8_t KEY_Scan(void)
//{
//   uint8_t  reval = 0;
//  key_t.read = _KEY_ALL_OFF; //0xFF 
//  
//   if(POWER_KEY_VALUE() ==KEY_DOWN )// high level
//	{
//		key_t.read &= ~0x01; // 0xff & 0xfe =  0xFE
//	}
//    else if(MODE_KEY_VALUE() ==KEY_DOWN )
//	{
//		key_t.read &= ~0x02; // 0xFf & 0xfd =  0xFD
//	}
//    else if(DEC_KEY_VALUE()==KEY_DOWN )
//	{
//		  key_t.read &= ~0x04; // 0xFf & 0xfB =  0xFB
//	}
//    else if(ADD_KEY_VALUE() ==KEY_DOWN )
//	{
//		  key_t.read &= ~0x08; // 0x1f & 0xf7 =  0xF7
//	 }

//   

//    switch(key_t.state )
//	{
//		case start:
//		{
//			if(key_t.read != _KEY_ALL_OFF)
//			{
//				key_t.buffer   = key_t.read; //??:key.buffer = 0xFE  POWER KEY 
//				key_t.state    = first;
//				key_t.on_time  = 0;
//				key_t.off_time = 0;
//                
//			}
//			break;
//		}
//		case first:
//		{
//			if(key_t.read == key_t.buffer) // adjust key be down ->continunce be pressed key
//			{
//				if(++key_t.on_time> 100) //1000  0.5us
//				{
//					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
//					key_t.on_time = 0;                        //key .value = 0xEF ^ 0XFF = 0X10
//                   
//					key_t.state   = second;
//                   
//                    
//				}
//			}
//			else
//			{
//				key_t.state   = start;
//			}
//			break;
//		}
//		case second:
//		{
//			if(key_t.read == key_t.buffer) //agModeln adjust key if be pressed down 
//			{
//				if(++key_t.on_time>50000)// 10000 long key be down
//				{
//					
//					key_t.value = key_t.value|0x80; //key.value = 0x01 | 0x80  =0x81  
//					key_t.on_time = 0;
//					key_t.state   = finish;
//                   
//				}
//			}
//			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
//				{
//					if(++key_t.off_time>50) //30 don't holding key dithering
//					{
//						key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
//						
//						key_t.state   = finish; // loose hand
//					}
//				}
//		   
//			break;
//		}
//		case finish:
//		{
//			
//			reval = key_t.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
//			key_t.state   = end;
//         
//			break;
//		}
//		case end:
//		{
//			if(key_t.read == _KEY_ALL_OFF)
//			{
//				if(++key_t.off_time>5)//50 //100
//				{
//					key_t.state   = start;
//                  
//				}
//			}
//			break;
//		}
//		default:
//		{
//			key_t.state   = start;
//         
//			break;
//		}
//	}
//	return  reval;


//}

////°´¼ü´¦Àíº¯Êý
////·µ»Ø°´¼üÖµ
////mode:0->don't continuce be pressed . 1->enable continuce be pressed
////0£¬Ã»ÓÐÈÎºÎ°´¼ü°´ÏÂ
////Enagle continuce be pressed: WK_UP
////×¢Òâ´Ëº¯ÊýÓÐÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>KEY2>WK_UP!!
//uint8_t  KEY_GPIO_Scan(uint8_t mode)
//{
//    static uint8_t key_up=1;     //release key flag
//    if(mode==1)key_up=1;    // continuce to pressed
//    if(key_up&&(POWER_KEY_VALUE()==1||MODE_KEY_VALUE()==1||DEC_KEY_VALUE()==1||ADD_KEY_VALUE()==1))
//    {
//        delay_ms(10);
//        key_up=0;
//        if(POWER_KEY_VALUE()==0)         return KEY0_PRES;
//        else if(MODE_KEY_VALUE()==0)     return KEY1_PRES;
//        else if(DEC_KEY_VALUE()==0)      return KEY2_PRES;
//        else if(ADD_KEY_VALUE()==0)      return WKUP_PRES;          
//    }
//    else if(POWER_KEY_VALUE()==0&&MODE_KEY_VALUE()==0&&DEC_KEY_VALUE()==0&&ADD_KEY_VALUE()==0){
//        key_up=1;
//    }
//    return 0;   //ÎÞ°´¼ü°´ÏÂ
//}





/************************************************************************
	*
	*Function Name: void JP_KEY(void)
	*Function : 
	*Input Ref: NO
	*Retrun Ref:NO
	*
************************************************************************/
uint8_t KEY_Scan(void)
{

  

   if(POWER_KEY_VALUE() ==KEY_DOWN){
        if(k1<0x32)
        k1++;   
    }
    else
		k1=0;

	if(k1 < 0x20 && k1 > 0x02){

	    if(POWER_KEY_VALUE() ==KEY_UP);
		HAL_Delay(20);

	    if(POWER_KEY_VALUE() ==KEY_UP){
            cnt = 0x01;
			return cnt;
         }
		
     }

   if(k1 ==0x32){
       
	    cnt = 0x02;
		return cnt ;


	}
	
}






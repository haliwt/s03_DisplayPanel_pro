#include "lcd.h"
#include "delay.h"
#include "run.h"



#define WIFI_Symbol     		0x01 //addr 0xC5
#define WIFI_NO_Symbol 

#define LINE_Symbol             0x01 //addr  0xC2


#define AI_Symbol    			0x01 //addr 0xC3
#define AI_NO_Symbol            0x0


#define DRY_Symbol              0x02  //addr 0xC2 ->T4
#define DRY_NO_Symbol           0x0

#define KILL_Symbol             0x04  //addr 0xC2 ->T5
#define KILL_NO_Symbol           0x0

#define BUG_Symbol            0x08   //addr 0xC2 ->T6
#define BUG_NO_Symbol         0x0

#define TEMP_Symbol              0x01     //addr 0xC4
#define HUMI_Symbol              0x01      //addr  0xC9

#define TWO_DOT_Symbol           0x01       //addr 0xCB

#define T10                      0x08     //addr 0xCF
#define T11                      0x04      //addr 0xCF
#define T12                      0x02      //addr 0xCF
#define T16                      0x01     //addr 0xCF

#define T13                      0x01      //addr 0xCE
#define T14                      0x01      //addr 0xCC
#define T15                      0x01      //addr 0xCA

#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
#define   seg_g  0x04      //SEG2 , //seg_g = 0x40
#define   seg_c  0x08      //SEG3 , //seg_d = 0x08
//High BIT
#define   seg_a  0x10      //SEG4 , //seg_c = 0x04
#define   seg_f  0x20      //SEG5   //seg_a = 0x01
#define   seg_e  0x40      //SEG6   //seg_b = 0x02 
#define   seg_d  0x80      //SEG7 -> ":"


#define  COM0_L        0x01
#define  COM1_L        0X02
#define  COM2_L        0X04
#define  COM3_L        0X08


#define  COM0_H        0X10
#define  COM1_H        0X20
#define  COM2_H        0X40
#define  COM3_H        0X80

#define LUM_VALUE      0x97


static void Display_Kill_Dry_Ster_Icon(void);

const uint8_t lcdNumber1_Low[]={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};


const unsigned char segNumber_Low[]={
 
         seg_b+seg_c,        		      // char "0"  0x00
		 seg_b+seg_c,                      // char "1"  0x01
		 seg_b+seg_g,              		  // char "2"  0x02
		 seg_b+seg_g+seg_c,               // char "3"  0x03
		 seg_b+seg_g+seg_c,               // char "4"  0x04
		 seg_g+seg_c,              		// char "5"  0x05
		 seg_g+seg_c,              // char "6"  0x06
		 seg_b+seg_c,                    	// char "7"  0x07
		 seg_b+seg_g+seg_c,  		        // char "8"  0x08
		 seg_b+seg_g+seg_c,        		// char "9"  0x09
	     0                                      // char "NLL"  0x16



};

const uint8_t  lcdNumber1_High[]={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};
const unsigned char segNumber_High[]={
         seg_a+seg_f+seg_e+seg_d,        // char "0"  0x00
		 0,                				 // char "1"  0x01
		 seg_a+seg_e+seg_d,              // char "2"  0x02
		 seg_a+seg_d,                    // char "3"  0x03
		 seg_f,                          // char "4"  0x04
		 seg_a+seg_f+seg_d,              // char "5"  0x05
		 seg_a+seg_f+seg_e+seg_d,        // char "6"  0x06
		 seg_a,                    		 // char "7"  0x07
		 seg_a+seg_f+seg_e+seg_d,  		 // char "8"  0x08
		 seg_a+seg_f+seg_d,        		 // char "9"  0x09
         0                               // char "NLL"  0x16



};

static const uint8_t lcdNumber2_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber2_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber3_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber3_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber4_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber4_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber5_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber5_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber6_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber6_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber7_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber7_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

static const uint8_t lcdNumber8_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
static const uint8_t lcdNumber8_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};






lcd_ref lcd_t; 

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
//static void TIM1723_Write_Cmd(uint8_t cmd);
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);



/*****************************************************
 * 
 * 
 * 
 * 
******************************************************/
static void TM1723_Start(void)
{
  TM1723_STB_SetLow();
	
}
static void TM1723_Stop(void)
{
   TM1723_STB_SetHigh();

}

static void TM1723_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1723_CLK_SetLow();
	 if(data & 0x01){
	     TM1723_DIO_SetHigh(); //TM1723 high of data to IC
		  
	 }
	 else{
	     TM1723_DIO_SetLow(); //TM1723 low level of data to IC
		  
	 }
   
    delay_us(100);
    data =data>>1;//
	 
	 TM1723_CLK_SetHigh();
	 //data =data>>1;//
	  delay_us(2);
	// data >>=1;//
	
  
     
 }

}
void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
 
}
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();

}

/*************************************************************************
 	*
 	* Function Name:void Display_Name_Humidity(void)
 	* Function :lcd display 'humidity'
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*************************************************************************/ 
#if 0
void DisplayPanel_TestHandler(void)
{
     TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);
	 
    //low-byte->T3,T4,T5,67,high->byte->1A,1F,1E,1D
    TM1723_Write_Display_Data(0xC2,lcdNumber1_High[6]+0x0F);//display digital "88"

    if(run_t.gModel==0)
      TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[6]+AI_Symbol+lcdNumber2_High[1]);//display  "AI icon"
    else
	  TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[6]+AI_NO_Symbol+lcdNumber2_High[1]);//don't display  "AI icon"
     
	 TM1723_Write_Display_Data(0xC4,0x01+lcdNumber2_Low[1]+lcdNumber3_High[2]);//display "t,c"
	 
     //wifi icon
	 if(run_t.wifi_connect_flag ==0){ //hasn't wifi
		 if(lcd_t.gTimer_wifi_500ms >49 && lcd_t.gTimer_wifi_500ms<100){
	          
	           TM1723_Write_Display_Data(0xC5,WIFI_Symbol+lcdNumber3_Low[2] + lcdNumber4_High[3]); //Wifi
	     }
	     else if(lcd_t.gTimer_wifi_500ms <50){
		 	 
	         TM1723_Write_Display_Data(0xC5,WIFI_NO_Symbol+lcdNumber3_Low[2] + lcdNumber4_High[3]); //Wifi 
	     }
	     else{
	        lcd_t.gTimer_wifi_500ms =0;
	     }
     }
	 else{ //link wifi to tencent clud 
        TM1723_Write_Display_Data(0xC5,WIFI_Symbol+lcdNumber3_Low[2] + lcdNumber4_High[3]); //Wifi

	 }
	 //endif icon
     TM1723_Write_Display_Data(0xC9,0x01+lcdNumber4_Low[3]+lcdNumber5_High[4]);//display digital '4,5'

	 //T15
      if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
         TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low[4]+lcdNumber6_High[5]);//display digital '5,6'
      }
	  else if(lcd_t.gTimer_fan_10ms <10){
		  TM1723_Write_Display_Data(0xCA,lcdNumber5_Low[4]+lcdNumber6_High[5]);//display digital '5,6'
	  }
     
	 TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low[5]+lcdNumber7_High[9]);//display "t,c"

    //T14
	 if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
	      TM1723_Write_Display_Data(0xCC,lcdNumber7_Low[9]+lcdNumber8_High[7]);//display "t,c

	 }
	 else if(lcd_t.gTimer_fan_10ms <10){
  			TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[9]+lcdNumber8_High[7]);//display "t,c
	  }
     //T13
	 if(lcd_t.gTimer_fan_10ms>9 && lcd_t.gTimer_fan_10ms<20){
				TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[7]+0xE0);//display "t,c"
	  }
	  else if(lcd_t.gTimer_fan_10ms <10){
	         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[7]+0xE0);//display "t,c"

	  }
	  //T11
      if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
              TM1723_Write_Display_Data(0xCF,T11+T16);//
      }
	  else if(lcd_t.gTimer_fan_10ms <10){
	         TM1723_Write_Display_Data(0xCF,T16+T12+T10);//

	  }
	  else
	  	   lcd_t.gTimer_fan_10ms=0;
	//open display
	 TIM1723_Write_Cmd(0x94);//(0x9B);

}

#endif 

void DisplayPanel_Ref_Handler(void)
{
     TIM1723_Write_Cmd(0x00);
	// TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

    //Address C2 ->low_byte->T3,T4,T5,T6,high_byte->1A,1F,1E,1D 
    //TM1723_Write_Display_Data(0xC2,0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol+lcdNumber1_High[lcd_t.number1_high]);//display digital "temperature"
    Display_Kill_Dry_Ster_Icon();
	
    //T1->AI
    if(run_t.gModel==1)
       TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[lcd_t.number1_low]+AI_Symbol+lcdNumber2_High[lcd_t.number2_high]);//display  "AI icon"
     else 
	 	TM1723_Write_Display_Data(0xC3,(lcdNumber1_Low[lcd_t.number1_low]&0x0e)+lcdNumber2_High[lcd_t.number2_high]);//don't display "AI icon"
     //
	 TM1723_Write_Display_Data(0xC4,0x01+lcdNumber2_Low[lcd_t.number2_low]+lcdNumber3_High[lcd_t.number3_high]);//display "t,c"
	 
     //T2->WIFI icon -> 0xC5
     if(run_t.wifi_connect_flag ==0){ //hasn't wifi
		 if(lcd_t.gTimer_wifi_500ms >49 && lcd_t.gTimer_wifi_500ms<100){
	          
	           TM1723_Write_Display_Data(0xC5,WIFI_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number3_high]); //Wifi
	     }
	     else if(lcd_t.gTimer_wifi_500ms <50){
		 	 
	         TM1723_Write_Display_Data(0xC5,WIFI_NO_Symbol+lcdNumber3_Low[lcd_t.number3_high] + lcdNumber4_High[lcd_t.number3_high]); //Wifi 
	     }
	     else{
	        lcd_t.gTimer_wifi_500ms =0;
	     }
     }
	 else{
           TM1723_Write_Display_Data(0xC5,WIFI_Symbol+lcdNumber3_Low[lcd_t.number3_low] + lcdNumber4_High[lcd_t.number3_high]); //Wifi
	 }
     //Humidity Icon "0xC9"-numbers "4-B,G,C","5-A,F,E,D"
     TM1723_Write_Display_Data(0xC9,0x01+lcdNumber4_Low[lcd_t.number4_low]+lcdNumber5_High[lcd_t.number5_high]);//display digital '4,5'

	 //T15,"0xCA"Numbers"5-B,G,C","6-A,F,E,D"
      if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
         TM1723_Write_Display_Data(0xCA,T15+lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]);//display digital '5,6'
      }
	  else if(lcd_t.gTimer_fan_10ms <10){
		  TM1723_Write_Display_Data(0xCA,lcdNumber5_Low[lcd_t.number5_low]+lcdNumber6_High[lcd_t.number6_high]);//display digital '5,6'
	  }
     //address"0xCB" ->numbers .T9,"6-B,G,C","7-A,F,E,D"
	 TM1723_Write_Display_Data(0xCB,0x01+lcdNumber6_Low[lcd_t.number6_low]+lcdNumber7_High[lcd_t.number7_high]);//display "6,7"

    //T14,address"0xCC" ->numbers .high 4 bits -T14,"7-B,G,C",low 4 bits "8-A,F,E,D"
	 if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
	      TM1723_Write_Display_Data(0xCC,lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]);//display "7,8'

	 }
	 else if(lcd_t.gTimer_fan_10ms <10){
  			TM1723_Write_Display_Data(0xCC,T14+lcdNumber7_Low[lcd_t.number7_low]+lcdNumber8_High[lcd_t.number8_high]);//display "t,c
	  }
     //T13,address "0xCE",numbers."8-B,G,C","null,T19,T18,T17"
	 if(lcd_t.gTimer_fan_10ms>9 && lcd_t.gTimer_fan_10ms<20){
				TM1723_Write_Display_Data(0xCE,T13+lcdNumber8_Low[lcd_t.number8_low]+0xE0);//display "t,c"
	  }
	  else if(lcd_t.gTimer_fan_10ms <10){
	         TM1723_Write_Display_Data(0xCE,lcdNumber8_Low[lcd_t.number8_low]+0xE0);//display "t,c"

	  }
	  //T16 address "0xCF",T12,T11,T10
      if(lcd_t.gTimer_fan_10ms >9 && lcd_t.gTimer_fan_10ms<20){
              TM1723_Write_Display_Data(0xCF,T11+T16);//
      }
	  else if(lcd_t.gTimer_fan_10ms <10){
	         TM1723_Write_Display_Data(0xCF,T16+T12+T10);//

	  }
	  else
	  	   lcd_t.gTimer_fan_10ms=0;
	//open display
	 TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);

}


static void Display_Kill_Dry_Ster_Icon(void)
{

  if(run_t.gDry==1 && run_t.gPlasma==1 && run_t.gBug==1){

     //[T3,T4,T5,T6,---- ] ->Address C2 ->low_byte->T3,T4,T5,T6,high_byte->1A,1F,1E,1D 
     TM1723_Write_Display_Data(0xC2,(0X01+DRY_Symbol+KILL_Symbol+BUG_Symbol)+lcdNumber1_High[lcd_t.number1_high]);//display digital "temp
     TIM1723_Write_Cmd(LUM_VALUE);
  }
  else if(run_t.gDry==0 && run_t.gPlasma==1 && run_t.gBug==1){

      TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_Symbol)&0x0d)+lcdNumber1_High[lcd_t.number1_high]);//display digital "temp
      TIM1723_Write_Cmd(LUM_VALUE);
   }
   else if(run_t.gDry==0 && run_t.gPlasma==0 && run_t.gBug ==1){

        TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_Symbol)& 0x9)+lcdNumber1_High[lcd_t.number1_high]);//display digit
        TIM1723_Write_Cmd(LUM_VALUE);
   }
  else if(run_t.gDry==0 && run_t.gPlasma==0 && run_t.gBug ==0){

        TM1723_Write_Display_Data(0xC2,0X01+DRY_NO_Symbol+KILL_NO_Symbol+BUG_NO_Symbol+lcdNumber1_High[lcd_t.number1_high]);//display digit
        TIM1723_Write_Cmd(LUM_VALUE);
  }
  else if(run_t.gDry==1 && run_t.gPlasma==0 && run_t.gBug ==1){

        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_Symbol)&0x0b)+lcdNumber1_High[lcd_t.number1_high]);//display digit
        TIM1723_Write_Cmd(LUM_VALUE);
  }
  else if(run_t.gDry==1 && run_t.gPlasma==0 && run_t.gBug ==0){

        TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_NO_Symbol+BUG_NO_Symbol)&0x03)+lcdNumber1_High[lcd_t.number1_high]);//display digit
       TIM1723_Write_Cmd(LUM_VALUE);
  }
  else if(run_t.gDry==0 && run_t.gPlasma==1 && run_t.gBug ==0){
   
		  TM1723_Write_Display_Data(0xC2,((0X01+DRY_NO_Symbol+KILL_Symbol+BUG_NO_Symbol)&0x05)+lcdNumber1_High[lcd_t.number1_high]);//display digit
		  TIM1723_Write_Cmd(LUM_VALUE);
 }
  else if(run_t.gDry==1 && run_t.gPlasma==1 && run_t.gBug ==0){
	 
			TM1723_Write_Display_Data(0xC2,((0X01+DRY_Symbol+KILL_Symbol+BUG_NO_Symbol)&0x07)+lcdNumber1_High[lcd_t.number1_high]);//display digit
			TIM1723_Write_Cmd(LUM_VALUE);
   }

  
   TIM1723_Write_Cmd(LUM_VALUE);
   
}

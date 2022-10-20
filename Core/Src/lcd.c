#include "lcd.h"
#include "delay.h"





#define AI_Symbol    			0x01 //addr 0xC3
#define WIFI_Symbol     		0x01 //addr 0xC5
#define LINE_Symbol             0x01 //addr  0xC2
#define DRY_Symbol              0x02  //addr 0xC2
#define KILL_Symbol             0x04  //addr 0xC2
#define EXPELING_Symbol         0x08   //addr 0xC2

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






lcd_ref lcd_t; 

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
static void TIM1723_Write_Cmd(uint8_t cmd);
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
static void TIM1723_Write_Cmd(uint8_t cmd)
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
void DisplayPanel_Handler(void)
{
     TIM1723_Write_Cmd(0x00);
	 TIM1723_Write_Cmd(0x40);
	 TIM1723_Write_Cmd(0x44);

    TM1723_Write_Display_Data(0xC2,lcdNumber1_High[6]+0x0F);//display digital "88"

    
    TM1723_Write_Display_Data(0xC3,lcdNumber1_Low[6]+AI_Symbol+lcdNumber2_High[1]);//display digital "88"
   
     
	 TM1723_Write_Display_Data(0xC4,0x01+lcdNumber2_Low[1]+lcdNumber3_High[2]);//display "t,c"
	 
	 if(lcd_t.gTimer_wifi_500ms >49 && lcd_t.gTimer_wifi_500ms<100){
          
           TM1723_Write_Display_Data(0xC5,WIFI_Symbol+lcdNumber3_Low[2] + lcdNumber4_High[3]); //Wifi
     }
     else if(lcd_t.gTimer_wifi_500ms <50){
	 	 
         TM1723_Write_Display_Data(0xC5,0x00+lcdNumber3_Low[2] + lcdNumber4_High[3]); //Wifi 
     }
     else{
        lcd_t.gTimer_wifi_500ms =0;
     }
    
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



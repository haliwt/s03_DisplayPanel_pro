#ifndef __LCD_H_
#define __LCD_H_
#include "main.h"

#define TM1723_POWER_ON()				HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_SET)
#define TM1723_POWER_OFF()             HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin,GPIO_PIN_RESET)


#define LCD_BACK_LIGHT_ON()				HAL_GPIO_WritePin(BACK_LIGHT_GPIO_Port,BACK_LIGHT_Pin,GPIO_PIN_SET)
#define LCD_BACK_LIGHT_OFF()            HAL_GPIO_WritePin(BACK_LIGHT_GPIO_Port,BACK_LIGHT_Pin,GPIO_PIN_RESET)




#define TM1723_CLK_SetHigh()            HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1723_CLK_SetLow()             HAL_GPIO_WritePin(TM1723_SCLK_GPIO_Port,TM1723_SCLK_Pin ,GPIO_PIN_RESET)  // ����͵�ƽ

#define TM1723_DIO_SetHigh()            HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_SET)    // ����ߵ�ƽ
#define TM1723_DIO_SetLow()             HAL_GPIO_WritePin(TM1723_DIO_GPIO_Port,TM1723_DIO_Pin,GPIO_PIN_RESET)    // output low level

#define TM1723_STB_SetHigh()            HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_SET)
#define TM1723_STB_SetLow()             HAL_GPIO_WritePin(TM1723_STB_GPIO_Port,TM1723_STB_Pin,GPIO_PIN_RESET)

//extern volatile uint8_t DispData[3];//??LED??
#define		BitSET(x,y)		x|=(1<<y)				//?1
#define		BitCLR(x,y)		x&=~(1<<y)				//?0


#define DisplayReg           0x40// to write display register 
  
#define AddrFixed 	         0x44// 
#define AddrAutoAdd         0x40 
 
   
  
#define OpenDispTM1723          0x97 // full screen is tunr on light
#define OpenDispTM1723_5        0X9f
#define TM1723Default          	0x87
#define CloseDispTM1723		    0x80// 



 //Display Address 
#define Addr00H  		0xC0//??00H
#define Addr01H  		0xC1//??01H

#define Addr02H  		0xC2//??02H
#define Addr03H  		0xC3//??03H
//digital 3
#define Addr04H  		0xC4//??03H
#define Addr05H  		0xC5//??03H
//digital 4
#define Addr06H  		0xC6//??00H
#define Addr07H  		0xC7//??01H


//Humidity SMG address
#define Addr08H  		0xC8//??02H
#define Addr09H  		0xC9//??03H

#define Addr0AH  		0xCA//??03H
#define Addr0BH  		0xCB//??03H

//temperature SMG address
#define Addr0CH         0xCC//??0CH
#define Addr0DH         0xCD//??0DH

#define Addr0EH         0xCE//??0CH
#define Addr0FH         0xCF//??0DH

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

const uint8_t lcdNumber2_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber2_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber3_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber3_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber4_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber4_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber5_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber5_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber6_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber6_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber7_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber7_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};

const uint8_t lcdNumber8_Low[]  ={0x0A,0x0A,0x06,0x0E,0x0E,0x0C,0x0C,0x0A,0x0E,0x0E,0x00};
const uint8_t lcdNumber8_High[] ={0xF0,0,0xD0,0x90,0x20,0xB0,0xF0,0x10,0xF0,0xB0,0x0};


typedef struct _LCD_Ref{

     uint8_t wifi_glint_flag;

	 uint8_t gTimer_wifi_500ms;
	 uint8_t gTimer_fan_10ms;


}lcd_ref;

extern lcd_ref lcd_t; 

void DisplayPanel_Handler(void);



#endif 

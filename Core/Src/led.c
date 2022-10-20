#include "led.h"
#include "run.h"
#include "lcd.h"

void (*panel_led_fun)(void);


/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Breath_Led(void)
{



}
/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void Lcd_PowerOn_Fun(void)
{
    LED_POWER_ON()	;//key of led turn On
    LCD_BACK_LIGHT_ON();

}

/*******************************************************************************************
 	*
 	* Function Name:void Panel_Led_OnOff_Function(void)
 	* Function :panel of led turn on or off which key function 
 	* Input Ref:NO
 	* Return Ref:NO
 	* 
*******************************************************************************************/  
void PowerOn_LcdLed_OnOff(void(* lcdled_turnon_handler)(void))
{

   panel_led_fun = lcdled_turnon_handler;

}



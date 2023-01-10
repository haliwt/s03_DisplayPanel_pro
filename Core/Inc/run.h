#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"


typedef enum WIFI_STATE_T{
   
    WIFI_POWER_ON = 0x80,
    WIFI_POWER_OFF=0X81,
    WIFI_MODE_1=0X08,   //state ->normal works
    WIFI_MODE_2=0X18,   //state->sleeping works
    WIFI_KILL_ON=0x04,  //Anion(plasma)
    WIFI_KILL_OFF=0x14,
    WIFI_PTC_ON = 0x02, 
    WIFI_PTC_OFF = 0x12,
    WIFI_SONIC_ON = 0x01,       //ultrasonic
    WIFI_SONIC_OFF = 0x11,
    WIFI_WIND_SPEED_ITEM = 0x90,
    WIFI_TEMPERATURE = 0xA0


}wifi_state_t;


typedef struct __RUN{

   uint8_t keyValue;
   uint8_t readKeyValue;
   uint8_t power_key;
   uint8_t gTemperature_timer_flag;
   uint8_t gPower_On;
   uint8_t gRun_flag;
   
   uint8_t keyAdd_continue;
   uint8_t keyDec_continue;
  

   uint8_t gDht11_flag;
   uint8_t gTemperature;
 
   uint8_t gTimer_minute_Counter;
   
  uint8_t gTimer_setup_zero;

  uint8_t gFan_RunContinue;

  uint8_t temperature_flag;
  uint8_t gTiming_flag;
  
   uint8_t usart_flag;
   uint8_t decodeFlag;
   uint8_t gTemp_check;
   
   uint8_t  gTimer_Cmd;
   uint8_t  gPlasma;

   uint8_t  gDry;

   uint8_t  gModel;
   uint8_t  gBug;
  
   uint8_t  gTimes_minutes_temp;
   
   uint8_t  gTimer_fan_counter;

  

   

   uint8_t single_data;
   uint8_t fan_off_60s;

   uint8_t wifi_connect_flag;

   uint8_t wifi_set_temperature;
   uint8_t wifi_set_timing;
   uint8_t wifi_set_wind_speed;
   uint8_t wifi_set_temp_flag ;
   uint8_t wifi_special_key;

 
   

   uint8_t dispTime_minute;
   uint8_t Timer_mode_flag;
   uint8_t temperature_set_flag;

   uint8_t gTimer_1hour;
   uint8_t rx_temphum_flag;
	
  
   
  
   uint8_t  gTimer_set_temperature ;
   uint8_t  gTimer_1_hour_counter;
   uint8_t  beijing_time_seconds;
   
   
   uint8_t gReal_humtemp[2];
   uint8_t gInputCmd[2];
   uint8_t wifisetTime[1];
   uint8_t wifiCmd[2];

    int8_t dispTime_hours;
	
    int8_t 	gTimes_hours_temp;


   
 }RUN_T;

extern RUN_T run_t;



void SplitDispose_Key(uint8_t value);







void Power_Off(void);
void DisplayTimer_Timing(void);


void RunCommand_Handler(void);


#endif 




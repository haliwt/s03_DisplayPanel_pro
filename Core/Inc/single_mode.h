#ifndef __SINGLE_MODE_
#define __SINGLE_MODE_
#include "main.h"


typedef enum _time_t{

   time_timing= 0x01,
   time_normal,
   time_gmt

}time_state_t;

typedef enum _WIFI_POWER_STATE_{
	WIFI_POWER_ON_ITEM = 0x01,
	WIFI_POWER_OFF_ITEM,
	WIFI_POWER_NULL

}wifi_power_state;

extern void (*single_ai_fun)(uint8_t cmd);
extern void (*single_add_fun)(void);
extern void (*sendAi_usart_fun)(uint8_t senddat);


void Scan_KeyModel(void);



void Single_AI_RunCmd(void (*singlaieHandler)(uint8_t dat));

void Single_Add_RunCmd(void(*addHandler)(void));

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void));

void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat));

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat));
void Decode_Function(void);

void Wifi_Key_Fun(void);
void RunPocess_Command_Handler(void);


void Receive_MainBoard_Data_Handler(uint8_t cmd);


void Power_Off_Fun(void);



#endif 


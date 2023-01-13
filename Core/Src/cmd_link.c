#include "cmd_link.h"
#include "usart.h"
#include "gpio.h"
#include "run.h"
#include "display.h"


volatile static uint8_t transOngoingFlag; //interrupt Transmit flag bit , 1---stop,0--run
uint8_t outputBuf[8];
static uint8_t transferSize;
static uint8_t state;
uint8_t inputBuf[MAX_BUFFER_SIZE];


/****************************************************************************************************
**
*Function Name:static void selectLight(uint8_t index)
*Function: UART2 transmit interrupt process ---4D 58 4C 53 32 30 32 
*Input Ref: LED number 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_PowerOff(uint8_t index)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D //Touch Key
	outputBuf[1]='K'; //58
	outputBuf[2]='P'; //4C	// 'P' power
	outputBuf[3]=index; //53	// 'S' select light command, 'C' close all light command
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}
void SendData_Buzzer(void)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D
	outputBuf[1]='K'; //58
	outputBuf[2]='Z'; //4C	// 'L' for light board
	outputBuf[3]='Z'; //53	// 'S' select light command, 'C' close all light command
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}


void SendData_Set_Temperature(uint8_t hdata)
{
	    outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='T'; //4C	// 'T'->temperature
		outputBuf[3]=hdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}

void SendData_Set_Wifi(uint8_t hdata)
{
	    outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='W'; //4C	// 'T'->temperature
		outputBuf[3]=hdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}


/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
	if(huart==&huart1) // Motor Board receive data (filter)
	{
		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0]=='M')  //hex :4D - "M" -fixed mainboard
				state=1; //=1
			break;
		case 1: //#1
			if(inputBuf[0]=='A') //hex : 41 -'A'  -fixed master
			{
				state=2; 
			}
			else
				state=0; 
			break;
		case 2://#2
			if(inputBuf[0]=='D' || inputBuf[0]=='W'   || inputBuf[0]=='P' ||inputBuf[0] =='C' || inputBuf[0] == 'B' ||inputBuf[0] == 'S') //'D'->data , 'W' ->wifi
			{
				
				if(inputBuf[0]=='D') run_t.single_data=PANEL_DATA; //receive data is single data
                else if(inputBuf[0]=='W') run_t.single_data = WIFI_INFO; //wifi data
                else if(inputBuf[0]=='P') run_t.single_data = WIFI_TEMP;//temperature 
				else if(inputBuf[0]=='C') run_t.single_data = WIFI_CMD; //command 
				else if(inputBuf[0]=='B') run_t.single_data = WIFI_BEIJING_TIME;
				else if(inputBuf[0]=='S') run_t.single_data = WIFI_WIND_SPEED;
			    state=3;
			}
			else
				state=0;
			break;
            
        case 3:
            if(run_t.single_data==PANEL_DATA){
                 run_t.gReal_humtemp[0]=inputBuf[0]; //Humidity value 
                 state = 4;  
            }
            else if(run_t.single_data == WIFI_INFO){
                  if(inputBuf[0]==0x01)
                     run_t.wifi_connect_flag =1;
                   else 
                      run_t.wifi_connect_flag =0;
                   
                    state=0;
                    run_t.decodeFlag=1;
             
             }
            else if(run_t.single_data == WIFI_TEMP){ //wifi modify temperature of value
                 run_t.wifi_set_temperature=inputBuf[0]; 
                 state=0;
                 run_t.decodeFlag=1;
            }
            else if(run_t.single_data == WIFI_CMD){
                 run_t.wifiCmd[0] =inputBuf[0];
                 state=0;
                 run_t.decodeFlag=1; 
             }
             else if(run_t.single_data == WIFI_WIND_SPEED){
                 run_t.wifi_set_wind_speed=inputBuf[0];
                 state=0;
                 run_t.decodeFlag=1; 

             }
			 else if(run_t.single_data == WIFI_BEIJING_TIME){
			  	 run_t.dispTime_hours  = inputBuf[0];
                 state = 4; 
             }
            
        break;
        
		case 4: //

		 if(run_t.single_data == WIFI_BEIJING_TIME){
				run_t.dispTime_minutes = inputBuf[0];
				state =5;
		 }
		 else if(run_t.single_data==PANEL_DATA){
              run_t.gReal_humtemp[1]=inputBuf[0]; //temperature value
			
		     state=0;
		     run_t.decodeFlag=1;
          }

		 break;
           
        case 5: 
			if(run_t.single_data == WIFI_BEIJING_TIME){
				 run_t.dispTime_seconds = inputBuf[0] + 2;
				 run_t.decodeFlag=1;
			    state=0;
		 }
            
        break;

		
		
		default:
			state=0;
			run_t.decodeFlag=0;  //
		break;

		}
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
	}
}

/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}
	
}


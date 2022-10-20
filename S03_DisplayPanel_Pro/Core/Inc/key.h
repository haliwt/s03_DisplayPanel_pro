#ifndef __KEY_H_
#define __KEY_H_
#include "main.h"


#define INT_KEY_VALUE()              HAL_GPIO_ReadPin(TOUCH_KEY_INT_GPIO_Port ,TOUCH_KEY_INT_Pin)//

#define POWER_KEY_VALUE()            HAL_GPIO_ReadPin(KEY_POWER_GPIO_Port ,KEY_POWER_Pin)
#define MODE_KEY_VALUE()             HAL_GPIO_ReadPin(KEY_MODE_GPIO_Port,KEY_MODE_Pin)
#define DEC_KEY_VALUE()              HAL_GPIO_ReadPin(KEY_DEC_GPIO_Port,KEY_DEC_Pin)
#define ADD_KEY_VALUE()              HAL_GPIO_ReadPin(KEY_ADD_GPIO_Port,KEY_ADD_Pin)


typedef enum _key_status{

   KEY_DOWN,
   KEY_UP,

}key_status;






void SplitDispose_Key(uint8_t value);



#endif 



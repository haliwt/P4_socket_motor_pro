#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "main.h"


#define KEY_VALUE()    LL_GPIO_IsInputPinSet(KEY_GPIO_Port,KEY_Pin)

typedef enum{
  KEY_DOWN,
  KEY_UP

}key_state_t;

uint8_t key_scan(void);

void key_parse_value(uint8_t keyvalue);

uint8_t get_key_value(void);
#endif 


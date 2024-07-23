#ifndef __drv_key_H__
#define __drv_key_H__
#include "stm32f1xx_hal.h" 
#include "main.h"

#define KEY1_PORT GPIOB
#define KEY2_PORT GPIOB

#define KEY1_PIN GPIO_PIN_10
#define KEY2_PIN GPIO_PIN_11

void Key_Init(void);

#endif

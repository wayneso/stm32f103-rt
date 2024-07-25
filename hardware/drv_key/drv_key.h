#ifndef __drv_key_H__
#define __drv_key_H__
#include "stm32f1xx_hal.h" 
#include "main.h"

#define KEY1_PORT GPIOB
#define KEY2_PORT GPIOB
#define KEY3_PORT GPIOB
#define KEY4_PORT GPIOB
#define KEY5_PORT GPIOB


#define KEY1_PIN GPIO_PIN_10
#define KEY2_PIN GPIO_PIN_11
#define KEY3_PIN GPIO_PIN_5
#define KEY4_PIN GPIO_PIN_6
#define KEY5_PIN GPIO_PIN_7

enum k3
{
	HIGH,
	MID,
	LOW,
	AUTO,
	k3_state
};


enum k4
{
	COOL,
	HOT,
	SLEEP,
	k4_state
};

enum k5
{
	OFF,
	ON,
	k5_state
};




void Key_Init(void);

#endif

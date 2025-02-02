/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "rtthread.h"

extern volatile rt_uint8_t Set_temp;
extern volatile rt_uint8_t Set_fan;
extern volatile rt_uint8_t Set_mode;
extern rt_uint8_t Set_nf;

void SystemClock_Config(void);
void Error_Handler(void);
void rt_hw_us_delay(rt_uint32_t us);
void Error_Handler(void);



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

#ifndef __rt_timer_H
#define __rt_timer_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "rtthread.h"
#include <drv_oled.h>
#include "drv_dht11.h"



extern struct rt_timer sleep_timer;

int timer_task(void);

#ifdef __cplusplus
}
#endif

#endif 

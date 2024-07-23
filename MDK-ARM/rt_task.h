#ifndef __rt_task_H
#define __rt_task_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "rtthread.h"
#include <drv_oled.h>
#include "drv_dht11.h"

extern rt_uint8_t temp, humi;
extern DHT11_Data_t dht11_data;

int oled_task(void);
int dht11_task(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

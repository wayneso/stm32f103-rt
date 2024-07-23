#include <rtthread.h>     // RT-Thread操作系统头文件
#include "main.h"
#include "drv_oled.h"     // OLED驱动头文件
#include "drv_dht11.h"    // DHT11传感器驱动头文件
#include "drv_key.h"      // 按键驱动头文件
#include "rt_task.h"      // RT-Thread任务管理头文件
#include "rt_timer.h"     // RT-Thread定时器头文件
#include "multi_button.h"


static struct rt_timer key_timer;  // 定义按键定时器
static struct rt_timer oled_timer;


// 按键定时器回调函数
static void key_timer_callback(void *parameter)
{
    button_ticks();  // 需要周期性调用按键处理函数
}

// 屏幕定时器回调函数
static void oled_timer_callback(void *parameter)
{
    OLED_Update();
}

int timer_task(void)
{
    rt_timer_init(&key_timer,
                  "key_timer",
                  key_timer_callback,
                  0,
                  10,
                  RT_TIMER_FLAG_PERIODIC);  // 初始化按键定时器


    rt_timer_init(&oled_timer,
                  "oled_timer",
                  oled_timer_callback,
                  0,
                  100,
                  RT_TIMER_FLAG_PERIODIC);  // 初始化屏幕定时器

    rt_timer_start(&key_timer);  // 启动按键定时器
    //rt_timer_start(&oled_timer);  // 启动屏幕定时器
    return 0;
}


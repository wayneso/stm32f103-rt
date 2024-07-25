#include <rtthread.h>
#include <drv_oled.h>
#include "drv_dht11.h"
#include "rt_task.h"
#include "rt_timer.h"

//通用任务时间片
#define THREAD_TIMESLICE        10


ALIGN(RT_ALIGN_SIZE)
//定义任务优先级
#define sample_priority         19
#define oled_priority           20
#define dht11_priority          25


// 定义任务堆栈     
static char sample_tasl_stack[256];
static char oled_task_stack[256];
static char dht11_task_stack[256];
// 定义线程控制块
static struct rt_thread task_sample;
static struct rt_thread oled_t;
static struct rt_thread dht11_t;

rt_uint8_t temp, humi;
DHT11_Data_t dht11_data;


// 采样任务入口函数
static void sample_task_entry(void *param)
{
    rt_uint16_t x, y;
    OLED_Clear();
    OLED_Update();
    while (1)
    {
        for (x = 0; x < 128; ++x)
        {
            for (y = 0; y < 64; ++y)
            {
                OLED_DrawPoint(x, y);
            }
        }
        OLED_Update();
        rt_thread_mdelay(1000);
    }
}

// 创建采样任务
int sample(void)
{
    rt_thread_init(&task_sample,
                   "task_sample",
                   sample_task_entry,
                   RT_NULL,
                   &sample_tasl_stack[0],
                   sizeof(sample_tasl_stack),
                   oled_priority,
                   THREAD_TIMESLICE);
    rt_thread_startup(&task_sample);
    return 0;
}

// OLED任务入口函数
static void oled_task_entry(void *param)
{
		if(Set_nf == 1)
		{
			while (1)
			{
					OLED_ClearArea(100,23,15,25);
					OLED_ShowNum(100, 23, humi, 2, OLED_6X8);
					OLED_ShowNum(100, 33, temp, 2,OLED_6X8);
					OLED_UpdateArea(100,23,15,25);
				
					rt_thread_mdelay(1000);
			}
		}

		
}


// 创建OLED任务
int oled_task(void)
{
    rt_thread_init(&oled_t,
                   "oled_t",
                   oled_task_entry,
                   RT_NULL,
                   &oled_task_stack[0],
                   sizeof(oled_task_stack),
                   oled_priority,
                   THREAD_TIMESLICE);
    rt_thread_startup(&oled_t);

    return 0;
}

// DHT11任务入口函数
static void dht11_task_entry(void *param)
{
    while (1)
    {
        DHT11_Read_Data(&dht11_data);
        temp = dht11_data.temperature;
        humi = dht11_data.humidity;
        rt_thread_mdelay(1000);
    }
}

// 创建DHT11任务
int dht11_task(void)
{
    rt_thread_init(&dht11_t,
                   "dht11_t",
                   dht11_task_entry,
                   RT_NULL,
                   &dht11_task_stack[0],
                   sizeof(dht11_task_stack),
                   dht11_priority,
                   THREAD_TIMESLICE);
    rt_thread_startup(&dht11_t);

    return 0;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(sample, task_sample);

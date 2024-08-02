#include <rtthread.h>
#include <drv_oled.h>
#include "drv_dht11.h"
#include "rt_task.h"
#include "rt_timer.h"

//ͨ������ʱ��Ƭ
#define THREAD_TIMESLICE        10


ALIGN(RT_ALIGN_SIZE)
//�����������ȼ�
#define oled_priority           20
#define dht11_priority          25


static char oled_task_stack[150];
static char dht11_task_stack[150];
// �����߳̿��ƿ�
static struct rt_thread oled_t;
static struct rt_thread dht11_t;

rt_uint8_t temp, humi;
DHT11_Data_t dht11_data;


// OLED������ں���
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


// ����OLED����
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

// DHT11������ں���
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

// ����DHT11����
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

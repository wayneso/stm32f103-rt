#include <rtthread.h>     // RT-Thread����ϵͳͷ�ļ�
#include "main.h"
#include "drv_oled.h"     // OLED����ͷ�ļ�
#include "drv_dht11.h"    // DHT11����������ͷ�ļ�
#include "drv_key.h"      // ��������ͷ�ļ�
#include "rt_task.h"      // RT-Thread�������ͷ�ļ�
#include "rt_timer.h"     // RT-Thread��ʱ��ͷ�ļ�
#include "multi_button.h"


static struct rt_timer key_timer;  // ���尴����ʱ��
struct rt_timer sleep_timer;


// ������ʱ���ص�����
static void key_timer_callback(void *parameter)
{
    button_ticks();  // ��Ҫ�����Ե��ð���������
}

// ��Ļ��ʱ���ص�����
static void sleep_timer_callback(void *parameter)
{
   if(Set_nf == 0)
		{
				OLED_Clear();
				OLED_Update();
		}
}	

int timer_task(void)
{
    rt_timer_init(&key_timer,
                  "key_timer",
                  key_timer_callback,
                  0,
                  10,
                  RT_TIMER_FLAG_PERIODIC);  


    rt_timer_init(&sleep_timer,
                  "sleep_timer",
                  sleep_timer_callback,
                  0,
                  3000,
                  RT_TIMER_FLAG_ONE_SHOT);  

    rt_timer_start(&key_timer);  
    return 0;
}


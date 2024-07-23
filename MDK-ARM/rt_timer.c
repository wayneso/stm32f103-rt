#include <rtthread.h>     // RT-Thread����ϵͳͷ�ļ�
#include "main.h"
#include "drv_oled.h"     // OLED����ͷ�ļ�
#include "drv_dht11.h"    // DHT11����������ͷ�ļ�
#include "drv_key.h"      // ��������ͷ�ļ�
#include "rt_task.h"      // RT-Thread�������ͷ�ļ�
#include "rt_timer.h"     // RT-Thread��ʱ��ͷ�ļ�
#include "multi_button.h"


static struct rt_timer key_timer;  // ���尴����ʱ��
static struct rt_timer oled_timer;


// ������ʱ���ص�����
static void key_timer_callback(void *parameter)
{
    button_ticks();  // ��Ҫ�����Ե��ð���������
}

// ��Ļ��ʱ���ص�����
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
                  RT_TIMER_FLAG_PERIODIC);  // ��ʼ��������ʱ��


    rt_timer_init(&oled_timer,
                  "oled_timer",
                  oled_timer_callback,
                  0,
                  100,
                  RT_TIMER_FLAG_PERIODIC);  // ��ʼ����Ļ��ʱ��

    rt_timer_start(&key_timer);  // ����������ʱ��
    //rt_timer_start(&oled_timer);  // ������Ļ��ʱ��
    return 0;
}


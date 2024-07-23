#include "multi_button.h"
#include "drv_key.h"
#include "main.h"
#include "rtthread.h"
#include "drv_oled.h"


enum Button_IDs {
	btn1_id,
	btn2_id,
};

struct Button btn1;
struct Button btn2;

uint8_t read_button_GPIO(uint8_t button_id)
{
	switch(button_id)
	{
		case btn1_id:
			return HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN);
		case btn2_id:
			return HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN);
		default:
			return 0;
	}
}

void BTN1_PRESS_DOWN_Handler(void* btn)
{
	  rt_kprintf("key1 is Press Down\n");
    Set_temp--;
    if (Set_temp <= 16) {
        Set_temp = 16;
    }
				OLED_ClearArea(35,23,15,25);
        OLED_ShowNum(35, 23, Set_temp, 2, OLED_8X16);
				OLED_UpdateArea(35,23,15,25);
    rt_kprintf("Set_temp:%d\n",Set_temp);
}

void BTN2_PRESS_DOWN_Handler(void* btn)
{
	  rt_kprintf("key2 is Press down\n");
    Set_temp++;
    if (Set_temp >= 32) {
        Set_temp = 32;
    }
				OLED_ClearArea(35,23,15,25);
        OLED_ShowNum(35, 23, Set_temp, 2, OLED_8X16);
				OLED_UpdateArea(35,23,15,25);
    rt_kprintf("Set_temp:%d\n",Set_temp);
}


void Key_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};  // 定义 GPIO 初始化结构体

    __HAL_RCC_GPIOB_CLK_ENABLE();  // 使能 GPIOB 时钟

    GPIO_InitStruct.Pin = KEY1_PIN | KEY2_PIN;  // 设置引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;  // 设置引脚模式为推挽输出
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		
    HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);  // 初始化引脚

		
		button_init(&btn1, read_button_GPIO, 1, btn1_id);
		button_init(&btn2, read_button_GPIO, 1, btn2_id);

		button_attach(&btn1, PRESS_DOWN, BTN1_PRESS_DOWN_Handler);

		button_attach(&btn2, PRESS_DOWN, BTN2_PRESS_DOWN_Handler);


		button_start(&btn1);
		button_start(&btn2);

};

#include "multi_button.h"
#include "drv_key.h"
#include "main.h"
#include "rtthread.h"
#include "drv_oled.h"
#include "rt_timer.h"


rt_uint8_t k3_count = 0;
rt_uint8_t k4_count = 0;
rt_uint8_t k5_count = 0;


enum Button_IDs {
	btn1_id,
	btn2_id,
	btn3_id,
	btn4_id,
	btn5_id,
	
};

struct Button btn1;
struct Button btn2;
struct Button btn3;
struct Button btn4;
struct Button btn5;

uint8_t read_button_GPIO(uint8_t button_id)
{
	switch(button_id)
	{
		case btn1_id:
			return HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN);
		case btn2_id:
			return HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN);
		case btn3_id:
			return HAL_GPIO_ReadPin(KEY3_PORT, KEY3_PIN);
		case btn4_id:
			return HAL_GPIO_ReadPin(KEY4_PORT, KEY4_PIN);
		case btn5_id:
			return HAL_GPIO_ReadPin(KEY5_PORT, KEY5_PIN);
		default:
			return 0;
	}
}

void BTN1_PRESS_DOWN_Handler(void* btn)
{
		if(Set_nf == 1)
		{	
			OLED_wakeup();
    Set_temp--;
    if (Set_temp <= 16) 
			{
        Set_temp = 16;
			}
				OLED_ClearArea(35,23,15,25);
        OLED_ShowNum(35, 23, Set_temp, 2, OLED_8X16);
				OLED_UpdateArea(35,23,15,25);
		}
}

void BTN2_PRESS_DOWN_Handler(void* btn)
{
		if(Set_nf == 1)
		{
			OLED_wakeup();
    Set_temp++;
    if (Set_temp >= 32) {
        Set_temp = 32;
    }
				OLED_ClearArea(35,23,15,25);
        OLED_ShowNum(35, 23, Set_temp, 2, OLED_8X16);
				OLED_UpdateArea(35,23,15,25);
		}
}

void BTN3_PRESS_DOWN_Handler(void* btn)
{
		if(Set_nf == 1)
		{
			OLED_wakeup();
				k3_count = Set_fan;
				k3_count++;
				Set_fan = k3_count % k3_state;
				OLED_ClearArea(30,3,97,9);
				switch(Set_fan)
				{
					case HIGH:
						OLED_ShowString(30,4,"HI",OLED_6X8);
						break;
					case MID:
						OLED_ShowString(50,4,"MID",OLED_6X8);
						break;
					case LOW:
						OLED_ShowString(75,4,"LOW",OLED_6X8);
						break;
					case AUTO:
						OLED_ShowString(100,4,"AUTO",OLED_6X8);
						break;
					};	
					OLED_UpdateArea(30,3,97,9);
	}
}

void BTN4_PRESS_DOWN_Handler(void* btn)
{
		if(Set_nf == 1)
		{
			OLED_wakeup();
				k4_count = Set_mode;
				k4_count++;
				Set_mode = k4_count % k4_state;
				OLED_ClearArea(35,52,92,9);
				switch(Set_mode)
				{
					case COOL:
						OLED_ShowString(35,52,"COOL",OLED_6X8);
						break;
					case HOT:
						OLED_ShowString(65,52,"AIR SUPPLY",OLED_6X8);
						break;
					case SLEEP:
						OLED_ShowString(90,52,"SLEEP",OLED_6X8);
						break;

				};	
				OLED_UpdateArea(35,52,92,9);
				
		}

}

void BTN5_PRESS_DOWN_Handler(void* btn)
{
		k5_count = Set_nf;
		k5_count++;
		Set_nf = k5_count % k5_state;
		
		switch (Set_nf)
		{
				case OFF:
					OLED_Clear();
					OLED_ShowString(30,25,"TUNN OFF!",OLED_8X16);
					OLED_Update();
					break;
				case ON:
					OLED_wakeup();
					break;
		}
}

void Key_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};  // 定义 GPIO 初始化结构体

    __HAL_RCC_GPIOB_CLK_ENABLE();  // 使能 GPIOB 时钟

    GPIO_InitStruct.Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN | KEY5_PIN;  // 设置引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;  // 设置引脚模式为推挽输出
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		
    HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);  // 初始化引脚

		
		button_init(&btn1, read_button_GPIO, 1, btn1_id);
		button_init(&btn2, read_button_GPIO, 1, btn2_id);
		button_init(&btn3, read_button_GPIO, 1, btn3_id);
		button_init(&btn4, read_button_GPIO, 1, btn4_id);
		button_init(&btn5, read_button_GPIO, 1, btn5_id);

		button_attach(&btn1, PRESS_DOWN, BTN1_PRESS_DOWN_Handler);
		button_attach(&btn2, PRESS_DOWN, BTN2_PRESS_DOWN_Handler);
		button_attach(&btn3, PRESS_DOWN, BTN3_PRESS_DOWN_Handler);
		button_attach(&btn4, PRESS_DOWN, BTN4_PRESS_DOWN_Handler);
		button_attach(&btn5, PRESS_DOWN, BTN5_PRESS_DOWN_Handler);

		button_start(&btn1);
		button_start(&btn2);
		button_start(&btn3);
		button_start(&btn4);
		button_start(&btn5);


};

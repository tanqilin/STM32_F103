
#include "led.h"
#include "./systick/systick.h"

// 实现头文件 led.h中的方法
void LED_GPIO_Config(void){
	
			/* 声明一个端口结构体 */
			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* 设置外部定时器 */
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	
			/*选择要控制的GPIOC引脚*/															   
			GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN | LED2_GPIO_PIN;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
			/*调用库函数，初始化GPIOC*/
			GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);		

			GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
			GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);		
			GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
}


// 关闭所有灯
void Close_All_Led(){
			GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);		
			GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
}


// 跑马灯
void Run_Horse_Light(void){		
			/* 打开LED1	*/
			GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
			Systick_DelayMs(250);
				
			// 关闭所有灯
			Close_All_Led();
			Systick_DelayMs(100);
	
			/* 打开LED2	*/
			GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
			Systick_DelayMs(250);
	
			Close_All_Led();
			Systick_DelayMs(100);
}

// 编译器要求末尾要以空行为结束否则会有警告


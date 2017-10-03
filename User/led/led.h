#ifndef __LED_H
#define	__LED_H

// 为了防止多个文件调用该文件时产生多次编译，所以定义一个宏来判断

#include "stm32f10x.h"

#define LED1_GPIO_PIN		GPIO_Pin_5		// 黄色 LED
#define LED2_GPIO_PIN		GPIO_Pin_6		// 蓝色 LED

#define LED_GPIO_PORT	GPIOE					// 使用的端口


#define ON  1
#define OFF 0

// LED1 黄色灯
#define LED_Y(a) if (a) \
				GPIO_ResetBits(LED_GPIO_PORT,GPIO_Pin_0);\
				else 	\
				GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_0)

// LED2 蓝色灯
#define LED_B(a) if (a) \
				GPIO_ResetBits(LED_GPIO_PORT,GPIO_Pin_1);\
				else 	\
				GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_1)
				

void LED_GPIO_Config(void);

void Run_Horse_Light(void);

void Close_All_Led(void);
#endif

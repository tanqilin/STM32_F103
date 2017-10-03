#ifndef __LED_H
#define	__LED_H

// Ϊ�˷�ֹ����ļ����ø��ļ�ʱ������α��룬���Զ���һ�������ж�

#include "stm32f10x.h"

#define LED1_GPIO_PIN		GPIO_Pin_5		// ��ɫ LED
#define LED2_GPIO_PIN		GPIO_Pin_6		// ��ɫ LED

#define LED_GPIO_PORT	GPIOE					// ʹ�õĶ˿�


#define ON  1
#define OFF 0

// LED1 ��ɫ��
#define LED_Y(a) if (a) \
				GPIO_ResetBits(LED_GPIO_PORT,GPIO_Pin_0);\
				else 	\
				GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_0)

// LED2 ��ɫ��
#define LED_B(a) if (a) \
				GPIO_ResetBits(LED_GPIO_PORT,GPIO_Pin_1);\
				else 	\
				GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_1)
				

void LED_GPIO_Config(void);

void Run_Horse_Light(void);

void Close_All_Led(void);
#endif

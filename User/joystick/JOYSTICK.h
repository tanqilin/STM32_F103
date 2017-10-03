
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stm32f10x.h"

#define JOY_PIN_X		GPIO_Pin_2
#define JOY_PIN_Y		GPIO_Pin_3

#define JOY_GPIO		GPIOE

#define Read_Pin_X() GPIO_ReadInputDataBit(JOY_GPIO,JOY_PIN_X)
#define Read_Pin_Y() GPIO_ReadInputDataBit(JOY_GPIO,JOY_PIN_Y)

void JOY_Config(void);

#endif


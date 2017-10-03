
#ifndef __MACHINE_H
#define __MACHINE_H

// 步进电机控制
#include "stm32f10x.h"
#include "./usart/bsp_usart.h" 

#define MACHINE_DIRE			GPIO_Pin_7			// 方向端口
#define MACHINE_ENABLE		GPIO_Pin_8			// 使能端口
#define MACHINE_PULSE			GPIO_Pin_9			// 脉冲端口

#define MACHINE_PORT		GPIOB							// 使用的端口

#define ON  1
#define OFF 0

#define LEFT  0
#define RIGHT 1
				
// 电机使能控制
#define Machine(a)	if (a)	\
					GPIO_SetBits(GPIOB,MACHINE_ENABLE);\
					else		\
					GPIO_ResetBits(GPIOB,MACHINE_ENABLE)

// 电机转动方向
#define MachineDire(a) if (a)	\
					GPIO_SetBits(GPIOB,MACHINE_DIRE);\
					else		\
					GPIO_ResetBits(GPIOB,MACHINE_DIRE)
					
void Machine_Config(void);
void Machine_Ctr(uint16_t direction,uint16_t pulse,uint32_t time);

#endif

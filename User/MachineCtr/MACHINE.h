
#ifndef __MACHINE_H
#define __MACHINE_H

// �����������
#include "stm32f10x.h"
#include "./usart/bsp_usart.h" 

#define MACHINE_DIRE			GPIO_Pin_7			// ����˿�
#define MACHINE_ENABLE		GPIO_Pin_8			// ʹ�ܶ˿�
#define MACHINE_PULSE			GPIO_Pin_9			// ����˿�

#define MACHINE_PORT		GPIOB							// ʹ�õĶ˿�

#define ON  1
#define OFF 0

#define LEFT  0
#define RIGHT 1
				
// ���ʹ�ܿ���
#define Machine(a)	if (a)	\
					GPIO_SetBits(GPIOB,MACHINE_ENABLE);\
					else		\
					GPIO_ResetBits(GPIOB,MACHINE_ENABLE)

// ���ת������
#define MachineDire(a) if (a)	\
					GPIO_SetBits(GPIOB,MACHINE_DIRE);\
					else		\
					GPIO_ResetBits(GPIOB,MACHINE_DIRE)
					
void Machine_Config(void);
void Machine_Ctr(uint16_t direction,uint16_t pulse,uint32_t time);

#endif

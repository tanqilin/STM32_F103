
#ifndef __FANCTR_H
#define __FANCTR_H

#include "stm32f10x.h"


#define EAST_FAN 	GPIO_Pin_4		// ��
#define SOUTH_FAN	GPIO_Pin_5		// ��
#define WEST_FAN	GPIO_Pin_6		// ��
#define NORTH_FAN GPIO_Pin_7		// ��

#define FAN_GPIO	GPIOA

#define ON 	1
#define OFF	0

// ��
#define CtrEast_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,EAST_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,EAST_FAN)

// ��
#define CtrSouth_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,SOUTH_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,SOUTH_FAN)
	
// ��
#define CtrWest_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,WEST_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,WEST_FAN)
	
// ��
#define CtrNorth_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,NORTH_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,NORTH_FAN)
					
void FAN_Config(void);
void CtrFan_CloseAll(void);
void CtrFan_Dire(uint16_t com);		// ���ڿ��ưڶ�����
void AutoFan_Dire(float adxl,uint16_t xAng,uint16_t yAng); 						// �Զ������ڶ��Ƕ�
#endif


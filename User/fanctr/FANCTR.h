
#ifndef __FANCTR_H
#define __FANCTR_H

#include "stm32f10x.h"


#define EAST_FAN 	GPIO_Pin_4		// 东
#define SOUTH_FAN	GPIO_Pin_5		// 南
#define WEST_FAN	GPIO_Pin_6		// 西
#define NORTH_FAN GPIO_Pin_7		// 北

#define FAN_GPIO	GPIOA

#define ON 	1
#define OFF	0

// 东
#define CtrEast_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,EAST_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,EAST_FAN)

// 南
#define CtrSouth_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,SOUTH_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,SOUTH_FAN)
	
// 西
#define CtrWest_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,WEST_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,WEST_FAN)
	
// 北
#define CtrNorth_fan(a) if (a) \
				GPIO_ResetBits(FAN_GPIO,NORTH_FAN);\
				else	\
				GPIO_SetBits(FAN_GPIO,NORTH_FAN)
					
void FAN_Config(void);
void CtrFan_CloseAll(void);
void CtrFan_Dire(uint16_t com);		// 串口控制摆动方向
void AutoFan_Dire(float adxl,uint16_t xAng,uint16_t yAng); 						// 自动纠正摆动角度
#endif


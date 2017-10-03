
#ifndef __HDT11_H
#define __HDT11_H

#include "stm32f10x.h"

#define HIGH  1
#define LOW   0

#define HDT11_GPIO_PIN 	GPIO_Pin_12		// HDT11传感器数据管脚
#define HDT11_GPIO 			GPIOE

typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
}DHT11_Data_TypeDef;

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(HDT11_GPIO,HDT11_GPIO_PIN);\
					else		\
					GPIO_ResetBits(HDT11_GPIO,HDT11_GPIO_PIN)

					
//读取引脚的电平
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(HDT11_GPIO,HDT11_GPIO_PIN)

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
static uint8_t Read_Byte(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
					
#endif



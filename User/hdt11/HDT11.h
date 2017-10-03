
#ifndef __HDT11_H
#define __HDT11_H

#include "stm32f10x.h"

#define HIGH  1
#define LOW   0

#define HDT11_GPIO_PIN 	GPIO_Pin_12		// HDT11���������ݹܽ�
#define HDT11_GPIO 			GPIOE

typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;

//���κ꣬��������������һ��ʹ��,����ߵ�ƽ��͵�ƽ
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(HDT11_GPIO,HDT11_GPIO_PIN);\
					else		\
					GPIO_ResetBits(HDT11_GPIO,HDT11_GPIO_PIN)

					
//��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(HDT11_GPIO,HDT11_GPIO_PIN)

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
static uint8_t Read_Byte(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
					
#endif



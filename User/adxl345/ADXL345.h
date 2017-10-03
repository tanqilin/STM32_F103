
#ifndef __ADXL345_H
#define __ADXL345_H

#include "stm32f10x.h"
#include "./usart/bsp_usart.h" 


#define I2C2_SLAVE_ADDRESS7     0xA6	 
//0x3A

#define  DEVID  0x00 
#define THRESH_TAP 0x1D 
#define OFSX  0x1E 
#define OFSY 0x1F 
#define OFSZ 0x20 
#define DUR 0x21 
#define Latent 0x22 
#define Window 0x23 
#define THRESH_ACT 0x24 
#define THRESH_INACT 0x25 
#define TIME_INACT 0x26 
#define ACT_INACT_CTL 0x27 
#define THRESH_FF 0x28 
#define TIME_FF 0x29  
#define TAP_AXES 0x2A 
#define ACT_TAP_STATUS 0x2B 
#define BW_RATE 0x2C 
#define POWER_CTL 0x2D 
#define INT_ENABLE 0x2E 
#define INT_MAP 0x2F 
#define INT_SOURCE 0x30 
#define DATA_FORMAT 0x31 
#define DATAX0 0x32 
#define DATAX1 0x33 
#define DATAY0 0x34 
#define DATAY1 0x35 
#define DATAZ0 0x36 
#define DATAZ1 0x37 
#define FIFO_CTL 0x38 
#define FIFO_STATUS 0x39 

typedef struct
{
	u16 x;
	u16 y;
	u16 z;
	double xangle;
	double yangle;
}ADXL345_Data_TypeDef;

void Iic_Init(void);
//IIC初始化
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte);
//I2C写数据
unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address);
//I2C读数据
ADXL345_Data_TypeDef ADXL345_GetValue(void);   //取数据
void ADXL345_Config(void);
void SendAdxlDataToUsart(ADXL345_Data_TypeDef GravityValue);

#endif

/* main 函数中使用方式
						
	// 配置 ADXL345 传感器
	ADXL345_Config();

	// 打印倾角传感器值
	GravityValue = ADXL345_GetValue();
	SendAdxlDataToUsart(GravityValue);
				
*/			



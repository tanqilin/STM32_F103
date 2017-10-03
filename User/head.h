#ifndef __HEAD_H
#define __HEAD_H


#include "stm32f10x.h"
#include "./led/led.h"
#include "./usart/bsp_usart.h" 
#include "./systick/systick.h"
#include "./MachineCtr/MACHINE.h"
#include "./hdt11/HDT11.h"
//#include "./adxl345/ADXL345.h"
//#include "./hcsr04/HCSR04.h"
//#include "./fanctr/FANCTR.h"
//#include "./joystick/JOYSTICK.h"
#include "./wifi/WIFI.h"
#include "./wifi/bsp_esp8266.h"
#include "./tm7705/bsp_tm7705.h"
#include "./lcd1602/LCD1602.h"

/* 电机控制命令 */
uint16_t response;	
uint16_t timeMs = 1;
uint16_t pulse = 0x00;

/* 风扇控制命令 */
uint16_t fanCom;
uint16_t xAngle = 15;
uint16_t yAngle = 15;

/* 电流电压 */
uint16_t adc1,adc2;

DHT11_Data_TypeDef DHT11_Data;
//ADXL345_Data_TypeDef GravityValue;


#endif


/*
*********************************************************************************************************
*
*	ģ������ : TM7705 ����ģ��(2ͨ����PGA��16λADC)
*	�ļ����� : bsp_tm7705.h
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "stm32f10x.h"
#include "./systick/systick.h"
#include "./usart/bsp_usart.h" 

#ifndef _BSP_TM7705_H
#define _BSP_TM7705_H


void TM7705_Config(void);
void TM7705_CalibSelf(uint8_t _ch);
void TM7705_SytemCalibZero(uint8_t _ch);
void TM7705_SytemCalibFull(uint8_t _ch);
void TM7705_ReadCH1CH2(void);
uint8_t TM7705_Type(uint16_t u,uint16_t i);	// �����õ�������
uint16_t TM7705_ReadAdc(uint8_t _ch);

void TM7705_WriteReg(uint8_t _RegID, uint32_t _RegValue);
uint32_t TM7705_ReadReg(uint8_t _RegID);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/

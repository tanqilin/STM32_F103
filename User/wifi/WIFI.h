
#ifndef __WIFI_H
#define __WIFI_H

#include "stm32f10x.h"
#include <stdio.h>

/** 
  * 串口宏定义，不同的串口挂载的总线不一样，移植时需要修改这几个宏
  */
// 串口2-USART2
#define  WIFI_USARTx                   USART2
#define  WIFI_USART_CLK                RCC_APB1Periph_USART2
#define  WIFI_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  WIFI_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  WIFI_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  WIFI_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  WIFI_USART_TX_GPIO_PORT       GPIOA   
#define  WIFI_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  WIFI_USART_RX_GPIO_PORT       GPIOA
#define  WIFI_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  WIFI_USART_IRQ                USART2_IRQn
#define  WIFI_USART_IRQHandler         USART2_IRQHandler


void WIFI_Config(void);
void WIFI_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void WIFI_SendString( USART_TypeDef * pUSARTx, char *str);
void WIFI_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void WIFI_SendFourByte(USART_TypeDef * pUSARTx, uint32_t ch);

#endif

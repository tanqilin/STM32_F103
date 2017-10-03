#ifndef __LCD1602_H
#define	__LCD1602_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on

	RS ========== PA0		:����/���� 0,����; 1,����
	RW ========== PA1		:��/д 0,д��; 1,��ȡ
	EN ========== PA2		:ʹ��
	
*/

#define RS_SET(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define RW_SET(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_1)

#define EN_SET(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_2)

#define  DataPort(x) GPIOA->ODR=(GPIOA->ODR&0xffffff00)|(x&0xff);//����8λ���ݲ����˿�					
					
void LCD_GPIO_Config(void);
void LCD_Write_Com(unsigned char com);
void LCD_Write_Data(unsigned char Data);
void LCD_Clear(void);
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s); 
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data); 
void LCD_Write_U(uint16_t ui);
void LCD_Write_A(uint16_t ui);
void LCD_Write_P(uint16_t ui);
void LCD_Write_T(uint8_t type);	// ���
void LCD1602_Config(void);					
	
					
					
#endif /* __LED_H */

/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��lcd.c
 * ����    ��lcd Ӧ�ú�����         
**********************************************************************************/
#include "LCD1602.h"
#include "./systick/systick.h"
#include "./usart/bsp_usart.h" 

/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;	/*�޸�*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	 /*�޸�*/
}


/*------------------------------------------------
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
 Systick_DelayMs(5);
 RS_SET(0); 
 RW_SET(0); 
 EN_SET(1); 
 DataPort(com);  
 EN_SET(0);
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
 Systick_DelayMs(5);
 RS_SET(1); 
 RW_SET(0); 
 EN_SET(1); 
 DataPort(Data); 
 EN_SET(0);
 }

/*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 Systick_DelayMs(5);
 }
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     //��ʾ��һ��
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
/*------------------------------------------------
              д���ַ�����
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
	LCD_Write_Data( Data);  
 }
 
 /*
		��ʾ����,��ʾ��ѹ
 */
 void LCD_Write_U(uint16_t ui){
		uint8_t p = 0x80+2;
		if(ui == 0)
			LCD_Write_Data(0x30);
			
		LCD_Write_Char(0,0,'U');
		LCD_Write_Char(1,0,':');
		LCD_Write_Com(p);   // λ
		LCD_Write_Data(0x30+(ui/1000));
		LCD_Write_Com(p+1);
		LCD_Write_Data(0x2E);	
		LCD_Write_Com(p+2);
		LCD_Write_Data(0x30+((ui%1000)/100));
		LCD_Write_Com(p+3);
		LCD_Write_Data(0x30+((ui%100)/10));
		LCD_Write_Com(p+4);
		LCD_Write_Data(0x56);     
 }
 
 
 /*
		��ʾ����,��ʾ����
 */
 void LCD_Write_A(uint16_t ui){
			uint8_t p = 0x80+10; 
			LCD_Write_Char(8,0,'I');
			LCD_Write_Char(9,0,':');
			LCD_Write_Com(p);   // λ

			if(ui>1000)
				LCD_Write_Data(0x30+(ui/1000));
			if(ui == 0)
				LCD_Write_Data(0x30);
			
			LCD_Write_Com(p+1);
			LCD_Write_Data(0x30+((ui%1000)/100));
			LCD_Write_Com(p+2);
			LCD_Write_Data(0x30+((ui%100)/10));
			LCD_Write_Com(p+3);
			LCD_Write_Data(0x30+((ui%10)));
			LCD_Write_Com(p+4);
			LCD_Write_Data(0x4D);
			LCD_Write_Com(p+5);
			LCD_Write_Data(0x41);      
 }
 
 /*
	��ʾ����
 */
 void LCD_Write_P(uint16_t ui){
			uint8_t p = 0xC0+2;
			
			LCD_Write_Char(0,1,'P');
			LCD_Write_Char(1,1,':');
			LCD_Write_Com(p);   // λ

			if(ui>1000){
				LCD_Write_Data(0x30+(ui/1000));
				LCD_Write_Com(p+1);
				LCD_Write_Data(0x2E);	
				LCD_Write_Com(p+2);
				LCD_Write_Data(0x30+((ui%1000)/100));
				LCD_Write_Com(p+3);
				LCD_Write_Data(0x30+((ui%100)/10));
				LCD_Write_Com(p+4);
				LCD_Write_Data(0x57);
			}else{
				LCD_Write_Data(0x30);
				LCD_Write_Com(p+1);
				LCD_Write_Data(0x2E);	
				LCD_Write_Com(p+2);
				LCD_Write_Data(0x30+((ui%1000)/100));
				LCD_Write_Com(p+3);
				LCD_Write_Data(0x30+((ui%100)/10));
				LCD_Write_Com(p+4);
				LCD_Write_Data(0x57);
			}
 }
 
 /*
	��ʾ�õ�������
 */
 void LCD_Write_T(uint8_t type){
	
			LCD_Write_Char(8,1,'T');
			LCD_Write_Char(9,1,':');
			LCD_Write_Char(10,1,(0x30+type));
 }
 
/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
 void LCD1602_Config(void) 
 {
	 LCD_GPIO_Config();
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38); 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38); 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
 }
   



































/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

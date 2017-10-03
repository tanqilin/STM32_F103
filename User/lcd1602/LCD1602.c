/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：lcd.c
 * 描述    ：lcd 应用函数库         
**********************************************************************************/
#include "LCD1602.h"
#include "./systick/systick.h"
#include "./usart/bsp_usart.h" 

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;	/*修改*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	 /*修改*/
}


/*------------------------------------------------
              写入命令函数
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
              写入数据函数
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
                清屏函数
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 Systick_DelayMs(5);
 }
/*------------------------------------------------
              写入字符串函数
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     //表示第一行
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);      //表示第二行
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
/*------------------------------------------------
              写入字符函数
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
		显示整数,显示电压
 */
 void LCD_Write_U(uint16_t ui){
		uint8_t p = 0x80+2;
		if(ui == 0)
			LCD_Write_Data(0x30);
			
		LCD_Write_Char(0,0,'U');
		LCD_Write_Char(1,0,':');
		LCD_Write_Com(p);   // 位
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
		显示整数,显示电流
 */
 void LCD_Write_A(uint16_t ui){
			uint8_t p = 0x80+10; 
			LCD_Write_Char(8,0,'I');
			LCD_Write_Char(9,0,':');
			LCD_Write_Com(p);   // 位

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
	显示功率
 */
 void LCD_Write_P(uint16_t ui){
			uint8_t p = 0xC0+2;
			
			LCD_Write_Char(0,1,'P');
			LCD_Write_Char(1,1,':');
			LCD_Write_Com(p);   // 位

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
	显示用电器类型
 */
 void LCD_Write_T(uint8_t type){
	
			LCD_Write_Char(8,1,'T');
			LCD_Write_Char(9,1,':');
			LCD_Write_Char(10,1,(0x30+type));
 }
 
/*------------------------------------------------
              初始化函数
------------------------------------------------*/
 void LCD1602_Config(void) 
 {
	 LCD_GPIO_Config();
   LCD_Write_Com(0x38);    /*显示模式设置*/ 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38); 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38); 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*显示关闭*/ 
   LCD_Write_Com(0x01);    /*显示清屏*/ 
   LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
   Systick_DelayMs(5); 
   LCD_Write_Com(0x0C);    /*显示开及光标设置*/
 }
   



































/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

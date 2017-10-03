
#include "head.h"

int main(void)
{		
	/* 初始化LED灯 */
	LED_GPIO_Config();
	
  /* 初始化USART串口通信 */
	USART_Config();
		
	// 初始化电机
//	Machine_Config();
	
	// 初始化温度传感器
//	DHT11_GPIO_Config();                

	// 初始化WIFI串口
//	ESP8266_Config();
	
	// 初始化 TM7055
	TM7705_Config();

	// 初始化液晶屏
	LCD1602_Config();
	LCD_Clear();	//清屏
	
	TM7705_ReadCH1CH2();
	printf("CH1=%d,ADC:%d\r\n",adc1,((adc1 * 5000) / 65535));
	printf("CH2=%d,ADC:%d\r\n",adc2,((adc2 * 5000) / 65535));
	

  while(1)
	{	
		Run_Horse_Light();

		TM7705_ReadCH1CH2();

		// 显示电压,电流,功率,类别 
		LCD_Write_U((adc1 * 5000) / 65535);
		LCD_Write_A((adc2 * 5000) / 65535);
		LCD_Write_P(((adc1 * 5000) / 65535)*0.15);
		LCD_Write_T(0x07);

		Systick_DelayMs(100);
	}	
}

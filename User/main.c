
#include "head.h"

int main(void)
{		
	/* ��ʼ��LED�� */
	LED_GPIO_Config();
	
  /* ��ʼ��USART����ͨ�� */
	USART_Config();
		
	// ��ʼ�����
//	Machine_Config();
	
	// ��ʼ���¶ȴ�����
//	DHT11_GPIO_Config();                

	// ��ʼ��WIFI����
//	ESP8266_Config();
	
	// ��ʼ�� TM7055
	TM7705_Config();

	// ��ʼ��Һ����
	LCD1602_Config();
	LCD_Clear();	//����
	
	TM7705_ReadCH1CH2();
	printf("CH1=%d,ADC:%d\r\n",adc1,((adc1 * 5000) / 65535));
	printf("CH2=%d,ADC:%d\r\n",adc2,((adc2 * 5000) / 65535));
	

  while(1)
	{	
		Run_Horse_Light();

		TM7705_ReadCH1CH2();

		// ��ʾ��ѹ,����,����,��� 
		LCD_Write_U((adc1 * 5000) / 65535);
		LCD_Write_A((adc2 * 5000) / 65535);
		LCD_Write_P(((adc1 * 5000) / 65535)*0.15);
		LCD_Write_T(0x07);

		Systick_DelayMs(100);
	}	
}

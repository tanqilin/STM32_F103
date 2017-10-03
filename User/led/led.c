
#include "led.h"
#include "./systick/systick.h"

// ʵ��ͷ�ļ� led.h�еķ���
void LED_GPIO_Config(void){
	
			/* ����һ���˿ڽṹ�� */
			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* �����ⲿ��ʱ�� */
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	
			/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
			GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN | LED2_GPIO_PIN;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
			/*���ÿ⺯������ʼ��GPIOC*/
			GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);		

			GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
			GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);		
			GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
}


// �ر����е�
void Close_All_Led(){
			GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);		
			GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
}


// �����
void Run_Horse_Light(void){		
			/* ��LED1	*/
			GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
			Systick_DelayMs(250);
				
			// �ر����е�
			Close_All_Led();
			Systick_DelayMs(100);
	
			/* ��LED2	*/
			GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN);	 
			Systick_DelayMs(250);
	
			Close_All_Led();
			Systick_DelayMs(100);
}

// ������Ҫ��ĩβҪ�Կ���Ϊ����������о���


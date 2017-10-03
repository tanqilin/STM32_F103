
#include "MACHINE.h"
#include "./systick/systick.h"
#include "./led/led.h"

// ��ʼ���������
void Machine_Config(void){
			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* �����ⲿ��ʱ�� */
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	
			GPIO_InitStructure.GPIO_Pin = MACHINE_PULSE;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
			/*���ÿ⺯������ʼ��GPIOC*/
			GPIO_Init(MACHINE_PORT, &GPIO_InitStructure);		
	
			// �������� ʹ�ܺͷ����źŵ������ʽ
			GPIO_InitStructure.GPIO_Pin = MACHINE_ENABLE | MACHINE_DIRE;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	
			GPIO_Init(MACHINE_PORT, &GPIO_InitStructure);		
		
			GPIO_SetBits(MACHINE_PORT, MACHINE_ENABLE);	// ʹ��
			GPIO_ResetBits(MACHINE_PORT, MACHINE_PULSE);	// ����
			GPIO_SetBits(MACHINE_PORT, MACHINE_DIRE);	// ����
}

// �������,�������壬ת�٣��Ƕȿ���
void Machine_Ctr(uint16_t direction,uint16_t pulse,uint32_t time){
		uint16_t x = 0;
	
		switch(direction){
			case 0x4F:	// ��
				Close_All_Led();
				Machine( ON );
				LED_Y( ON );
				break;
			case 0x43:	// �ر�
				Close_All_Led();
				Machine( OFF );
				break;
			case 0x4C:	// ��ת
				Close_All_Led();
				MachineDire( LEFT );
				break;
			case 0x52:	// ��ת
				Close_All_Led();
				MachineDire( RIGHT );
				break;
			default:break;
		}
		
		for(x=0; x < pulse ; x++){
			// �������
			GPIO_SetBits(MACHINE_PORT, MACHINE_PULSE);
			Systick_DelayUs(time);
			GPIO_ResetBits(MACHINE_PORT, MACHINE_PULSE);
			Systick_DelayUs(time);
		}
}


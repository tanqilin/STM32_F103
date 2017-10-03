
#include "./hcsr04/HCSR04.h"
#include "./systick/systick.h"

// ���������
void HCSR04_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//������
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG;//TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HCSR04_GPIO,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO;//RX
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(HCSR04_GPIO,&GPIO_InitStructure);
	
	GPIO_SetBits(HCSR04_GPIO,HCSR04_ECHO);
	GPIO_ResetBits(HCSR04_GPIO,HCSR04_TRIG);
}

// ��ȡ������ֵ
float HCSR04_ReadData(){
		float length;
		uint16_t count;
	
		GPIO_SetBits(HCSR04_GPIO,HCSR04_TRIG);
		Systick_DelayUs(20);//���߳���10us�����䳬����
		GPIO_ResetBits(HCSR04_GPIO,HCSR04_TRIG);

		TIM2->CNT=0;//��������0
		while(GPIO_ReadInputDataBit(HCSR04_GPIO,HCSR04_ECHO)==0);//�ȴ�ECHO�Ÿߵ�ƽ		

		while((GPIO_ReadInputDataBit(HCSR04_GPIO,HCSR04_ECHO)==1)&&(TIM2->CNT<TIM2->ARR-10));

		count=TIM2->CNT;//ECHO�ŵ͵�ƽ���ȡ��������ֵ���Ӷ��������ʱ��
		length=count/58.0;
	
		return length;
}


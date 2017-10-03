
#include "./hcsr04/HCSR04.h"
#include "./systick/systick.h"

// 超声波测距
void HCSR04_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//超声波
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

// 读取传感器值
float HCSR04_ReadData(){
		float length;
		uint16_t count;
	
		GPIO_SetBits(HCSR04_GPIO,HCSR04_TRIG);
		Systick_DelayUs(20);//拉高超过10us，发射超声波
		GPIO_ResetBits(HCSR04_GPIO,HCSR04_TRIG);

		TIM2->CNT=0;//计数器清0
		while(GPIO_ReadInputDataBit(HCSR04_GPIO,HCSR04_ECHO)==0);//等待ECHO脚高电平		

		while((GPIO_ReadInputDataBit(HCSR04_GPIO,HCSR04_ECHO)==1)&&(TIM2->CNT<TIM2->ARR-10));

		count=TIM2->CNT;//ECHO脚低电平后读取计数器的值，从而算出往返时间
		length=count/58.0;
	
		return length;
}


#include "JOYSTICK.h"


// ≥ı ºªØ“°∏À
void JOY_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = JOY_PIN_X | JOY_PIN_Y;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	GPIO_Init(JOY_GPIO,&GPIO_InitStructure);
	
	GPIO_ResetBits(JOY_GPIO,JOY_PIN_X);
	GPIO_ResetBits(JOY_GPIO,JOY_PIN_Y);
}



// ³¬Éù²¨²â¾àÄ£¿é
#ifndef __HCSR04_H
#define __HCSR04_H

#include "stm32f10x.h"

#define HCSR04_TRIG			GPIO_Pin_6
#define HCSR04_ECHO			GPIO_Pin_7

#define	HCSR04_GPIO			GPIOB

// ÅäÖÃ³¬Éù²¨¹¤×÷Òý½Å
void HCSR04_Config(void);
float HCSR04_ReadData(void);

#endif


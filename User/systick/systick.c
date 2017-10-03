
#include "systick.h"
#include "core_cm3.h"



// ΢����ʱ�źů�
void Systick_DelayUs(uint32_t us){

	uint32_t i;
	
	SysTick_Config(72);

	for(i=0;i<us;i++){
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// �ص���ʱ��,�ر�ʹ���ź�
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

// ������ʱ����
void Systick_DelayMs(uint32_t ms){

	uint32_t i;
	
	SysTick_Config(72000);

	for(i=0;i<ms;i++){
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// �ص���ʱ��,�ر�ʹ���ź�
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}








#include "MACHINE.h"
#include "./systick/systick.h"
#include "./led/led.h"

// 初始化电机串口
void Machine_Config(void){
			GPIO_InitTypeDef GPIO_InitStructure;
			
			/* 设置外部定时器 */
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	
			GPIO_InitStructure.GPIO_Pin = MACHINE_PULSE;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
			/*调用库函数，初始化GPIOC*/
			GPIO_Init(MACHINE_PORT, &GPIO_InitStructure);		
	
			// 单独设置 使能和方向信号的输出方式
			GPIO_InitStructure.GPIO_Pin = MACHINE_ENABLE | MACHINE_DIRE;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	
			GPIO_Init(MACHINE_PORT, &GPIO_InitStructure);		
		
			GPIO_SetBits(MACHINE_PORT, MACHINE_ENABLE);	// 使能
			GPIO_ResetBits(MACHINE_PORT, MACHINE_PULSE);	// 脉冲
			GPIO_SetBits(MACHINE_PORT, MACHINE_DIRE);	// 方向
}

// 电机控制,方向，脉冲，转速，角度控制
void Machine_Ctr(uint16_t direction,uint16_t pulse,uint32_t time){
		uint16_t x = 0;
	
		switch(direction){
			case 0x4F:	// 打开
				Close_All_Led();
				Machine( ON );
				LED_Y( ON );
				break;
			case 0x43:	// 关闭
				Close_All_Led();
				Machine( OFF );
				break;
			case 0x4C:	// 反转
				Close_All_Led();
				MachineDire( LEFT );
				break;
			case 0x52:	// 正转
				Close_All_Led();
				MachineDire( RIGHT );
				break;
			default:break;
		}
		
		for(x=0; x < pulse ; x++){
			// 电机脉冲
			GPIO_SetBits(MACHINE_PORT, MACHINE_PULSE);
			Systick_DelayUs(time);
			GPIO_ResetBits(MACHINE_PORT, MACHINE_PULSE);
			Systick_DelayUs(time);
		}
}


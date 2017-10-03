
#include "FANCTR.h"

// ��ʼ������
void FAN_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = EAST_FAN | SOUTH_FAN | WEST_FAN | NORTH_FAN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(FAN_GPIO, &GPIO_InitStructure);		
			
	// ����ĸ���������
	GPIO_SetBits(FAN_GPIO,EAST_FAN);
	GPIO_SetBits(FAN_GPIO,SOUTH_FAN);
	GPIO_SetBits(FAN_GPIO,WEST_FAN);
	GPIO_SetBits(FAN_GPIO,NORTH_FAN);
}

// �ر����з���
void CtrFan_CloseAll(){
	CtrEast_fan( OFF );
	CtrSouth_fan( OFF );
	CtrWest_fan( OFF );
	CtrNorth_fan( OFF );
}

// ���Ʒ����ڷ���
void CtrFan_Dire(uint16_t com){
			switch(com){
			case 0x43:	// ��
				CtrFan_CloseAll();
				break;
			case 0x45:	// ��
				CtrFan_CloseAll();
				CtrEast_fan( ON );
				break;
			case 0x53:	// ��
				CtrFan_CloseAll();
				CtrSouth_fan( ON );
				break;
			case 0x57:	// ��
				CtrFan_CloseAll();
				CtrWest_fan( ON );
				break;
			case 0x4e:	// ��
				CtrFan_CloseAll();
				CtrNorth_fan( ON );
				break;
			case 0xA5:	// ����
				CtrFan_CloseAll();
				CtrNorth_fan( ON );
				CtrWest_fan( ON );
				break;
			case 0x93:	// ����
				CtrFan_CloseAll();
				CtrEast_fan( ON );
				CtrNorth_fan( ON );
				break;
			case 0x98:	// ����
				CtrFan_CloseAll();
				CtrEast_fan( ON );
				CtrSouth_fan( ON );
				break;
			case 0xAA:	// ����
				CtrFan_CloseAll();
				CtrWest_fan( ON );
				CtrSouth_fan( ON );
				break;
			default:break;
		}
}

float oldX = 0;

// ���ݽǶ��Զ����Ʒ���
void AutoFan_Dire(float adxl,uint16_t xAng,uint16_t yAng){
	
		// ����������ڶ�
		if( adxl > 0 && adxl < xAng){
			CtrEast_fan( OFF );
			CtrWest_fan( ON );
		}
		else if( adxl < 0 && adxl > (-xAng)){
			CtrEast_fan( ON );
			CtrWest_fan( OFF );
		}
		else{
			CtrEast_fan( OFF );
			CtrWest_fan( OFF );
		}
		
		oldX = adxl;
}




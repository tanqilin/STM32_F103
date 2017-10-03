#include "./adxl345/ADXL345.h"
#include "./systick/systick.h"
#include"math.h"

/**********************************************************************/
/*IIC配置		         				                             							*/
/*																																	  */
/**********************************************************************/
void Iic_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	 I2C_InitTypeDef I2C_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Configure IO connected to IIC*********************/
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
 	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
 	 I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
 	 I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
 	 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
 	 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 	 I2C_InitStructure.I2C_ClockSpeed = 200000;
	 
	 I2C_Cmd(I2C2, ENABLE);   

	 I2C_Init(I2C2, &I2C_InitStructure);
}
/**********************************************************************/
/*IIC写一个字节	         				                              */
/*																	  */
/**********************************************************************/
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	//产生起始条件
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	//等待ACK
	I2C_Send7bitAddress(I2C2,id,I2C_Direction_Transmitter);
	//向设备发送设备地址
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	//等待ACK
	I2C_SendData(I2C2, write_address);
	//寄存器地址
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//等待ACK
	I2C_SendData(I2C2, byte);
	//发送数据
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//发送完成
	I2C_GenerateSTOP(I2C2, ENABLE);
	//产生结束信号
}
/**********************************************************************/
/*IIC读数据	         				                              	  */
/*																	  */
/**********************************************************************/
unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address)
{  
	unsigned char temp; 	

	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  	//等待I2C
  	I2C_GenerateSTART(I2C2, ENABLE);
  	//产生起始信号
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    //EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Transmitter);
	//发送地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  	//EV6
  	I2C_Cmd(I2C2, ENABLE);
 	//重新设置可以清楚EV6
  	I2C_SendData(I2C2, read_address);  
	//发送读得地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  	//EV8 
  	I2C_GenerateSTART(I2C2, ENABLE);
	//重新发送
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	//EV5
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Receiver);
  	//发送读地址
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  	//EV6  
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
	//关闭应答和停止条件产生
    while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	      
    temp = I2C_ReceiveData(I2C2);
   
  	I2C_AcknowledgeConfig(I2C2, ENABLE);

	return temp;
}

void ADXL345_Config(void)
{
	Iic_Init();
	I2C_WriteByte(0xA6,BW_RATE,0x08);   //速率设定为12.5 参考pdf13页
	I2C_WriteByte(0xA6,POWER_CTL,0x08);   //电源工作方式设置
	I2C_WriteByte(0xA6,DATA_FORMAT,0x03);	
}

// 读取传感器，并计算出各值
ADXL345_Data_TypeDef ADXL345_GetValue(void)
{
	ADXL345_Data_TypeDef GravityValue;
	
	GravityValue.x = (u16)I2C_ReadByte(0xA6,DATAX1);
	GravityValue.x <<= 8;
	GravityValue.x += (u16)I2C_ReadByte(0xA6,DATAX0);

	GravityValue.y = (u16)I2C_ReadByte(0xA6,DATAY1);
	GravityValue.y <<= 8;
	GravityValue.y += (u16)I2C_ReadByte(0xA6,DATAY0);

	GravityValue.z = (u16)I2C_ReadByte(0xA6,DATAZ1);
	GravityValue.z <<= 8;
	GravityValue.z += (u16)I2C_ReadByte(0xA6,DATAZ0);

	if(GravityValue.x > 0x01FF)
	{
		GravityValue.x = -GravityValue.x;
		GravityValue.x |= 0x8000;
	}
	if(GravityValue.y > 0x01FF)
	{
		GravityValue.y = -GravityValue.y;
		GravityValue.y |= 0x8000;
	}
	if(GravityValue.z > 0x01FF)
	{
		GravityValue.z = -GravityValue.z;
		GravityValue.z |= 0x8000;
	}

	if(!(GravityValue.z & 0x8000))
	{
		if(GravityValue.x & 0x8000)
		{
			GravityValue.x &= 0x7FFF ;
			if(GravityValue.z == 0)
				GravityValue.xangle = 90;
			else
				GravityValue.xangle = atan((double)GravityValue.x / (double)GravityValue.z) * 57.296;
			GravityValue.x |= 0x8000;
		}
		if(!(GravityValue.x & 0x8000))
		{
			if(GravityValue.z == 0)
				GravityValue.xangle = -90;
			else
				GravityValue.xangle = -atan((double) GravityValue.x / (double)GravityValue.z) * 57.296;
		}

		if(GravityValue.y & 0x8000)
		{
			GravityValue.y &= 0x7FFF ;
			if(GravityValue.z == 0)
				GravityValue.yangle = -90;
			else
				GravityValue.yangle = atan((double)GravityValue.y / (double)GravityValue.z) * 57.296;
			GravityValue.y |= 0x8000;
		}
		if(!(GravityValue.y & 0x8000))
		{
			if(GravityValue.z == 0)
				GravityValue.yangle = 90;
			else
				GravityValue.yangle = -atan((double)GravityValue.y / (double)GravityValue.z) * 57.296;
		}
	}
	else
	{
		GravityValue.z &= 0x7FFF ;
		if(GravityValue.x & 0x8000)
		{
			GravityValue.x &= 0x7FFF ;
			GravityValue.xangle = 180 - atan((double)GravityValue.x / (double)GravityValue.z) * 57.296;
			GravityValue.x |= 0x8000;
		}
		if(!(GravityValue.x & 0x8000))
		{
			GravityValue.xangle = -(180 - atan((double) GravityValue.x / (double)GravityValue.z) * 57.296);
		}

		if(GravityValue.y & 0x8000)
		{
			GravityValue.y &= 0x7FFF ;
			GravityValue.yangle = 180 - atan((double)GravityValue.y / (double)GravityValue.z) * 57.296;
			GravityValue.y |= 0x8000;
		}
		if(!(GravityValue.y & 0x8000))
		{
			GravityValue.yangle = -(180 - atan((double)GravityValue.y / (double)GravityValue.z) * 57.296);
		}
		GravityValue.z |= 0x8000;
	}
	return GravityValue;
}

// 发送传感器数据到串口
void SendAdxlDataToUsart(ADXL345_Data_TypeDef GravityValue){
//	printf("x: %d\n",GravityValue.x/3);
//	printf("y: %d\n",GravityValue.y/3);
	printf("z: %5d , ",GravityValue.z/3);
	printf("x: %f  , ",GravityValue.xangle);	
	printf("y: %f  , \n",GravityValue.yangle);	
}

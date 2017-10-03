
#include "bsp_usart.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern uint16_t response;	// 串口收到命令
extern uint16_t pulse;		// 串口脉冲
extern uint16_t timeMs;		// 转速

extern uint16_t fanCom;		// 转速
extern uint16_t xAngle;
extern uint16_t yAngle;


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}


// 发送一个字符
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

// 发送一个字符串
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}


// 发送两个字符
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

// 发送四个字节
void Usart_SendFourByte(USART_TypeDef * pUSARTx, uint32_t ch)
{
	uint16_t temp_h,temp_l;
	
	// 取出高16位
	temp_h = (ch&0XFFFF0000)>>16;
	
	temp_l = ch&0xFFFF;
	
	// 先发送高16位，再发送低16位
	Usart_SendHalfWord(DEBUG_USARTx,temp_h);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	Usart_SendHalfWord(DEBUG_USARTx,temp_l);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


// 使用printf()向电脑发送数据
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


// 使用getchar()从电脑获取输入
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}




uint16_t type;

// 获取串口信息，高位，低位
void getRsponseData(uint16_t sign,uint16_t str_h,uint16_t str_l){			
		type = sign;
		
		switch(type){
			case 0x01:	// 命令
				if(str_h == 0x01){	// 控制电机的命令
					response = str_l;
					Usart_SendFourByte(DEBUG_USARTx, str_l|0x01010000);
				}
				if(str_h == 0x02){ 	// 控制风扇的命令
					fanCom = str_l;
					Usart_SendFourByte(DEBUG_USARTx, str_l|0x01020000);
				}
			break;
			case 0x02:	// 脉冲
				if(type == str_h){
						pulse = str_l;
				}else{
						pulse = ((str_h&0x00ff)<<8)|str_l;
				}
			break;
			case 0x03:	// 转速
				if(type == str_h){
						timeMs = str_l;
				}else{
						timeMs = ((str_h&0x00ff)<<8)|str_l;
				}
			break;
			case 0x04:	// 角度
				if(str_h == 0x01){	// X 轴
					xAngle = str_l;
					Usart_SendFourByte(DEBUG_USARTx, str_l|0x04010000);
				}
				if(str_h == 0x02){	// Y 轴
					yAngle = str_l;
					Usart_SendFourByte(DEBUG_USARTx, str_l|0x04020000);
				}
			break;
			default:break;
		}
}



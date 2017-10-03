
#include "HDT11.h"
#include "./systick/systick.h"

// 初始化传感器工作引脚
void DHT11_GPIO_Config(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
			
		// 设置管脚工作模式
		GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);
		
		// 拉高管脚电平
		GPIO_SetBits(HDT11_GPIO, HDT11_GPIO_PIN);	 
}

// 使HDT11-DATA引脚变为输入模式
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 

	  GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);	 
}


// 描述  ：使DHT11-DATA引脚变为输出模式
static void DHT11_Mode_Out_PP(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  	GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);	 	 
}

// 读取传感器管脚数据
static uint8_t Read_Byte(void)
{	  

	 uint8_t i, temp=0;
	
	 for(i=0;i<8;i++)    
	 {
	   /*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
    	while(DHT11_DATA_IN()==Bit_RESET);
		 
		 /*DHT11 以27~28us的高电平表示“0”，以70us高电平表示“1”，
	 		 通过检测60us后的电平即可区别这两个状态*/

			Systick_DelayUs(60); //延时60us		   	  
	
		  if(DHT11_DATA_IN() == Bit_SET)//60us后仍为高电平表示数据“1”
		   {
				 /*轮询直到从机发出的剩余的 30us 高电平结束*/
				 while(DHT11_DATA_IN()==Bit_SET);

				 temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1 
			
		   }
		   else	 //60us后为低电平表示数据“0”
		   {			   
		   	  temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0
		   }
	 }
	  return temp;
}


uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	 /*输出模式*/
   DHT11_Mode_Out_PP();
   /*主机拉低*/
   DHT11_DATA_OUT(LOW);
   /*延时18ms*/
   Systick_DelayMs(18);

   /*总线拉高 主机延时30us*/
   DHT11_DATA_OUT(HIGH); 

   Systick_DelayUs(30);   //延时30us
   
 	 /*主机设为输入 判断从机响应信号*/ 
   DHT11_Mode_IPU();

	 /*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
   if(DHT11_DATA_IN()==Bit_RESET)   //T !   
    {
  
	
	   /*轮询直到从机发出 的80us 低电平 响应信号结束*/  
	    while(DHT11_DATA_IN()==Bit_RESET);
	  	 
	   /*轮询直到从机发出的 80us 高电平 标置信号结束*/
	    while(DHT11_DATA_IN()==Bit_SET);

	   /*开始接收数据*/   
	 	 DHT11_Data->humi_int= Read_Byte();
								
		 DHT11_Data->humi_deci= Read_Byte();
				
		 DHT11_Data->temp_int= Read_Byte();

		 DHT11_Data->temp_deci= Read_Byte();
				 		
		 DHT11_Data->check_sum= Read_Byte();
		 								  

		 /*读取结束，引脚改为输出模式*/
		 DHT11_Mode_Out_PP();
		 
		 /*主机拉高*/
		 DHT11_DATA_OUT(HIGH);

		 /*检查读取的数据是否正确*/
		 if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci)
		  	return SUCCESS;
		  else 
		  	return ERROR;
   }
   else
   	{		
			return ERROR;
		}
   
}


//		// 控制电机脉冲和转速
//		if( Read_DHT11(&DHT11_Data)==SUCCESS){			
//			WIFI_SendFourByte(WIFI_USARTx,(DHT11_Data.humi_int<<8)|DHT11_Data.temp_int|0x02010000);
//			// 超过30度电机转动
//			if(DHT11_Data.temp_int > 25)
//				Machine_Ctr(response,pulse,timeMs*500);
//		}


//		// 控制电机脉冲和转速
//		if( Read_DHT11(&DHT11_Data)==SUCCESS){			
//			WIFI_SendFourByte(WIFI_USARTx,(DHT11_Data.humi_int<<8)|DHT11_Data.temp_int|0x02010000);
//			// 超过30度电机转动
//			if(DHT11_Data.temp_int > 25)
//				Machine_Ctr(response,pulse,timeMs*500);
//		}



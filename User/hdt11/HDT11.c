
#include "HDT11.h"
#include "./systick/systick.h"

// ��ʼ����������������
void DHT11_GPIO_Config(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
			
		// ���ùܽŹ���ģʽ
		GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);
		
		// ���߹ܽŵ�ƽ
		GPIO_SetBits(HDT11_GPIO, HDT11_GPIO_PIN);	 
}

// ʹHDT11-DATA���ű�Ϊ����ģʽ
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 

	  GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);	 
}


// ����  ��ʹDHT11-DATA���ű�Ϊ���ģʽ
static void DHT11_Mode_Out_PP(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = HDT11_GPIO_PIN;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  	GPIO_Init(HDT11_GPIO, &GPIO_InitStructure);	 	 
}

// ��ȡ�������ܽ�����
static uint8_t Read_Byte(void)
{	  

	 uint8_t i, temp=0;
	
	 for(i=0;i<8;i++)    
	 {
	   /*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
    	while(DHT11_DATA_IN()==Bit_RESET);
		 
		 /*DHT11 ��27~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
	 		 ͨ�����60us��ĵ�ƽ��������������״̬*/

			Systick_DelayUs(60); //��ʱ60us		   	  
	
		  if(DHT11_DATA_IN() == Bit_SET)//60us����Ϊ�ߵ�ƽ��ʾ���ݡ�1��
		   {
				 /*��ѯֱ���ӻ�������ʣ��� 30us �ߵ�ƽ����*/
				 while(DHT11_DATA_IN()==Bit_SET);

				 temp|=(uint8_t)(0x01<<(7-i));  //�ѵ�7-iλ��1 
			
		   }
		   else	 //60us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		   {			   
		   	  temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0
		   }
	 }
	  return temp;
}


uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	 /*���ģʽ*/
   DHT11_Mode_Out_PP();
   /*��������*/
   DHT11_DATA_OUT(LOW);
   /*��ʱ18ms*/
   Systick_DelayMs(18);

   /*�������� ������ʱ30us*/
   DHT11_DATA_OUT(HIGH); 

   Systick_DelayUs(30);   //��ʱ30us
   
 	 /*������Ϊ���� �жϴӻ���Ӧ�ź�*/ 
   DHT11_Mode_IPU();

	 /*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
   if(DHT11_DATA_IN()==Bit_RESET)   //T !   
    {
  
	
	   /*��ѯֱ���ӻ����� ��80us �͵�ƽ ��Ӧ�źŽ���*/  
	    while(DHT11_DATA_IN()==Bit_RESET);
	  	 
	   /*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
	    while(DHT11_DATA_IN()==Bit_SET);

	   /*��ʼ��������*/   
	 	 DHT11_Data->humi_int= Read_Byte();
								
		 DHT11_Data->humi_deci= Read_Byte();
				
		 DHT11_Data->temp_int= Read_Byte();

		 DHT11_Data->temp_deci= Read_Byte();
				 		
		 DHT11_Data->check_sum= Read_Byte();
		 								  

		 /*��ȡ���������Ÿ�Ϊ���ģʽ*/
		 DHT11_Mode_Out_PP();
		 
		 /*��������*/
		 DHT11_DATA_OUT(HIGH);

		 /*����ȡ�������Ƿ���ȷ*/
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


//		// ���Ƶ�������ת��
//		if( Read_DHT11(&DHT11_Data)==SUCCESS){			
//			WIFI_SendFourByte(WIFI_USARTx,(DHT11_Data.humi_int<<8)|DHT11_Data.temp_int|0x02010000);
//			// ����30�ȵ��ת��
//			if(DHT11_Data.temp_int > 25)
//				Machine_Ctr(response,pulse,timeMs*500);
//		}


//		// ���Ƶ�������ת��
//		if( Read_DHT11(&DHT11_Data)==SUCCESS){			
//			WIFI_SendFourByte(WIFI_USARTx,(DHT11_Data.humi_int<<8)|DHT11_Data.temp_int|0x02010000);
//			// ����30�ȵ��ת��
//			if(DHT11_Data.temp_int > 25)
//				Machine_Ctr(response,pulse,timeMs*500);
//		}



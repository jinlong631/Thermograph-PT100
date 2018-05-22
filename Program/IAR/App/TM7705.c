/**
  *******************************  STM8L151K4  *********************************
  * @�ļ���     �� TM7705.c
  * @����       �� ������
  * @��汾     �� V1.6.1
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2018��05��12��
  * @ժҪ       �� �����
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-05-12 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
  
#include "TM7705.h"
	u16 a=0;
/* ȫ�ֱ��� ------------------------------------------------------------------*/
void TM7705_Init(void)
{
  	
	//GPIO����
  	//SCLK��PA2����DIN���ã�PA3��
	GPIO_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3,GPIO_Mode_Out_PP_Low_Slow);
	//DOUT(PA4)��DRDY��PA5������
	GPIO_Init(GPIOA,GPIO_Pin_4|GPIO_Pin_5,GPIO_Mode_In_PU_No_IT);
	//RST����
	GPIO_Init(GPIOD,GPIO_Pin_0,GPIO_Mode_Out_PP_Low_Slow);
	Delay(1000);
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
	//��λ
	
	Delay(1000);
	Send_Cmd(0x39);
	a=Read_Data();
	
	
}


//��ȡ16λ����
u16 Read_Data(void)
{
  	u16 data=0;
  	u8 i=0;
  	//while(DRDY);
	for(i=0;i<16;i++)
	{
	  	data<<=1;
	  	GPIO_SetBits(GPIOA,GPIO_Pin_2);
		Delay(100);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))
			data|=0x01;
		
	}
	return data;
}

void Send_Cmd(u8 cmd)
{
  	u8 i=0;
	
  	//while(DRDY);
	for(i=0;i<8;i++)
	{
		if(cmd&0x80)
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
		else
		  	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		Delay(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		Delay(100);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		cmd<<=1;
	}
}


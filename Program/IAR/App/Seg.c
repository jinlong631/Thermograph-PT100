/**
  *******************************  STM8L151K4  *********************************
  * @�ļ���     �� Seg.c
  * @����       �� ������
  * @��汾     �� V1.6.1
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2018��05��11��
  * @ժҪ       �� �����
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-05-11 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "Seg.h"
/* ȫ�ֱ��� ------------------------------------------------------------------*/
u8 Seg_Data[4]={0,1,2,3};
const u8 seg_duan[10]={0xAF,0x21,0x9D,0xB5,0x33,};


/************************************************
�������� �� Seg_Init
��    �� �� �����ģ���ʼ��
��    �� �� ������
ժ    Ҫ �� 
*************************************************/	
void Seg_Init(void)
{
  	inline void Seg_Tim2_Init(void);
	inline void Seg_Gpio_Init(void);
  	Seg_Gpio_Init();//�����GPIO��ʼ��
	Seg_Tim2_Init();//��ʱ����ʼ��
  	
	
	
}

/************************************************
�������� �� Seg_Gpio_Init
��    �� �� GPIO��ʼ��
��    �� �� ������
ժ    Ҫ �� PB��Ϊ����ܶ�ѡ
			PD[4:7]Ϊ�����λѡ
*************************************************/	
void Seg_Gpio_Init(void)
{
  	GPIO_Init(GPIOB,GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
	//PB������Ϊ���������2M����ʼ��
	GPIO_Init(GPIOD,GPIO_Pin_HNib,GPIO_Mode_Out_OD_HiZ_Slow);
	//PD[4:7]������Ϊ��©�����2M����ʼ����
}


/************************************************
�������� �� Seg_Tim2_Init
��    �� �� ��̬�����ʱ����ʼ��
��    �� �� ������
ժ    Ҫ �� ��Ƶ1M��4��Ƶ����625������400HZ
*************************************************/	
void Seg_Tim2_Init(void)//��ʱ����ʼ��
{
  	TIM2_TimeBaseInit(TIM2_Prescaler_4,TIM2_CounterMode_Up,625-1);
	//4��Ƶ�����ϼ�������625����
	TIM2_UpdateRequestConfig(TIM2_UpdateSource_Regular);
	//���������Ч
	TIM2_ITConfig(TIM2_IT_Update,ENABLE);
	//�����ж�ʹ��
	ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_IRQn,ITC_PriorityLevel_1);
	//���ȼ�1
	TIM2_Cmd(ENABLE);
	//��ʼ������
}


/************************************************
�������� �� Seg_Tim_Base
��    �� �� TIM2����ж�
��    �� �� ������
ժ    Ҫ �� 21���жϣ�400HZ
*************************************************/	
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void Seg_Tim_Base( void )
{
  	static u8 seg_wei=0;//����ܵ�ǰλ
	
  	TIM2_ClearFlag(TIM2_FLAG_Update);//���־λ
	
	if(seg_wei==3)//λѡѭ��
		seg_wei=0;
	else
	  	seg_wei++;
	
	GPIO_SetBits(GPIOD,GPIO_Pin_HNib);//λѡ�ر�
	GPIO_Write(GPIOB,seg_duan[Seg_Data[seg_wei]]);//���ö�ѡ
	switch(seg_wei)//��λѡ
	{
		case 3:GPIO_ResetBits(GPIOD,GPIO_Pin_4);break;
	  	case 1:GPIO_ResetBits(GPIOD,GPIO_Pin_5);break;
		case 2:GPIO_ResetBits(GPIOD,GPIO_Pin_6);break;
		case 0:GPIO_ResetBits(GPIOD,GPIO_Pin_7);break;
	}

}
	

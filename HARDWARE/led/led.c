//*******************************
//STM32F407 ����LED����
//File: led.c
//Author: ��ĩ����
//Version: V1.0
//Date: 2022/03/25
//*******************************

#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//LED�˿�ʹ��
	GPIO_InitStructure.GPIO_Pin = LED_Pin_Red | LED_Pin_Green;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		//������������
	GPIO_Init(GPIOF, &GPIO_InitStructure);					//��ʼ��
	
	GPIO_SetBits(GPIOF,LED_Pin_Red);
	GPIO_ResetBits(GPIOF,LED_Pin_Green);
	
}


void LED_Toggle(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == LED_Pin_Red)	
		GPIO_ToggleBits(GPIOF, LED_Pin_Red);
	else 
		GPIO_ToggleBits(GPIOF, LED_Pin_Green);
}






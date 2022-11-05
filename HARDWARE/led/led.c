//*******************************
//STM32F407 板载LED配置
//File: led.c
//Author: 夏末终年
//Version: V1.0
//Date: 2022/03/25
//*******************************

#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//LED端口使能
	GPIO_InitStructure.GPIO_Pin = LED_Pin_Red | LED_Pin_Green;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		//无上拉或下拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);					//初始化
	
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






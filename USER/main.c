/**
  ******************************************************************************
  * @Author: ��ĩ����
  * @brief   �������PID
  * @attention	ʵ��ƽ̨:STM32F407 
  * @file    main.c
  *
  * @version V1.0								@date    
  * 	ʹ��PWMʵ�ֵ��������������					2022-3-25
  *
  * @version V2.0								@date    
  * 	����pid.c��ʵ��pid����						2022-4-1
  *
  * @version V3.0								@date    
  * 	����DataScope_DP.c��ʵ����λ��				2022-4-10
  
  * @version V4.0								@date    
  * 	����bluetooth.c��ʵ����������ת���ź�			2022-4-25
  *
  * @version V5.0								@date    
  * 	����oled.c��ʵ��oled��ʾת�ٵ�				2022-5-7
  *
  ******************************************************************************
  */ 
#include "delay.h"
#include "led.h"
#include "pwm.h"
#include "usart.h"
#include "speed.h"
#include "motor.h"
#include "timer.h"
#include "show.h"
#include "pid.h"
#include "bluetooth.h"
#include "adc.h"
#include "oled.h"

static void System_Config(void);

int main(void)
{
	System_Config();

	while(1)
	{	
		//Show_Diargram();
		Show_OLED();
	}
}

static void System_Config(void)
{
	// ����ϵͳ�ж����ȼ�����2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// ��ʼ����ʱ����
	delay_init(168); 

	// ���ڳ�ʼ��������������128000
	uart_init(128000);
	
	// ������ʼ��
	Bluetooth_Init();
	
	// 84M/84 = 1Mhz,��װ��ֵ500��PWMƵ��Ϊ 1M/500 = 2Khz
 	TIM3_PWM_Init(500-1, 84-1);
	
	// LED��ʼ��
	LED_Init();	
	
	// OLED��ʼ��
 	OLED_Init();

	// ADC��ʼ��
	Rheostat_Init();
	
	// �����ʼ��
	Motor_Init();
	
	// pid�㷨��ʼ��
	Motor_PID_Init();
	
	// ����Ƶ�� 84M/8400 = 10khz, ���ֵ1000��1000/10k = 100ms����һ��ת��
	TIM7_Int_Init(1000-1, 8400-1);
	
	// ��ʱ��4��ʼ��������AB������
	TIM4_Speed_Init();
}


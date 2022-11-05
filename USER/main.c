/**
  ******************************************************************************
  * @Author: 夏末终年
  * @brief   电机调速PID
  * @attention	实验平台:STM32F407 
  * @file    main.c
  *
  * @version V1.0								@date    
  * 	使用PWM实现电机开环调速运行					2022-3-25
  *
  * @version V2.0								@date    
  * 	增加pid.c，实现pid调速						2022-4-1
  *
  * @version V3.0								@date    
  * 	增加DataScope_DP.c，实现上位机				2022-4-10
  
  * @version V4.0								@date    
  * 	增加bluetooth.c，实现蓝牙发送转速信号			2022-4-25
  *
  * @version V5.0								@date    
  * 	增加oled.c，实现oled显示转速等				2022-5-7
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
	// 设置系统中断优先级分组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// 初始化延时函数
	delay_init(168); 

	// 串口初始化函数，波特率128000
	uart_init(128000);
	
	// 蓝牙初始化
	Bluetooth_Init();
	
	// 84M/84 = 1Mhz,重装载值500，PWM频率为 1M/500 = 2Khz
 	TIM3_PWM_Init(500-1, 84-1);
	
	// LED初始化
	LED_Init();	
	
	// OLED初始化
 	OLED_Init();

	// ADC初始化
	Rheostat_Init();
	
	// 电机初始化
	Motor_Init();
	
	// pid算法初始化
	Motor_PID_Init();
	
	// 计数频率 84M/8400 = 10khz, 溢出值1000，1000/10k = 100ms计算一次转速
	TIM7_Int_Init(1000-1, 8400-1);
	
	// 定时器4初始化，捕获AB相脉冲
	TIM4_Speed_Init();
}


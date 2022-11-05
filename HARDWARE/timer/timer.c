//*******************************
//STM32F407 定时器7设置:
//此定时器设置定时功能，定时时间到了便计算一次电机转速
//因为只需要实现定时功能，基本定时器7就已足够
//File: timer.c
//Author: 夏末终年
//Version: V1.0
//Date: 2022/03/25
//*******************************
#include "timer.h"
#include "speed.h"
#include "motor.h"
#include "pid.h"

extern float rotateSpeed;
extern struct PID motor1_pid;

/**
 * 通用定时器7初始化
 * arr：自动重装值。
 * psc：时钟预分频数
 * 定时器溢出时间计算方法:Tout = ((arr+1)*(psc+1))/Ft us.
 * Ft = 定时器工作频率,单位:Mhz
 */
void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  	//使能TIM7时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr;   			//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  			//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);		//初始化TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); 				//允许定时器7更新中断
	TIM_Cmd(TIM7,ENABLE); 									//使能定时器7
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; 			//定时器7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; 		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//定时器7中断服务函数，计算电机转速
void TIM7_IRQHandler(void)
{ 
	/* 如果发生溢出中断，就计算一次 */
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET)
	{
		calc_motor_rotate_speed();
		PID_Input_Renew(&motor1_pid, rotateSpeed);
		PID_Compute(&motor1_pid);
		set_motor_rotate(motor1_pid.output);
	}
	/* 清除中断标志位 */
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  
}

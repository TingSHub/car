//*******************************
//STM32F407 ��ʱ��7����:
//�˶�ʱ�����ö�ʱ���ܣ���ʱʱ�䵽�˱����һ�ε��ת��
//��Ϊֻ��Ҫʵ�ֶ�ʱ���ܣ�������ʱ��7�����㹻
//File: timer.c
//Author: ��ĩ����
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
 * ͨ�ö�ʱ��7��ʼ��
 * arr���Զ���װֵ��
 * psc��ʱ��Ԥ��Ƶ��
 * ��ʱ�����ʱ����㷽��:Tout = ((arr+1)*(psc+1))/Ft us.
 * Ft = ��ʱ������Ƶ��,��λ:Mhz
 */
void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  	//ʹ��TIM7ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr;   			//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  			//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);		//��ʼ��TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); 				//����ʱ��7�����ж�
	TIM_Cmd(TIM7,ENABLE); 									//ʹ�ܶ�ʱ��7
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; 			//��ʱ��7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; 		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��7�жϷ�������������ת��
void TIM7_IRQHandler(void)
{ 
	/* �����������жϣ��ͼ���һ�� */
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET)
	{
		calc_motor_rotate_speed();
		PID_Input_Renew(&motor1_pid, rotateSpeed);
		PID_Compute(&motor1_pid);
		set_motor_rotate(motor1_pid.output);
	}
	/* ����жϱ�־λ */
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  
}

#include "show.h"
#include "usart.h"
#include "speed.h"
#include "delay.h"
#include "pid.h"
#include "DataScope_DP.h"
#include "oled.h"
#include "timer.h"
#include "adc.h"
#include <math.h>

extern float rotateSpeed;
extern struct PID_constant constant1;
extern struct PID motor1_pid;
extern uint16_t ADC_ConvertedValue_t;
extern uint16_t ADC_ConvertedValue_f;

void Show_Diargram(void)
{
	int Send_Count, i;
	DataScope_Get_Channel_Data(motor1_pid.setpoint, 1);
	DataScope_Get_Channel_Data(motor1_pid.input, 2);
	DataScope_Get_Channel_Data(motor1_pid.output, 3);
	DataScope_Get_Channel_Data(motor1_pid.last_error, 4);
	DataScope_Get_Channel_Data(motor1_pid.next_error, 5);
	DataScope_Get_Channel_Data(motor1_pid.current_error, 6);
	Send_Count = DataScope_Data_Generate(6);
	for(i = 0 ; i < Send_Count; i++) 
	{
		while((USART1->SR&0X40) == 0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
	}
	delay_ms(50); //20HZ
}

void Show_OLED(void)
{
	OLED_ShowString(0,0,"setpoint:",16,1);
	OLED_ShowString(0,16,"measure:",16,1);
	OLED_ShowString(0,32,"duty:",16,1);
	OLED_ShowString(0,48,"battery:",16,1);
	OLED_ShowString(100,0,"r/m",16,1);
	OLED_ShowString(100,16,"r/m",16,1);
	OLED_ShowString(100,32,"%",16,1);
	OLED_ShowString(90,48,".",16,1);
	OLED_ShowString(116,48,"V",16,1);
	
	OLED_ShowNum(72,0,abs((int)motor1_pid.setpoint),3,16,1);
	OLED_ShowNum(72,16,abs((int)motor1_pid.input),3,16,1);
	OLED_ShowNum(72,32,abs((int)((int)motor1_pid.output/5)),3,16,1);
	OLED_ShowNum(72,48,ADC_ConvertedValue_t,2,16,1);
	OLED_ShowNum(96,48,ADC_ConvertedValue_f,2,16,1);

	OLED_Refresh();
	delay_ms(1000);
}

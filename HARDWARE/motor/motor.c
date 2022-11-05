#include "motor.h"
#include "pwm.h"
#include "pid.h"

extern struct PID motor1_pid;

void Motor_Init()
{		 					 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_MOTOR1, ENABLE);//使能GPIOA时钟

	//电机1正负极GPIO初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_MOTOR1_IN1 | GPIO_Pin_MOTOR1_IN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO_MOTOR1, &GPIO_InitStructure);		//初始化GPIO
	
	//全部拉低，电机停转
	GPIO_ResetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN1 | GPIO_Pin_MOTOR1_IN2);
}  

static void set_forward(void)
{
	GPIO_SetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN1);
	GPIO_ResetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN2);
}

static void set_backward(void)
{
	GPIO_ResetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN1);
	GPIO_SetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN2);
}

static void set_stop(void)
{
	GPIO_ResetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN1);
	GPIO_ResetBits(GPIO_MOTOR1,GPIO_Pin_MOTOR1_IN2);
}


void set_motor_rotate(int pwm)
{
	if(pwm > 0)
	{
		set_pwm(pwm);
		set_forward();
	}
	else if(pwm < 0)
	{
		set_pwm(-pwm);
		set_backward();
	}
	else
	{
		set_pwm(0);
		set_stop();
	}
}

/* 遥控小车蓝牙接收处理函数 */
void RemoteControl(uint8_t ch)
{
  switch (ch)
  {
  case 'A':
	  
      break;
  case 'B':
	  
      break;
  case 'C':
	  
      break;
  case 'D':
	  
      break;
  case 'E':
	  
      break;
  case 'F':
	  
      break;
  case 'G':
	  
    break;
  case 'H':
	  
	  break;
  case 'X':
	  PID_Change_Setpoint(&motor1_pid, motor1_pid.setpoint + 50);
	  break;
  case 'Y': 
	  PID_Change_Setpoint(&motor1_pid, motor1_pid.setpoint - 50);
      break;
  case 'Z':
	  PID_Change_Setpoint(&motor1_pid, 0);
	  break;
  default:
      break;
  }
}

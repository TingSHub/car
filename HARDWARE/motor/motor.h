#ifndef _MOTOR_H
#define _MOTOR_H
#include "sys.h"

#define RCC_AHB1Periph_MOTOR1 RCC_AHB1Periph_GPIOF
#define GPIO_MOTOR1 GPIOF

#define GPIO_Pin_MOTOR1_IN1 GPIO_Pin_3
#define GPIO_Pin_MOTOR1_IN2 GPIO_Pin_4

void Motor_Init(void);
void set_motor_rotate(int pwm);
/* 遥控小车蓝牙接收处理函数 */
void RemoteControl(uint8_t ch);

#endif

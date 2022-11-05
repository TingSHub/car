#ifndef __LED_H
#define __LED_H
#include "sys.h"

//************************
//板载两个LED,低电平点亮
//F9:红色灯
//F10:绿色灯
//*************************

/* LED端口定义 */
#define GPIO_LED GPIOF

#define LED_Pin_Red		GPIO_Pin_9
#define LED_Pin_Green	GPIO_Pin_10

/* 位带操作 */
#define PF_Out(n)	*(volatile uint16_t*)(0x42000000 + 32 * (0x21414) + n * 4)

/**
 * LED初始化函数
 */
void LED_Init(void);

/**
 * LED翻转函数
 */
void LED_Toggle(uint16_t GPIO_Pin);	 				    
#endif

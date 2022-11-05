#ifndef __LED_H
#define __LED_H
#include "sys.h"

//************************
//��������LED,�͵�ƽ����
//F9:��ɫ��
//F10:��ɫ��
//*************************

/* LED�˿ڶ��� */
#define GPIO_LED GPIOF

#define LED_Pin_Red		GPIO_Pin_9
#define LED_Pin_Green	GPIO_Pin_10

/* λ������ */
#define PF_Out(n)	*(volatile uint16_t*)(0x42000000 + 32 * (0x21414) + n * 4)

/**
 * LED��ʼ������
 */
void LED_Init(void);

/**
 * LED��ת����
 */
void LED_Toggle(uint16_t GPIO_Pin);	 				    
#endif

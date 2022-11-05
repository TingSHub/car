#ifndef __ADC_H
#define	__ADC_H

#include "sys.h"

// ADC GPIO �궨��
#define RHEOSTAT_ADC_GPIO_PORT    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN     GPIO_Pin_5
#define RHEOSTAT_ADC_GPIO_CLK     RCC_AHB1Periph_GPIOA

// ADC ��ź궨��
#define RHEOSTAT_ADC              ADC1
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC1
#define RHEOSTAT_ADC_CHANNEL      ADC_Channel_5


// ADC �жϺ궨��
#define Rheostat_ADC_IRQ            ADC_IRQn
#define Rheostat_ADC_INT_FUNCTION   ADC_IRQHandler


void Rheostat_Init(void);

#endif /* __ADC_H */




#include "speed.h"
#include "sys.h"
#include "usart.h"

#define ENCODER_TIM_PSC  0          /*��������Ƶ*/
#define ENCODER_TIM_PERIOD  65535   /*���������ֵ*/
#define CNT_INIT 0                  /*��������ֵ*/

#define ENCODER_RESOLUTION 13    /*������һȦ������������*/
#define ENCODER_MULTIPLE 4       /*��������Ƶ��ͨ����ʱ���ı�����ģʽ����*/
#define MOTOR_REDUCTION_RATIO 30 /*����ļ��ٱ�*/

volatile float rotateSpeed = 0;
/**
 * ���1Ȧ�ܵ�������(��ʱ���ܶ�����������) = 
 * ����������������*��������Ƶ*������ٱ�= 1560 
 */
#define TOTAL_RESOLUTION \
 (ENCODER_RESOLUTION*ENCODER_MULTIPLE*MOTOR_REDUCTION_RATIO)

/**
* @brief TIM4 ͨ��1ͨ��2 ����������
* @param none
*/
void TIM4_Speed_Init(void)                      
{ 
	GPIO_InitTypeDef GPIO_InitStruct;            /*GPIO*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; /*ʱ��*/
	TIM_ICInitTypeDef TIM_ICInitStruct;          /*����ͨ��*/
    
    /*GPIO��ʼ��*/    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); /*ʹ��GPIOʱ�� AHB1*/                    
	GPIO_StructInit(&GPIO_InitStruct);        
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;        /*���ù���*/
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;	 /*�ٶ�100MHz*/
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;        
	GPIO_Init(GPIOB, &GPIO_InitStruct); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); 

	/*ʱ����ʼ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   	  /*ʹ�ܶ�ʱ��ʱ�� APB1*/
	TIM_DeInit(TIM4);  
	TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);    
	TIM_TimeBaseStruct.TIM_Prescaler = ENCODER_TIM_PSC;       /*Ԥ��Ƶ */        
	TIM_TimeBaseStruct.TIM_Period = ENCODER_TIM_PERIOD;       /*����(��װ��ֵ)*/
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;      
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;  /*�������ϼ���ģʽ*/  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct); 

	/*������ģʽ���ã�ͬʱ����ͨ��1��ͨ��2(��4��Ƶ)�����Ծ�ΪRising*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
	TIM_ICStructInit(&TIM_ICInitStruct);        
	TIM_ICInitStruct.TIM_ICFilter = 0;   /*����ͨ�����˲�����*/
	TIM_ICInit(TIM4, &TIM_ICInitStruct); /*����ͨ����ʼ��*/
	TIM_SetCounter(TIM4, CNT_INIT);      /*CNT���ֵ*/
	TIM_ClearFlag(TIM4,TIM_IT_Update);   /*�жϱ�־��0*/
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); /*�ж�ʹ��*/
	TIM_Cmd(TIM4,ENABLE);                /*ʹ��CR�Ĵ���*/
} 

// ��ȡ��ʱ������ֵ
static int read_encoder(void)
{
	int encoderNum = 0;
	encoderNum = (int)((int16_t)(TIM4->CNT));	 /*CNTΪuint32, תΪint16*/
	TIM_SetCounter(TIM4, CNT_INIT);				 /*CNT���ֵ*/

	return encoderNum;
}

//������ת�٣�100ms����1�Σ�
void calc_motor_rotate_speed()
{
	int encoderNum = 0;
	
	/*��ȡ��������ֵ������������ת����*/
	encoderNum = read_encoder();
	
	/* ת�� = ��λʱ���ڵļ���ֵ / �ֱܷ��� * ʱ��ϵ�� ��λ r / min */
	rotateSpeed = 60 * (float)encoderNum * 10 / (float)TOTAL_RESOLUTION;

	/* printf�ض���ֱ�Ӵ�ӡ������ */
	//printf("encoder: %d\t speed:%.2f rps\r\n",encoderNum, rotateSpeed);
}


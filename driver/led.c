#include "main.h"

/**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void led_init (void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = LED2_MAP;	
	/*���ÿ⺯������ʼ��GPIOB*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	/* �ر�����led��	*/
	GPIO_SetBits(GPIOB, LED2_MAP);	 	 
	GPIO_ResetBits(GPIOB, LED2_MAP);	
	LED2 = !LED2;	
}
/*********************************************END OF FILE**********************/


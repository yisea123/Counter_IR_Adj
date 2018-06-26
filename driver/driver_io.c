#include "main.h"


void drive_io_init (void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	/*����GPIO����ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE); 
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = OUTPUT_PIN_MAP;
	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	/* �ر��������	*/	 
	GPIO_SetBits(GPIOF, OUTPUT_PIN_MAP);	
	
	

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	////////////////////////////////////////////////////
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	 									   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	//EXT6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line6); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//�ⲿ�ж���6
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT6_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT6_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);
	//EXT7
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line7); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//�ⲿ�ж���7
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT7_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT7_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//EXT8
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line8); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//�ⲿ�ж���8
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT8_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT8_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);			
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_11;
	GPIO_Init(GPIOG, &GPIO_InitStructure);		
	//EXT0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line0); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//�ⲿ�ж���0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT0_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT0_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);
	//EXT1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line1); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//�ⲿ�ж���1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT1_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT1_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);
	//EXT2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line2); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//�ⲿ�ж���2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT2_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT2_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);
	//EXT3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line3); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//�ⲿ�ж���3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT3_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT3_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);		
	//EXT11
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line11); //����жϹ����־λ
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//�ⲿ�ж���11
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT11_INT_PREEM;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT11_INT_SUB;			//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);			
	
}

//�ⲿ�ж���0���жϷ�����
void EXTI0_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line0); //����ж���0�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}
//�ⲿ�ж���1���жϷ�����
void EXTI1_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line1); //����ж���1�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}
//�ⲿ�ж���2���жϷ�����
void EXTI2_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line2); //����ж���2�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}
//�ⲿ�ж���3���жϷ�����
void EXTI3_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line3); //����ж���3�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}

//�ⲿ�ж���6 7 8���жϷ�����
void EXTI9_5_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line6 | EXTI_Line7 | EXTI_Line8); //����ж���6�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}
//�ⲿ�ж���11���жϷ�����
void EXTI15_10_IRQHandler(void)
{
	OSIntEnter();
	EXTI_ClearITPendingBit(EXTI_Line11); //����ж���11�����־λ
	OSQPost(io_msg, (void *) 0x55);//������Ϣ
	OSIntExit();
}


























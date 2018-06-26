#include "main.h"


s_counter_info g_counter;

U16 process_rdy = 0;
typedef struct {
	vu16 AD_Value_0[SAMPLE_NUM][CHANEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
	vu16 AD_Value_1[SAMPLE_NUM][CHANEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
	vu16 AD_Value_2[SAMPLE_NUM][CHANEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
}s_AD_buf;

s_AD_buf AD_DMA_buf;
u16 After_filter[CHANEL_NUM]; //���������ƽ��ֵ֮��Ľ��


//vu16 Detect_Buf[DETECTG_BUF_GROUP][DETECTG_BUF_SIZE];
vu16 Detect_Buf[DETECTG_BUF_SIZE];
s_buf AD_buff;




s_counter_env counter_env;

void counter_init (void)
{
	int i;
	S8 *p = (S8 *) &g_counter;
	for (i = 0; i < sizeof(s_counter_info); i++)
	{
		*(p++) = 0;
	}

	memset ((void *)Detect_Buf, 0, sizeof(Detect_Buf));
	memset ((void *)After_filter, 0, sizeof(After_filter));
	memset ((void *)&AD_DMA_buf, 0, sizeof(AD_DMA_buf));

	COUNT_COMPLETE = 1;

	g_counter.AD_buf_p = 0;
	g_counter.AD_use_buf_index = 0;
	g_counter.counter_state = COUNTER_IDLE;

	for (i = 0; i < CHANEL_NUM; i++){
		g_counter.ch[i].ad_min = 0xFFFF;
		g_counter.ch[i].ad_max = 0;
		g_counter.ch[i].ad_averaged_value = 0;
	}

	g_counter.sim_ad_value = 35000;

	g_counter.max_len.data_hl = 0;
	g_counter.max_close_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;
}


void counter_reset (void)
{
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
	g_counter.total_count = 0;
	g_counter.pre_count = 0;
	g_counter.total_reject = 0;
	g_counter.total_good = 0;
	g_counter.rej_flag = 0;
	g_counter.rej_flag_buf.data_hl = 0;
	CHANEL_INIT(0);
	CHANEL_INIT(1);
	CHANEL_INIT(2);
	CHANEL_INIT(3);
	CHANEL_INIT(4);
	CHANEL_INIT(5);
	CHANEL_INIT(6);
	CHANEL_INIT(7);
	CHANEL_INIT(8);
	CHANEL_INIT(9);
	CHANEL_INIT(10);
	CHANEL_INIT(11);
	g_counter.max_len.data_hl = 0;
	g_counter.max_close_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;
	stop_vibrate ();
	REJECT_FLAG = 1;//�޳���־
	PRE_COUNT_FLAG = 1;
	g_counter.counter_step = 0;
	g_counter.counter_state = COUNTER_IDLE;
	COUNT_COMPLETE = 0;
	g_counter.complete_count = 0;//��������ź�
	g_counter.complete_res = 0;//��������ź�
	OS_EXIT_CRITICAL();
}
void counter_data_clear (void)
{
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
	CHANEL_DATA_CLEAR(0);
	CHANEL_DATA_CLEAR(1);
	CHANEL_DATA_CLEAR(2);
	CHANEL_DATA_CLEAR(3);
	CHANEL_DATA_CLEAR(4);
	CHANEL_DATA_CLEAR(5);
	CHANEL_DATA_CLEAR(6);
	CHANEL_DATA_CLEAR(7);
	CHANEL_DATA_CLEAR(8);
	CHANEL_DATA_CLEAR(9);
	CHANEL_DATA_CLEAR(10);
	CHANEL_DATA_CLEAR(11);
	g_counter.max_len.data_hl = 0;
	g_counter.max_close_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;

	OS_EXIT_CRITICAL();
}


void AD_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);
	//PA0/1/2/3 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//PB0/1 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PC0/1/2/3/4/5 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOG.15
	PEout(3) = 1;
	PEout(4) = 1;
	PEout(5) = 1;
	PEout(6) = 1;
}



void set_adc1_sample_time (void)
{
	#define SAMPLE_TIME sample_time//ADC_SampleTime_28Cycles5// ADC_SampleTime_7Cycles5 //ADC_SampleTime_71Cycles5 //ADC_SampleTime_239Cycles5
	uint8_t sample_time = ADC_SampleTime_55Cycles5;
		//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	switch (g_counter.set_adc_mode)
	{
//		case 0:
//			sample_time = ADC_SampleTime_1Cycles5;
//			break;
		case 1:
			sample_time = ADC_SampleTime_7Cycles5;
			break;
		case 2:
			sample_time = ADC_SampleTime_13Cycles5;
			break;
		case 3:
			sample_time = ADC_SampleTime_28Cycles5;
			break;
		case 4:
			sample_time = ADC_SampleTime_41Cycles5;
			break;
		case 5:
			sample_time = ADC_SampleTime_55Cycles5;
			break;
		case 6:
			sample_time = ADC_SampleTime_71Cycles5;
			break;
		case 7:
			sample_time = ADC_SampleTime_239Cycles5;
			break;
		default:break;
	}
	ADC_RegularChannelConfig(ADC1, CH0, 1, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH1, 2, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH2, 3, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH3, 4, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH4, 5, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH5, 6, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH6, 7, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH7, 8, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH8, 9, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH9, 10, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH10, 11, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH11, 12, SAMPLE_TIME );
}

void ADC1_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;



	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE ); //ʹ��ADC1ͨ��ʱ�ӣ������ܽ�ʱ��

	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC1); //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = CHANEL_NUM; //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	set_adc1_sample_time ();

	// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	ADC_DMACmd(ADC1, ENABLE);

	//����ģ�⿴�Ź�
//	ADC_AnalogWatchdogThresholdsConfig(ADC1,0xfff,0);
//	ADC_AnalogWatchdogCmd(ADC1,ADC_AnalogWatchdog_AllRegEnable);
//	ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);//����ģ�⿴�Ź��ж�

	//ʹ��ADC�ж�
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = ADC1_2_INT_PREEM;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = ADC1_2_INT_SUB;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_Init(&NVIC_InitStructure);

	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1

	ADC_ResetCalibration(ADC1); //��λָ����ADC1��У׼�Ĵ���

	while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�


	ADC_StartCalibration(ADC1); //��ʼָ��ADC1��У׼״̬

	while(ADC_GetCalibrationStatus(ADC1)); //��ȡָ��ADC1��У׼����,����״̬��ȴ�
}

void re_calibration_detect (void)
{
	int i;
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	counter_reset ();
	OS_ENTER_CRITICAL();
	COUNT_COMPLETE = 1;
	VIBRATE_SWITCH = 1;
	for (i = 0; i < CHANEL_NUM; i++){
		g_counter.ch[i].ad_max = 0;
		g_counter.ch[i].ad_min = 0xFFFF;
		g_counter.ch[i].std_v = 0;
		g_counter.ch[i].ad_averaged_value = 0;
	}
	process_rdy = 0;
	AD_Sample_init ();
	OS_EXIT_CRITICAL();
}


U16 detect_chanel_index = 0xFFFF;//���ͨ������
U16 chanel_pos_index = 0;	//ͨ������������λ������
U16 ADC_sync_signal = 0; //ADCת������ͬ���ź�
U16 ADC1_irq_cycle = 23;
U16 ADC1_process_time = 6;
//ADC�жϷ�����
void ADC1_2_IRQHandler(void)
{
	//U16 temp;
//	unsigned long long tick_old;
//	tick_old = get_tim5_ticks();
//	refresh_adc1_cycle ();
///////////////////////////////////////////////////////////////////////////////
//	if (ADC_GetITStatus(ADC1, ADC_IT_AWD) != RESET){//���۹���ʱ������
//		detect_chanel_index = CHANEL_NUM - (DMA_GetCurrDataCounter (DMA1_Channel1) % CHANEL_NUM);
//		ADC_ClearFlag(ADC1, ADC_FLAG_AWD);
//		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
//	}else
//	if (ADC_GetITStatus(ADC1, ADC_IT_EOC)){//���ﲻ���ж�ADC_IT_EOC�Ƿ���λ����Ϊ����DMA��ת�����Ӳ��������ADC_IT_EOCλ
		chanel_pos_index++; //����������һ������������
		chanel_pos_index %= CHANEL_SENSOR_NUM;
		WRITE_SENSOR_ADDR(chanel_pos_index);//����������һ������������
//		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);//���ﲻ�����ADCx���жϴ�����λ����Ϊ����DMA��ת�����Ӳ��������ADC_IT_EOCλ
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//	}
////////////////////////////////////////////////////////////////////
//	ADC1_process_time = get_tim5_ticks () - tick_old + 2;
}


void AD1_DMA_Configuration(void)
{

	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ��DMA����
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_DMA_buf; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = SAMPLE_NUM * CHANEL_NUM * 2; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// DMA_Mode_Normal; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC | DMA_IT_HT, ENABLE); //��������ж�

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = DMA1_1_INT_PREEM;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = DMA1_1_INT_SUB;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_Init(&NVIC_InitStructure);

}
int counter_process_state;
void counter_process (void);
//============================================
//��������:DMA1_Channel1_IRQHandler
//��������:DMA�ж� ��AD�ɼ�ֵƽ���˲�
//����:��
//���:��
//============================================
#define START_DATA 5
#if (SAMPLE_NUM == 8)
	#define GET_STD_AD_V(AD,BUF,C,S)  {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C]; \
		/*AD[C] /= S; */ \
		if (g_counter.ch[C].ad_fitter_index >= AD_FITTER_BUFF_SIZE){ \
			g_counter.ch[C].ad_fitter_index = 0; \
		} \
		g_counter.ch[C].ad_fitter_buff[g_counter.ch[C].ad_fitter_index] = AD[C]; \
		g_counter.ch[C].ad_fitter_index++; \
		if (process_rdy > START_DATA){ \
			if (AD[C] > g_counter.ch[C].ad_max){ \
				g_counter.ch[C].ad_max = AD[C]; \
			} \
			if (AD[C] < g_counter.ch[C].ad_min){ \
				g_counter.ch[C].ad_min = AD[C]; \
			} \
			if (process_rdy != process_rdy_old) { \
				g_counter.ch[C].std_v += AD[C] / (PROCESS_RDY - 1 - (START_DATA + 1)); \
			}\
		} \
		if ((process_rdy + 1) == PROCESS_RDY){ \
			for (g_counter.ch[C].ad_fitter_index = 0; \
					g_counter.ch[C].ad_fitter_index < AD_FITTER_BUFF_SIZE; \
					g_counter.ch[C].ad_fitter_index++){ \
				g_counter.ch[C].ad_averaged_value += g_counter.ch[C].ad_fitter_buff[g_counter.ch[C].ad_fitter_index]; \
			} \
			g_counter.ch[C].ad_fitter_index = 0; \
			g_counter.ch[C].std_v = g_counter.ch[C].ad_averaged_value / AD_FITTER_BUFF_SIZE; \
			g_counter.ch[C].std_down_offset = (g_counter.ch[C].ad_max - g_counter.ch[C].ad_min); \
			g_counter.ch[C].std_up_offset = (g_counter.ch[C].ad_max - g_counter.ch[C].ad_min - 1); \
			g_counter.ch[C].std_down_offset *= g_counter.set_std_down_v_offset; \
			g_counter.ch[C].std_up_offset *= g_counter.set_std_down_v_offset; \
			g_counter.ch[C].std_down_offset /= (g_counter.set_std_up_v_offset); \
			g_counter.ch[C].std_up_offset /= (g_counter.set_std_up_v_offset); \
		} \
	}
#endif

#if (SAMPLE_NUM == 8)
	#define AD_FILTER(AD,BUF,C,S) {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C]; \
		 /*AD[C] /= S; */\
		if (g_counter.ch[C].ad_fitter_index >= AD_FITTER_BUFF_SIZE){ \
			g_counter.ch[C].ad_fitter_index = 0; \
		} \
		g_counter.ch[C].ad_averaged_value -= g_counter.ch[C].ad_fitter_buff[g_counter.ch[C].ad_fitter_index]; \
		g_counter.ch[C].ad_fitter_buff[g_counter.ch[C].ad_fitter_index] = AD[C]; \
		g_counter.ch[C].ad_averaged_value += AD[C]; \
		AD[C] = g_counter.ch[C].ad_averaged_value / AD_FITTER_BUFF_SIZE; \
		g_counter.ch[C].ad_fitter_index++; \
		if (AD[C] > g_counter.ch[C].ad_max){ \
			g_counter.ch[C].ad_max = AD[C]; \
		} \
		if (AD[C] < g_counter.ch[C].ad_min){ \
			g_counter.ch[C].ad_min = AD[C]; \
		} \
	}
#endif


void pause_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}

void start_vibrate (void)
{
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
	OPEN_DOOR(0);
	OPEN_DOOR(1);
	OPEN_DOOR(2);
	OPEN_DOOR(3);
	OPEN_DOOR(4);
	OPEN_DOOR(5);
	OPEN_DOOR(6);
	OPEN_DOOR(7);
	OPEN_DOOR(8);
	OPEN_DOOR(9);
	OPEN_DOOR(10);
	OPEN_DOOR(11);
	g_counter.rej_flag_buf.data_hl >>= 16;
	if (g_counter.pre_count < g_counter.set_count){
		g_counter.total_count = g_counter.pre_count;
		g_counter.pre_count = 0;
		g_counter.counter_state = NORMAL_COUNT;
		PRE_COUNT_FLAG = 1;
		VIBRATE_SWITCH = 0;
	}else{//�������߸պ�����
		g_counter.total_count = g_counter.pre_count;
		g_counter.pre_count = 0;
		SEND_COUNTER_FIN_SIGNAL ();
		g_counter.counter_state = PRE_COUNT;
		if (g_counter.pre_count < g_counter.set_pre_count){//�ﵽ�趨��Ԥ��
			VIBRATE_SWITCH = 0;
		}
	}
	OS_EXIT_CRITICAL();
}
void stop_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}


int AD_Sample_init (void)
{
	AD_GPIO_Configuration ();
	AD1_DMA_Configuration ();
	ADC1_Configuration ();
	ENABLE_SENSOR ();
	DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	return 0;
}

void AD_Start_Sample (u32 _memBaseAddr)
{
	/* Write to DMA1 Channel4 CMAR */
	DMA1_Channel1->CMAR = _memBaseAddr;
	//ADC_sync_signal = 0;//AD �ź����� ����ͬ��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



int save_detect_data (U16 _ch, U16 * _index, U16 _ad_value)
{
//	if (_ad_value == 0)
//	{
//		_ad_value = _ad_value;
//	}
	if (my_env.dma_state == 1){
		return 0;
	}
	if (_ch == g_counter.set_watch_ch){
		if ((*_index) < DETECTG_BUF_SIZE){
			Detect_Buf[*_index] = _ad_value;
			(*_index)++;
			return 0;
		}else{
			return 1;
		}
	}
	return 0;
}

#define CASE_CH(CH) case CH: if (DOOR_##CH == 1){ \
	if (g_counter.set_door_n_close_delay[CH] == 0){ \
		DOOR_##CH = 0; \
	}else if ((_ch->door_close_delay == 0) && (DOOR_##CH == 1)){/*���door_close_delay����0��˵���˿�û���ڼ�ʱ*/ \
		_ch->door_close_delay = g_counter.set_door_n_close_delay[CH];/*С���Źر���ʱ*/ \
	} \
	_ch->close_interval.data_hl = _ch->interval.data_hl; \
	if (_ch->close_interval.data_hl < g_counter.set_min_interval.data_hl){/*С���Źر�ʱҩ�����̫С*/  \
		REJECT_FLAG = 0; \
		g_counter.rej_flag_buf.data.h |= REJ_TOO_CLOSE; \
		g_counter.rej_flag_buf.data.l |= REJ_TOO_CLOSE; \
		g_counter.rej_flag = g_counter.rej_flag_buf.data.l; /*�����޳�ԭ��*/ \
	} \
	if (_ch->close_interval.data_hl > _ch->max_close_interval.data_hl){ \
		_ch->max_close_interval.data_hl = _ch->close_interval.data_hl; \
		if (_ch->max_close_interval.data_hl > g_counter.max_close_interval.data_hl){ \
			g_counter.max_close_interval.data_hl = _ch->max_close_interval.data_hl; \
		} \
	} \
	if (_ch->close_interval.data_hl < _ch->min_close_interval.data_hl){ \
		_ch->min_close_interval.data_hl = _ch->close_interval.data_hl; \
		if (_ch->min_close_interval.data_hl < g_counter.min_close_interval.data_hl){ \
			g_counter.min_close_interval.data_hl = _ch->min_close_interval.data_hl; \
		} \
	} \
} \
break


int count_piece(s_chanel_info * _ch, U16 _ad_value_, U16 _ch_id)
{
	int r_code = 0;
	int ad_change_v = 0;

	ad_change_v =  _ch->std_down_v - _ad_value_;
	if (ad_change_v < 0){
		ad_change_v = 0;
	}
	switch(_ch->process_step){
		case 0: {

			_ch->wave_down_flag = 0;
			_ch->wave_up_flag = 0;
			_ch->ad_value_min = AD_MAX_V;
			_ch->ad_value_min_temp = AD_MAX_V;

			_ch->cur_count = 0;
			_ch->counter_state = NORMAL_COUNT;
			_ch->sample_index = 0;

			_ch->process_step = 6;
			_ch->state = CH_IDLE;
			_ch->interval_ticks = get_sys_run_time ();
			_ch->max_interval.data_hl = 0;
			_ch->max_len.data_hl = 0;
			_ch->max_close_interval.data_hl = 0;
			_ch->max_area_sum.data_hl = 0;
			_ch->min_interval.data_hl = 0xFFFFFFFF;
			_ch->min_len.data_hl = 0xFFFFFFFF;
			_ch->min_close_interval.data_hl = 0xFFFFFFFF;
			_ch->min_area_sum.data_hl = 0xFFFFFFFF;
			_ch->area_sum.data_hl = 0;

			break;
		}
		case 6:{
			if (_ad_value_ < _ch->std_down_v){
				r_code = save_detect_data (_ch_id, &_ch->sample_index, _ad_value_);
				_ch->state = CH_BUSY;
				_ch->wave_down_flag++;
//				_ch->area_sum_buf += ad_change_v;

				if (_ad_value_ < _ch->ad_value_min_temp){
					_ch->ad_value_min_temp = _ad_value_;
				}
			}else{
				_ch->wave_down_flag = 0;
				_ch->sample_index = 0;
				_ch->state = CH_IDLE;
				_ch->ad_value_min_temp = 0xFFFF;
				_ch->ad_value_min = 0xFFFF;
//				_ch->area_sum_buf = 0;
			}

			if (_ch->wave_down_flag > WAVE_DOWN){//��⵽��ҩ��
				_ch->length_ticks = get_sys_run_time ();
				_ch->interval.data_hl = _ch->length_ticks - _ch->interval_ticks;
				///////////////////////////////////////////////////////////////////////////////////////////
				//����
				///////////////////////////////////////////////////////////////////////////////////////////
				_ch->cur_count++;
				if (_ch->counter_state == NORMAL_COUNT){//ͨ����������״̬
					if ((g_counter.total_count) < g_counter.set_count){//�жϵ�ǰ������������һƿ
						g_counter.total_count++;
						if (g_counter.total_count == g_counter.set_count){//��ǰ��һƿ�����һ��
							g_counter.counter_state = PRE_COUNT;//����������Ԥ����״̬
							g_counter.last_piece_chanel_id = _ch_id;
							if (g_counter.pre_count >= g_counter.set_pre_count){
								pause_vibrate();
							}
						}
					}else{//�Ѿ��ﵽ�趨�ļ���������ʼԤ��
						_ch->door_close_delay = g_counter.set_door_n_close_delay[_ch_id];/*С���Źر���ʱ*/
						_ch->close_interval.data_hl = _ch->interval.data_hl;
						if (_ch->close_interval.data_hl < g_counter.set_min_interval.data_hl){/*С���Źر�ʱҩ�����̫С*/
							g_counter.rej_flag_buf.data.h |= REJ_TOO_CLOSE;
							g_counter.rej_flag_buf.data.l |= REJ_TOO_CLOSE;
							REJECT_FLAG = 0;
							g_counter.rej_flag = g_counter.rej_flag_buf.data.l; /*�����޳�ԭ��*/
						}
						if (_ch->close_interval.data_hl > _ch->max_close_interval.data_hl){
							_ch->max_close_interval.data_hl = _ch->close_interval.data_hl;
							if (_ch->max_close_interval.data_hl > g_counter.max_close_interval.data_hl){
								g_counter.max_close_interval.data_hl = _ch->max_close_interval.data_hl;
							}
						}
						if (_ch->close_interval.data_hl < _ch->min_close_interval.data_hl){
							_ch->min_close_interval.data_hl = _ch->close_interval.data_hl;
							if (_ch->min_close_interval.data_hl < g_counter.min_close_interval.data_hl){
								g_counter.min_close_interval.data_hl = _ch->min_close_interval.data_hl;
							}
						}
						_ch->cur_count = 1;
						g_counter.pre_count++;
						if (g_counter.pre_count >= g_counter.set_pre_count){//�ﵽ�趨��Ԥ��
							pause_vibrate();
						}
						if (g_counter.pre_count > g_counter.set_count){//Ԥ�������趨��
							g_counter.rej_flag_buf.data.h |= REJ_TOO_MORE;
						}
						_ch->counter_state = PRE_COUNT;
						PRE_COUNT_FLAG = 0;
					}
				}else{// if (_ch->counter_state == PRE_COUNT){//ͨ��Ԥ����״̬
					g_counter.pre_count++;
					if (g_counter.pre_count >= g_counter.set_pre_count){//�ﵽ�趨��Ԥ��
						pause_vibrate();
					}
					if (g_counter.pre_count > g_counter.set_count){//Ԥ�������趨��
						g_counter.rej_flag_buf.data.h |= REJ_TOO_MORE;
					}
				}
				_ch->wave_down_flag = 0;
				_ch->ad_value_min_temp = _ad_value_;
				if (_ch->interval.data_hl > _ch->max_interval.data_hl ){
					if ( _ch->max_interval.data_hl > 0){
						_ch->max_interval.data_hl = _ch->interval.data_hl;
					}else{
						_ch->max_interval.data_hl = 1;//ͨ����һ������
					}
				}
				if (_ch->interval.data_hl < _ch->min_interval.data_hl){
					_ch->min_interval.data_hl = _ch->interval.data_hl;
					if (_ch->min_interval.data_hl < g_counter.min_interval.data_hl){
						g_counter.min_interval.data_hl = _ch->min_interval.data_hl;
					}
				}
				_ch->process_step = 16;
				///////////////////////////////////////////////////////////////////////////////////////////
			}
			break;
		}
		case 16:{

			r_code = save_detect_data (_ch_id, &_ch->sample_index, _ad_value_);

//			_ch->area_sum_buf += ad_change_v;

			if (_ad_value_ < _ch->ad_value_min_temp){
				_ch->ad_value_min_temp = _ad_value_;
				_ch->wave_up_flag = 0;
			}else if (_ad_value_ > _ch->ad_value_min_temp + WAVE_UP_V){
				_ch->wave_up_flag++;
			}

			if (_ch->wave_up_flag > WAVE_UP){//�����˲��Ⱥ�
				_ch->ad_value_min = _ch->ad_value_min_temp;
				_ch->ad_value_min_temp = AD_MAX_V;
				_ch->wave_up_flag = 0;
				_ch->process_step = 31;
			}

			break;
		}
		case 31:{/*�ж��Ƿ���ο�ֵ��ͬ�����,ȷ��������ֵ,���λָ����ο�ֵ*/

			r_code = save_detect_data (_ch_id, &_ch->sample_index, _ad_value_);

			if (_ad_value_ >= _ch->std_up_v){
				_ch->wave_up_flag++;
			}else{
				_ch->wave_up_flag = 0;
			}

			if (_ch->wave_up_flag > WAVE_UP){
				_ch->interval_ticks = get_sys_run_time ();
				_ch->len.data_hl = _ch->interval_ticks - _ch->length_ticks;
				if (_ch->len.data_hl > _ch->max_len.data_hl){
					_ch->max_len.data_hl = _ch->len.data_hl;
					if (_ch->max_len.data_hl > g_counter.max_len.data_hl){
						g_counter.max_len.data_hl = _ch->max_len.data_hl;
					}
				}
				if (_ch->len.data_hl < _ch->min_len.data_hl){
					_ch->min_len.data_hl = _ch->len.data_hl;
					if (_ch->min_len.data_hl < g_counter.min_len.data_hl){
						g_counter.min_len.data_hl = _ch->min_len.data_hl;
					}
				}

				_ch->area_sum.data_hl = ((g_counter.ch[_ch_id].std_v - _ch->ad_value_min) *_ch->len.data_hl) / 20;
//				_ch->area_sum.data_hl = _ch->area_sum_buf + ad_change_v;//�������
//				_ch->area_sum_buf = 0;
				if (_ch->area_sum.data_hl > _ch->max_area_sum.data_hl){
					_ch->max_area_sum.data_hl = _ch->area_sum.data_hl;
					if (_ch->max_area_sum.data_hl > g_counter.max_area_sum.data_hl){
						g_counter.max_area_sum.data_hl = _ch->max_area_sum.data_hl;
					}
				}
				if (_ch->area_sum.data_hl < _ch->min_area_sum.data_hl){
					_ch->min_area_sum.data_hl = _ch->area_sum.data_hl;
					if (_ch->min_area_sum.data_hl < g_counter.min_area_sum.data_hl){
						g_counter.min_area_sum.data_hl = _ch->min_area_sum.data_hl;
					}
				}

				//ҩ�����˼�����������޳��ź�////////////////////////////////////////////////////////////////////////
				if (_ch->counter_state == NORMAL_COUNT){//��������
					if (_ch->len.data_hl > g_counter.set_max_len.data_hl){ //�����趨����
						g_counter.rej_flag_buf.data.l |= REJ_TOO_LONG;
					}else if (_ch->len.data_hl < g_counter.set_min_len.data_hl){//�����趨����
						g_counter.rej_flag_buf.data.l |= REJ_TOO_SHORT;
					}
					if (_ch->area_sum.data_hl > g_counter.set_max_area_sum.data_hl){ //�����趨���
						g_counter.rej_flag_buf.data.l |= REJ_TOO_BIG;
					}else if (_ch->area_sum.data_hl < g_counter.set_min_area_sum.data_hl){//�����趨���
						g_counter.rej_flag_buf.data.l |= REJ_TOO_SMALL;
					}
					if (g_counter.last_piece_chanel_id == _ch_id){//��ǰ��һƿ�����һ�����˵���
						SEND_COUNTER_FIN_SIGNAL ();//�������,������������ź�
					}
				}else if (_ch->counter_state == PRE_COUNT){//Ԥ����
					if (_ch->len.data_hl > g_counter.set_max_len.data_hl){ //�����趨����
						g_counter.rej_flag_buf.data.h |= REJ_TOO_LONG;
					}else if (_ch->len.data_hl < g_counter.set_min_len.data_hl){//�����趨����
						g_counter.rej_flag_buf.data.h |= REJ_TOO_SHORT;
					}
					if (_ch->area_sum.data_hl > g_counter.set_max_area_sum.data_hl){ //�����趨���
						g_counter.rej_flag_buf.data.h |= REJ_TOO_BIG;
					}else if (_ch->area_sum.data_hl < g_counter.set_min_area_sum.data_hl){//�����趨���
						g_counter.rej_flag_buf.data.h |= REJ_TOO_SMALL;
					}
				}
				_ch->process_step = 6;
				_ch->sample_size = _ch->sample_index;
				_ch->state = CH_DATA_RDY;
				_ch->sample_index = 0;
				_ch->wave_up_flag = 0;
			}

			break;
		}
	}
	return r_code;
}


////////////////////////////////////////////////////////////////////////////////

//void counter_process (void)
//{
//}

u16 counter_process_time = 0;
u16 dma_irq_cycle = 0;
uint16_t tim5_dma_cur_cnt = 0;
uint16_t tim5_dma_pre_cnt = 0;
void DMA1_Channel1_IRQHandler(void)
{
	static int process_rdy_old = 0;
	int r_code = 0, i;
	//tick_old = get_tim5_ticks();
	//refresh_dma1_cycle (); //��ͳ��DMA�ж�����
	tim5_dma_cur_cnt = get_tim5_ticks();
	dma_irq_cycle = tim5_dma_cur_cnt - tim5_dma_pre_cnt;
	tim5_dma_pre_cnt = tim5_dma_cur_cnt;
	if ((dma_irq_cycle > 2100) && (process_rdy >= PROCESS_RDY)){
		counter_process_state = 0xE001;
	}
/////////////////////////////////////////////////////////////////////////////////
//	u8 count;
	if(DMA_GetITStatus(DMA1_IT_HT1)){
		g_counter.AD_buf_p = AD_DMA_buf.AD_Value_0;
	}else if(DMA_GetITStatus(DMA1_IT_TC1)){
		g_counter.AD_buf_p = AD_DMA_buf.AD_Value_1;
	}else if (DMA_GetITStatus(DMA1_IT_TE1)){
		g_counter.AD_buf_p = 0;
	}
	DMA_ClearITPendingBit(DMA1_IT_GL1); //���ȫ���жϱ�־
	if (g_counter.AD_buf_p != 0){
		if (process_rdy < PROCESS_RDY){
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 0, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 1, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 2, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 3, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 4, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 5, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 6, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 7, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 8, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 9, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 10, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_buf_p, 11, SAMPLE_NUM);

			if ((process_rdy + 1) == PROCESS_RDY){
				for (i = 0; i < CHANEL_NUM; i++){
					if (g_counter.ch[i].std_v > STD_UP_V_OFFSET) {
						g_counter.ch[i].std_up_v = g_counter.ch[i].std_v - STD_UP_V_OFFSET;
					}else{
						g_counter.ch[i].std_up_v = g_counter.ch[i].std_v;
					}
					if (g_counter.ch[i].std_v > STD_DOWN_V_OFFSET) {
						g_counter.ch[i].std_down_v = g_counter.ch[i].std_v - STD_DOWN_V_OFFSET;
					}else{
						g_counter.ch[i].std_down_v = g_counter.ch[i].std_v;
					}
				}
				process_rdy = PROCESS_RDY;
				COUNTER_FINISH_OP ();
			}else{
				process_rdy_old = process_rdy;
			}
		}else{
		//////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////// process begin ///////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////

			AD_FILTER (After_filter, g_counter.AD_buf_p, 0, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 1, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 2, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 3, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 4, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 5, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 6, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 7, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 8, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 9, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 10, SAMPLE_NUM);
			AD_FILTER (After_filter, g_counter.AD_buf_p, 11, SAMPLE_NUM);

			//After_filter[0] = g_counter.sim_ad_value;
			r_code += count_piece (&g_counter.ch[0], After_filter[0], 0);
			r_code += count_piece (&g_counter.ch[1], After_filter[1], 1);
			r_code += count_piece (&g_counter.ch[2], After_filter[2], 2);
			r_code += count_piece (&g_counter.ch[3], After_filter[3], 3);
			r_code += count_piece (&g_counter.ch[4], After_filter[4], 4);
			r_code += count_piece (&g_counter.ch[5], After_filter[5], 5);
			r_code += count_piece (&g_counter.ch[6], After_filter[6], 6);
			r_code += count_piece (&g_counter.ch[7], After_filter[7], 7);
			r_code += count_piece (&g_counter.ch[8], After_filter[8], 8);
			r_code += count_piece (&g_counter.ch[9], After_filter[9], 9);
			r_code += count_piece (&g_counter.ch[10], After_filter[10], 10);
			r_code += count_piece (&g_counter.ch[11], After_filter[11], 11);

			if (my_env.print == 1){
				if (r_code != 0){
				}else if (g_counter.ch[g_counter.set_watch_ch].state == CH_DATA_RDY){
					if (my_env.dma_state == 0){
						my_env.dma_state = 1;
						g_counter.buf_addr = (u32)&Detect_Buf[0];
						OSQPost(debug_msg, (void *) 0x55);//������Ϣ
					}
				}
			}else if ((AD_buff.buffer_en == 1)){
				AD_buff.buffer[AD_buff.buffer_index] = After_filter[g_counter.set_watch_ch];
				AD_buff.buffer_index++;
				if (AD_buff.buffer_index >= AD_BUFF_SIZE){
					AD_buff.buffer_index = 0;
					AD_buff.buffer_en = 0;
					OSQPost(debug_msg, (void *) 0x55);//������Ϣ
				}
			}

		//	counter_process_state = r_code;
		//////////////////////////////// process end /////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////
		}
	}
//////////////////////////////////////////////////////////////////////
	counter_process_time = get_tim5_ticks () - tim5_dma_cur_cnt + 2;
}



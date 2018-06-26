#ifndef __AD_SAMPLE__
#define __AD_SAMPLE__

#define SAMPLE_NUM 8 //每通道采样次数
#define CHANEL_NUM 12 //为12个通道
#define CHANEL_SENSOR_NUM 8

#define PROCESS_RDY 15


#define WAVE_DOWN 	g_counter.set_wave_down_flag //16
#define WAVE_UP 	g_counter.set_wave_up_flag //16
#define WAVE_UP_V 	g_counter.set_wave_up_value //10


#define STD_VALUE 31000
//#define STD_DOWN_V_OFFSET g_counter.set_std_down_v_offset
//#define STD_UP_V_OFFSET g_counter.set_std_up_v_offset
#define STD_DOWN_V_OFFSET g_counter.ch[i].std_down_offset
#define STD_UP_V_OFFSET g_counter.ch[i].std_up_offset
//#define STD_DOWN_V (STD_VALUE - STD_DOWN_V_OFFSET)
//#define STD_UP_V (STD_VALUE - STD_UP_V_OFFSET)

#define AD_MAX_V 4096 * 8

#define CH0 	ADC_Channel_0
#define CH1 	ADC_Channel_1
#define CH2 	ADC_Channel_2
#define CH3 	ADC_Channel_3
#define CH4 	ADC_Channel_14
#define CH5 	ADC_Channel_15
#define CH6 	ADC_Channel_6
#define CH7 	ADC_Channel_7
#define CH8 	ADC_Channel_8
#define CH9 	ADC_Channel_9
#define CH10 	ADC_Channel_10
#define CH11 	ADC_Channel_11
#define CH12 	ADC_Channel_12
#define CH13 	ADC_Channel_13


#define AD_BUFF_SIZE 1024 * 2
#define AD_FITTER_BUFF_SIZE 8

//#define SAMPLE_BUF_SIZE 512 //每通道采50次
#define SET_SENSOR_EN_PORT GPIOE
#define SET_SENSOR_EN_PIN GPIO_Pin_6
#define WRITE_SENSOR_ADDR(ADDR) GPIO_Write(GPIOE, ((GPIO_ReadOutputData(GPIOE) & (~(7 << 3))) | (ADDR<<3)))
#define RESET_SENSOR_EN() GPIO_ResetBits(SET_SENSOR_EN_PORT, SET_SENSOR_EN_PIN)
#define SET_SENSOR_EN() GPIO_SetBits(SET_SENSOR_EN_PORT, SET_SENSOR_EN_PIN)


#define ENABLE_SENSOR() SET_SENSOR_EN()
#define DISABLE_SENSOR() RESET_SENSOR_EN()


#define DETECTG_BUF_SIZE 1024 * 4
#define DETECTG_BUF_GROUP 2
#define AD_DMA_BUF_GROUP 2

//Rej flag
#define REJ_TOO_MORE 	0x0001 //多数
#define REJ_TOO_LONG 	0x0002 //超长
#define REJ_TOO_SHORT 	0x0004 //超短
#define REJ_TOO_BIG 	0x0008 //面积太大
#define REJ_TOO_SMALL 	0x0010 //面积太小
#define REJ_TOO_CLOSE 	0x0020 //关门间隔太小



#define OPEN_DOOR(CH) { \
	g_counter.ch[CH].door_close_delay = 0; \
	g_counter.ch[CH].cur_count = 0; \
	g_counter.last_piece_chanel_id = 0xFFFF; \
	g_counter.ch[CH].counter_state = NORMAL_COUNT; \
	DOOR_##CH = 1; \
}
#define CHANEL_INIT(CH) { \
	OPEN_DOOR(CH) \
	g_counter.ch[CH].max_interval.data_hl = 0; \
	g_counter.ch[CH].max_len.data_hl = 0; \
	g_counter.ch[CH].max_close_interval.data_hl = 0; \
	g_counter.ch[CH].max_area_sum.data_hl = 0; \
	g_counter.ch[CH].min_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_len.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_close_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_area_sum.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].interval.data_hl = 0; \
	g_counter.ch[CH].close_interval.data_hl = 0; \
	g_counter.ch[CH].len.data_hl = 0; \
	g_counter.ch[CH].area_sum.data_hl = 0; \
	g_counter.ch[CH].cur_count = 0; \
}
#define CHANEL_DATA_CLEAR(CH) { \
	g_counter.ch[CH].ad_max = 0; \
	g_counter.ch[CH].max_interval.data_hl = 0; \
	g_counter.ch[CH].max_len.data_hl = 0; \
	g_counter.ch[CH].max_close_interval.data_hl = 0; \
	g_counter.ch[CH].max_area_sum.data_hl = 0; \
	g_counter.ch[CH].min_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_len.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_close_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_area_sum.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].ad_min = 0xFFFF; \
}

#define SEND_COUNTER_FIN_SIGNAL() { \
	if (g_counter.rej_flag_buf.data.l > 0){ \
		REJECT_FLAG = 0; \
		g_counter.rej_flag = g_counter.rej_flag_buf.data.l; /*保存最后一次剔除原因*/ \
	} \
	g_counter.counter_fin_signal_delay = g_counter.set_min_interval.data_hl+20; \
}

#define COUNTER_FINISH_OP() { \
	COUNT_COMPLETE = 0;  \
	g_counter.complete_count++; /*数粒完成信号+1*/ \
}


enum CHANEL_STATE
{
	CH_IDLE = 0,
	CH_BUSY,
	CH_DATA_RDY
};

enum COUNTER_STATE
{
	COUNTER_IDLE = 0,
	NORMAL_COUNT,
	PRE_COUNT
};

typedef struct
{
	S16 std_down_value0;
	S16 std_up_value0;
	S16 ad0_averaged_value;
	S16 ad1_averaged_value;
	S16 ad2_averaged_value;
	S16 ad0_step;
	S16 ad1_step;
	S16 ad2_step;
	S16 cmp_use_index;
	U16 AD_min_index[3];
}s_counter_env;

typedef struct
{
	u16 buffer[AD_BUFF_SIZE];
	u16 buffer_index;
	u16 buffer_en;
	u16 cir;
}s_buf;


typedef union{
	U32 data_hl;
	struct{
		U16 l;
		U16 h;
	}data;
}s_32;

typedef struct
{
	//s_chanel_pos pos[CHANEL_SENSOR_NUM];
	U16 process_step;
	U16 wave_down_flag;
	U16 wave_up_flag;
	U16 ad_value_min;
	U16 ad_value_min_temp;
	U16 cur_count;
	U16 counter_state;
	U16 std_down_v;
	U16 std_up_v;
	U16 std_v;
	U16 std_down_offset;
	U16 std_up_offset;
	U16 ad_min;
	U16 ad_max;
	U16 sample_index;
	U16 sample_size;
	U16 state;
	U16 door_close_delay;
	U32 ad_averaged_value;
	U16 ad_fitter_buff[AD_FITTER_BUFF_SIZE];
	U16 ad_fitter_index;
	uint32_t area_sum_buf;//截面积
	s_32 area_sum;//截面积
	s_32 min_area_sum;
	s_32 max_area_sum;
	s_32 len;//长度
	s_32 min_len;
	s_32 max_len;
	s_32 interval;
	s_32 close_interval;
	s_32 min_close_interval;
	s_32 max_close_interval;
	s_32 min_interval;
	s_32 max_interval;
	uint32_t interval_ticks;
	uint32_t length_ticks;
}s_chanel_info;

typedef struct
{
	s_chanel_info ch[CHANEL_NUM];
	U16 set_count;
	U16 total_count;
	U16 counter_state;
	U16 set_door_close_delay;
	U16 set_adc_mode;
	U16 set_pre_count;
	U16 pre_count;
	U16 total_reject;
	U16 total_good;
	U16 dma_buf_index;
	U16 AD_use_buf_index;
	U16 set_watch_ch;
	U32 dma_buf_addr;
	U32 buf_addr;
	vu16 (* AD_buf_p)[CHANEL_NUM];
	U16 counter_step;
	U16 set_std_up_v_offset;
	U16 set_std_down_v_offset;
	U16 set_wave_down_flag;
	U16 set_wave_up_flag;
	U16 set_wave_up_value;
	U16 counter_fin_signal_delay;
	U16 last_piece_chanel_id;//最后一粒所在的通道号
	U16 rej_flag;
	U16 rej_flag_clear_delay;
	s_32 rej_flag_buf;
	s_32 area_sum;//截面积
	s_32 min_area_sum;
	s_32 max_area_sum;
	s_32 set_min_len;
	s_32 set_max_len;
	s_32 set_min_interval;
	s_32 set_max_interval;
	s_32 set_min_area_sum;
	s_32 set_max_area_sum;
	s_32 min_len;
	s_32 max_len;
	s_32 min_interval;
	s_32 min_close_interval;
	s_32 max_close_interval;
	U32 complete_count;
	U32 complete_res;
	U16 sim_ad_value;
	U16 sim_flag;
	U16 set_door_n_close_delay[CHANEL_NUM];
}s_counter_info;

void AD_filter(U16 _detect_chanel_index, U16 _chanel_pos_index);
int AD_Sample_init (void);
void re_calibration_detect (void);
u16 GetVolt(u16 advalue);
extern u16 After_filter[CHANEL_NUM]; //用来存放求平均值之后的结果
extern s_counter_env counter_env;
//extern vu16 Detect_Buf[DETECTG_BUF_GROUP][DETECTG_BUF_SIZE];
extern vu16 Detect_Buf[DETECTG_BUF_SIZE];

extern U16 ADC1_irq_cycle;
extern U16 ADC1_process_time;

extern u16 dma_irq_cycle;
extern u16 counter_process_time;
extern int counter_process_state;

extern U16 detect_chanel_index;//检测通道索引
extern U16 chanel_pos_index;	//通道光敏二极管位置索引
extern s_counter_info g_counter;

extern s_buf AD_buff;


extern U16 process_rdy;
extern u16 wave_down_flag;
extern u16 wave_up_flag;
extern u16 wave_up_value;

//void counter_process (void);
void counter_init (void);
void counter_reset (void);
void counter_data_clear(void);
void start_vibrate (void);
void stop_vibrate (void);
void pause_vibrate (void);
void AD_Start_Sample (u32 _memBaseAddr);

#endif


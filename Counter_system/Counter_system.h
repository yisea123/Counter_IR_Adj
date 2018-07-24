#ifndef __COUNTER_SYSTEM_
#define __COUNTER_SYSTEM_


//Rej flag
#define REJ_TOO_MORE 								0x0001 //多数
#define REJ_TOO_LONG 								0x0002 //超长
#define REJ_TOO_SHORT 							0x0004 //超短
#define REJ_TOO_BIG 								0x0008 //面积太大
#define REJ_TOO_SMALL 							0x0010 //面积太小
#define REJ_TOO_CLOSE 							0x0020 //关门间隔太小
#define REJ_DOOR_SWITCH_TOO_FAST 		0x0040 //开关间隔太小


#define FLAG_CLEAR_DELAY 50000





#define OPEN_DOOR(CH) { \
	g_counter.ch[CH].ch_door_close_delay = 0; \
	DOOR_##CH = 1; \
	g_counter.ch[CH].door_open_ticks = get_sys_run_time (); \
}

#define OPEN_ALL_DOOR() { \
	OPEN_DOOR(0); \
	OPEN_DOOR(1); \
	OPEN_DOOR(2); \
	OPEN_DOOR(3); \
	OPEN_DOOR(4); \
	OPEN_DOOR(5); \
	OPEN_DOOR(6); \
	OPEN_DOOR(7); \
	OPEN_DOOR(8); \
	OPEN_DOOR(9); \
	OPEN_DOOR(10); \
	OPEN_DOOR(11); \
}

#define UPDATE_CHANEL_STATUS(CH, STATUS) { \
	g_counter.ch[CH].cur_count = 0; \
	g_counter.last_piece_chanel_id = 0xFF; \
	g_counter.ch[CH].counter_state = STATUS; \
}

#define UPDATE_ALL_CHANEL_STATUS(STATUS) { \
	UPDATE_CHANEL_STATUS(0, STATUS); \
	UPDATE_CHANEL_STATUS(1, STATUS); \
	UPDATE_CHANEL_STATUS(2, STATUS); \
	UPDATE_CHANEL_STATUS(3, STATUS); \
	UPDATE_CHANEL_STATUS(4, STATUS); \
	UPDATE_CHANEL_STATUS(5, STATUS); \
	UPDATE_CHANEL_STATUS(6, STATUS); \
	UPDATE_CHANEL_STATUS(7, STATUS); \
	UPDATE_CHANEL_STATUS(8, STATUS); \
	UPDATE_CHANEL_STATUS(9, STATUS); \
	UPDATE_CHANEL_STATUS(10, STATUS); \
	UPDATE_CHANEL_STATUS(11, STATUS); \
	g_counter.rej_flag_buf.data_hl >>= 16; \
	g_counter.count.data_hl >>= 16; \
}

#define SET_CHANEL_STATUS(CH,STATUS) { \
	g_counter.ch[CH].counter_state = STATUS; \
}
#define SET_ALL_CHANEL_STATUS(STATUS) { \
	SET_CHANEL_STATUS(0, STATUS); \
	SET_CHANEL_STATUS(1, STATUS); \
	SET_CHANEL_STATUS(2, STATUS); \
	SET_CHANEL_STATUS(3, STATUS); \
	SET_CHANEL_STATUS(4, STATUS); \
	SET_CHANEL_STATUS(5, STATUS); \
	SET_CHANEL_STATUS(6, STATUS); \
	SET_CHANEL_STATUS(7, STATUS); \
	SET_CHANEL_STATUS(8, STATUS); \
	SET_CHANEL_STATUS(9, STATUS); \
	SET_CHANEL_STATUS(10, STATUS); \
	SET_CHANEL_STATUS(11, STATUS); \
}

#define UPDATA_PIECE_INFO() { \
	_ch->interval.data_hl  = get_sys_run_time () - _ch->interval_ticks ; \
	_ch->interval_ticks = get_sys_run_time ();/*记录新时间戳*/ \
	if (_ch->interval.data_hl > _ch->max_interval.data_hl ){ \
		if ( _ch->max_interval.data_hl > 0){ \
			_ch->max_interval.data_hl = _ch->interval.data_hl; \
		}else{ \
			_ch->max_interval.data_hl = 1;/*通道第一粒出现*/ \
		} \
	} \
	if (_ch->interval.data_hl < _ch->min_interval.data_hl){ \
		_ch->min_interval.data_hl = _ch->interval.data_hl; \
		if (_ch->min_interval.data_hl < g_counter.min_interval.data_hl){ \
			g_counter.min_interval.data_hl = _ch->min_interval.data_hl; \
		} \
	} \
	if (_ch->len.data_hl > _ch->max_len.data_hl){ \
		_ch->max_len.data_hl = _ch->len.data_hl; \
		if (_ch->max_len.data_hl > g_counter.max_len.data_hl){ \
			g_counter.max_len.data_hl = _ch->max_len.data_hl; \
		} \
	} \
	if (_ch->len.data_hl < _ch->min_len.data_hl){ \
		_ch->min_len.data_hl = _ch->len.data_hl; \
		if (_ch->min_len.data_hl < g_counter.min_len.data_hl){ \
			g_counter.min_len.data_hl = _ch->min_len.data_hl; \
		} \
	} \
	_ch->area_sum.data_hl = ((_ch->std_v - _ch->ad_value_min) *_ch->len.data_hl) / 20; \
	if (_ch->area_sum.data_hl > _ch->max_area_sum.data_hl){ \
		_ch->max_area_sum.data_hl = _ch->area_sum.data_hl; \
		if (_ch->max_area_sum.data_hl > g_counter.max_area_sum.data_hl){ \
			g_counter.max_area_sum.data_hl = _ch->max_area_sum.data_hl; \
		} \
	} \
	if (_ch->area_sum.data_hl < _ch->min_area_sum.data_hl){ \
		_ch->min_area_sum.data_hl = _ch->area_sum.data_hl; \
		if (_ch->min_area_sum.data_hl < g_counter.min_area_sum.data_hl){ \
			g_counter.min_area_sum.data_hl = _ch->min_area_sum.data_hl; \
		} \
	} \
}
//
#define CHECK_PRE_COUNT_CLOSE_DOOR_INTERVAL() { \
	_ch->close_door_interval.data_hl = _ch->interval.data_hl; \
	if (_ch->close_door_interval.data_hl > _ch->max_close_door_interval.data_hl){ \
		_ch->max_close_door_interval.data_hl = _ch->close_door_interval.data_hl; \
		if (_ch->max_close_door_interval.data_hl > g_counter.max_close_door_interval.data_hl){ \
			g_counter.max_close_door_interval.data_hl = _ch->max_close_door_interval.data_hl; \
		} \
	} \
	if (_ch->close_door_interval.data_hl < _ch->min_close_door_interval.data_hl){ \
		_ch->min_close_door_interval.data_hl = _ch->close_door_interval.data_hl; \
		if (_ch->min_close_door_interval.data_hl < g_counter.min_close_door_interval.data_hl){ \
			g_counter.min_close_door_interval.data_hl = _ch->min_close_door_interval.data_hl; \
		} \
	} \
	/*判断是否小料门关闭时药粒间隔太小*/ \
	if (_ch->close_door_interval.data_hl < g_counter.set_door_close_interval.data_hl){ \
		g_counter.rej_flag_buf.data_hl |= (REJ_TOO_CLOSE | REJ_TOO_CLOSE << 16); \
	} \
}
//
#define CHECK_PRE_COUNT_DOOR_SWITCH_INTERVAL() { \
	_ch->door_switch_interval.data_hl = get_sys_run_time () - _ch->door_open_ticks; \
	if (_ch->min_door_switch_interval.data_hl > _ch->door_switch_interval.data_hl){ \
		_ch->min_door_switch_interval.data_hl = _ch->door_switch_interval.data_hl; \
	} \
	if (_ch->max_door_switch_interval.data_hl < _ch->door_switch_interval.data_hl){ \
		_ch->max_door_switch_interval.data_hl = _ch->door_switch_interval.data_hl; \
	} \
	/*判断是否小料门开关间隔太小*/ \
	if (_ch->door_switch_interval.data_hl < g_counter.set_door_switch_interval){ \
		/*开关频率太快，需额外加一段延时等待料门完全打开*/ \
		_ch->ch_door_close_delay += g_counter.set_door_close_ex_delay; \
		g_counter.rej_flag_buf.data_hl |= (REJ_DOOR_SWITCH_TOO_FAST | REJ_DOOR_SWITCH_TOO_FAST << 16); \
	} \
}
//


#define CHECK_NORMAL_COUNT_LENGTH() { \
	if (_ch->len.data_hl > g_counter.set_max_len.data_hl){ /*超过设定长度*/ \
		g_counter.rej_flag_buf.data.current_bottle |= REJ_TOO_LONG; \
	}else if (_ch->len.data_hl < g_counter.set_min_len.data_hl){/*低于设定长度*/ \
		g_counter.rej_flag_buf.data.current_bottle |= REJ_TOO_SHORT; \
	} \
}

#define CHECK_NORMAL_COUNT_AREA() { \
	if (_ch->area_sum.data_hl > g_counter.set_max_area_sum.data_hl){ /*超过设定面积*/ \
		g_counter.rej_flag_buf.data.current_bottle |= REJ_TOO_BIG; \
	}else if (_ch->area_sum.data_hl < g_counter.set_min_area_sum.data_hl){/*低于设定面积*/ \
		g_counter.rej_flag_buf.data.current_bottle |= REJ_TOO_SMALL; \
	} \
}


#define CHECK_PRE_COUNT_LENGTH() { \
	if (_ch->len.data_hl > g_counter.set_max_len.data_hl){ /*超过设定长度*/ \
		g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_LONG; \
	}else if (_ch->len.data_hl < g_counter.set_min_len.data_hl){/*低于设定长度*/ \
		g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_SHORT; \
	} \
}

#define CHECK_PRE_COUNT_AREA() { \
	if (_ch->area_sum.data_hl > g_counter.set_max_area_sum.data_hl){ /*超过设定面积*/ \
		g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_BIG; \
	}else if (_ch->area_sum.data_hl < g_counter.set_min_area_sum.data_hl){/*低于设定面积*/ \
		g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_SMALL; \
	} \
}
//

#define CHANEL_INIT(CH) { \
	OPEN_DOOR(CH) \
	g_counter.ch[CH].max_interval.data_hl = 0; \
	g_counter.ch[CH].max_len.data_hl = 0; \
	g_counter.ch[CH].max_close_door_interval.data_hl = 0; \
	g_counter.ch[CH].max_area_sum.data_hl = 0; \
	g_counter.ch[CH].max_door_switch_interval.data_hl = 0; \
	g_counter.ch[CH].min_door_switch_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_len.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_close_door_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_area_sum.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].interval.data_hl = 0; \
	g_counter.ch[CH].close_door_interval.data_hl = 0; \
	g_counter.ch[CH].len.data_hl = 0; \
	g_counter.ch[CH].area_sum.data_hl = 0; \
	g_counter.ch[CH].cur_count = 0; \
	g_counter.total_count_sum.data_hl = 0; \
}
#define CHANEL_DATA_CLEAR(CH) { \
	g_counter.ch[CH].ad_max = 0; \
	g_counter.ch[CH].max_interval.data_hl = 0; \
	g_counter.ch[CH].max_len.data_hl = 0; \
	g_counter.ch[CH].max_close_door_interval.data_hl = 0; \
	g_counter.ch[CH].max_area_sum.data_hl = 0; \
	g_counter.ch[CH].max_door_switch_interval.data_hl = 0; \
	g_counter.ch[CH].min_door_switch_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_len.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_close_door_interval.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].min_area_sum.data_hl = 0xFFFFFFFF; \
	g_counter.ch[CH].ad_min = 0xFFFF; \
}

#define SEND_COUNTER_FIN_SIGNAL(TIME) { \
	if (g_counter.rej_flag_buf.data.current_bottle > 0){ \
		REJECT_FLAG = 0; \
		g_counter.rej_flag = g_counter.rej_flag_buf.data.current_bottle; /*保存最后一次剔除原因*/ \
	} \
	g_counter.counter_fin_signal_delay = ((g_counter.set_door_switch_interval > g_counter.set_door_close_interval.data_hl) ? \
																				 g_counter.set_door_switch_interval : g_counter.set_door_close_interval.data_hl) + 200 + TIME; \
}

#define COUNTER_FINISH_OP() { \
	COUNT_COMPLETE = 0;  \
	g_counter.complete_count++; /*数粒完成信号+1*/ \
	g_counter.complete_res++; /*数粒完成信号+1*/ \
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
	SEPARATE_PRE_COUNT,
	PRE_COUNT
};

enum SYSTEM_STATE
{
	RUNNING_OK = 0,
	COUNTER_ERROR,
	STATUS_ERROR,
	ADC_TIME_ERROR,
	DETECTOR_ERROR
};

typedef struct{
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




typedef union{
	U32 data_hl;
	struct{
		U16 l;
		U16 h;
	}data;
}s_32;


typedef union{
	U32 data_hl;
	struct{
		U16 normal_count;
		U16 pre_count;
	}data;
}s_ctr;


typedef union{
	U32 data_hl;
	struct{
		U16 current_bottle;
		U16 next_bottle;
	}data;
}s_rej;

typedef struct{
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
	U16 piece_in;
	U16 piece_in_new;
	U16 piece_in_old;
	U32 piece_in_time;
	U16 set_ch_door_close_delay;
	U16 ch_door_close_delay;
	U16 ad_fitter_index;
	S32 ad_averaged_value;
	uint32_t ad_fitter_buff[AD_FITTER_BUFF_SIZE];
	uint32_t area_sum_buf;//截面积
	s_32 area_sum;//截面积
	s_32 min_area_sum;
	s_32 max_area_sum;
	s_32 len;//长度
	s_32 min_len;
	s_32 max_len;
	s_32 interval;
	s_32 close_door_interval;
	s_32 min_close_door_interval;
	s_32 max_close_door_interval;
	s_32 min_interval;
	s_32 max_interval;
	s_32 door_switch_interval;
	s_32 min_door_switch_interval;
	s_32 max_door_switch_interval;
	uint32_t door_open_ticks;
	uint32_t interval_ticks;
	uint32_t length_start_ticks;
}s_chanel_info;

typedef struct{
	s_chanel_info ch[CHANEL_NUM];
	U16 set_count;
	U16 set_pre_count;
	U16 set_count_new;
	U16 set_pre_count_new;
	U16 normal_count;
	U16 counter_state;
	U16 set_door_close_delay;
	U16 set_adc_mode;
	U16 pre_count;
	U16 total_reject;
	U16 total_good;
	U16 dma_buf_index;
	U16 AD_use_buf_index;
	U16 set_watch_ch;
	U32 dma_buf_addr;
	U32 buf_addr;
	U16 (* AD_buf_p)[CHANEL_NUM];
	U16 counter_step;
	U16 set_std_denumerator;
	U16 set_std_numerator;
	U16 set_wave_down_flag;
	U16 set_wave_up_flag;
	U16 set_wave_up_value;
	U16 set_door_switch_interval;
	U16 set_door_close_ex_delay;
	U16 set_vib_restart_delay;
	U16 set_pre_count_threshold;
	U16 std_ref_value_old;
	U16 std_ref_value;
	U16 std_ref_value_offset;
	U16 counter_fin_signal_delay;
	U16 last_piece_chanel_id;//最后一粒所在的通道号
	U16 rej_flag;
	U16 rej_flag_clear_delay;
	s_ctr count;
	s_rej rej_flag_buf;
	s_32 total_count_sum;
	s_32 area_sum;//截面积
	s_32 min_area_sum;
	s_32 max_area_sum;
	s_32 set_min_len; 
	s_32 set_max_len;
	s_32 set_door_close_interval;
	s_32 set_max_interval;
	s_32 set_min_area_sum;
	s_32 set_max_area_sum;
	s_32 min_len;
	s_32 max_len;
	s_32 min_interval;
	s_32 min_close_door_interval;
	s_32 max_close_door_interval;
	U32 complete_count;
	U32 complete_res;
	U16 sim_ad_value;
	U16 sim_flag;
	U16 set_door_n_close_delay[CHANEL_NUM];
	U16 running_status;
	U16 system_status;
	U16 view_IR_DA_value[CHANEL_NUM];
}s_counter_info;
//

extern s_counter_info g_counter;
//extern s_counter_env counter_env;
//void counter_process (void);
void counter_init (void);
void counter_reset (void);
void counter_data_clear(void);
void start_vibrate (void);
void stop_vibrate (void);
void pause_vibrate (void);
void count_pieces(s_chanel_info * _ch);


#endif










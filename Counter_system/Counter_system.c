#include "main.h"





s_counter_info g_counter;
//s_counter_env counter_env;

void counter_init (void)
{
	int i, j;
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
	//g_counter.counter_state = COUNTER_IDLE;

	for (i = 0; i < CHANEL_NUM; i++){
		g_counter.ch[i].ad_min = 0xFFFF;
		g_counter.ch[i].ad_max = 0;
		g_counter.ch[i].ad_averaged_value = 0;
		for (j = 0; j < AD_FITTER_BUFF_SIZE; j++){
			g_counter.ch[i].ad_fitter_buff[j] = 0;
		}
	}

	g_counter.sim_ad_value = 35000;

	g_counter.max_len.data_hl = 0;
	g_counter.max_close_door_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_door_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;
}
//
void counter_reset (void)
{
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
	g_counter.normal_count = 0;
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
	g_counter.max_close_door_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_door_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;
	stop_vibrate ();
	REJECT_FLAG = 1;//剔除标志
	PRE_COUNT_FLAG = 1;
	g_counter.counter_step = 0;
	//g_counter.counter_state = COUNTER_IDLE;
	COUNT_COMPLETE = 0;
	g_counter.complete_count = 0;//数粒完成信号
	g_counter.complete_res = 0;//数粒完成信号
	OS_EXIT_CRITICAL();
}
//
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
	g_counter.max_close_door_interval.data_hl = 0;
	g_counter.max_area_sum.data_hl = 0;
	g_counter.min_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_len.data_hl = 0xFFFFFFFF;
	g_counter.min_close_door_interval.data_hl = 0xFFFFFFFF;
	g_counter.min_area_sum.data_hl = 0xFFFFFFFF;

	OS_EXIT_CRITICAL();
}


//
void pause_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}
//
void start_vibrate (void)
{
#if OS_CRITICAL_METHOD == 3u                           /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();//关中断<-------------------------- 1
	OPEN_ALL_DOOR();//打开所有小料门,此时通道状态仍然是PRE_COUNT状态，因此数量会累加pre_count的变量上
	///////////////////////////////////////////////////////
	//改参数后下一瓶生效///////////////////////////////////
	g_counter.set_count = g_counter.set_count_new;
	g_counter.set_pre_count = g_counter.set_pre_count_new;
	///////////////////////////////////////////////////////
	OS_EXIT_CRITICAL();//开中断<--------------------------- 1
	if ((g_counter.set_count > g_counter.pre_count) && 
			((g_counter.set_count - g_counter.pre_count) < g_counter.set_pre_count_threshold)){//判断预数粒是否很接近装量
		if (VIBRATE_SWITCH == 0){//如果是，而且振动器已经停下来了,或者说没有药粒经过电眼了
			delay_ms (g_counter.set_vib_restart_delay);//如果是，而且振动器已经停下来了则延时一段时间再启动振动器
		}
	}
	OS_ENTER_CRITICAL();//关中断<-------------------------- 2
	if ((g_counter.rej_flag_buf.data.h != 0)){//如果这一瓶将要被剔除，那么没必要再数下去了，直接给装瓶信号，此刻振动器应该处于停止状态
		if (g_counter.pre_count < g_counter.set_count){
			g_counter.pre_count = g_counter.set_count;
		}
	}
	OS_EXIT_CRITICAL();//开中断<-------------------------- 2
	if (g_counter.pre_count < g_counter.set_count){
		OS_ENTER_CRITICAL();//关中断<-------------------------- 3
		g_counter.rej_flag_buf.data_hl >>= 16;
		g_counter.normal_count = g_counter.pre_count;
		g_counter.pre_count = 0;
		UPDATE_ALL_CHANEL_STATUS(NORMAL_COUNT);
		PRE_COUNT_FLAG = 1;
		VIBRATE_SWITCH = 0;
		OS_EXIT_CRITICAL();//开中断<-------------------------- 3
	}else{//预数粒多数或者刚好数够
		delay_ms (g_counter.set_vib_restart_delay);//延时一段时间再给信号
		OS_ENTER_CRITICAL();//关中断<-------------------------- 4
		g_counter.rej_flag_buf.data_hl >>= 16;
		g_counter.normal_count = g_counter.pre_count;//这里的pre_count已经是数够了的
		g_counter.pre_count = 0;
		UPDATE_ALL_CHANEL_STATUS(SEPARATE_PRE_COUNT);
		SEND_COUNTER_FIN_SIGNAL ();
		g_counter.rej_flag_buf.data.l = 0;
		if (g_counter.pre_count < g_counter.set_pre_count){//达到设定的预数
			VIBRATE_SWITCH = 0;
		}
		OS_EXIT_CRITICAL();//开中断<-------------------------- 4
	}
}
//
void stop_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}
//






















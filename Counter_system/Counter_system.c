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
	g_counter.count.data.normal_count = 0;
	g_counter.count.data.pre_count = 0;
	g_counter.total_reject = 0;
	g_counter.total_good = 0;
	g_counter.rej_flag = 0;
	g_counter.rej_flag_buf.data_hl = 0;
	g_counter.system_status = RUNNING_OK;
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
	VIBRATE_SWITCH = VIB_STOP;
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
	//*****************************************************************************************************************
	if ((g_counter.set_count > g_counter.count.data.pre_count) && 
			((g_counter.set_count - g_counter.count.data.pre_count) < g_counter.set_pre_count_threshold)){//判断预数粒是否很接近装量
		if (VIBRATE_SWITCH == 0){//如果是，而且振动器已经停下来了,或者说没有药粒经过电眼了
			delay_ms (g_counter.set_vib_restart_delay);//如果是，而且振动器已经停下来了则延时一段时间再启动振动器
		}
	}
	//***************************************************************************************************************	
	OS_ENTER_CRITICAL();//关中断<-------------------------- 2   
	if (g_counter.system_status == RUNNING_OK){
		if ((g_counter.rej_flag_buf.data.next_bottle != 0)){//如果这一瓶将要被剔除，那么没必要再数下去了，直接给装瓶信号，此刻振动器应该处于停止状态
			if (g_counter.count.data.pre_count < g_counter.set_count){
				g_counter.count.data.pre_count = g_counter.set_count;
			}
		}
		if (g_counter.count.data.pre_count < g_counter.set_count){
			UPDATE_ALL_CHANEL_STATUS(NORMAL_COUNT);//继续正常数粒
			PRE_COUNT_FLAG = 1;
			VIBRATE_SWITCH = VIB_START;
		}else{//预数粒多数或者刚好数够
			UPDATE_ALL_CHANEL_STATUS(SEPARATE_PRE_COUNT);//准备预数粒
			SEND_COUNTER_FIN_SIGNAL (5000);//500ms
			if (g_counter.count.data.pre_count < g_counter.set_pre_count){//达到设定的预数
				VIBRATE_SWITCH = VIB_START;
			}
		}
	}
	OS_EXIT_CRITICAL();//开中断<-------------------------- 2
}
//
void stop_vibrate (void)
{
	VIBRATE_SWITCH = VIB_STOP;
}
//


////////////////////////////////////////////////////////////////////////////////
void count_pieces(s_chanel_info * _ch)
{
	_ch->piece_in_new = _ch->piece_in;
	///////////////////////////////////////////////////////////
	if ((_ch->piece_in_new == 0) && (_ch->piece_in_old == 0)){      //电眼没有药粒状态
	}else if ((_ch->piece_in_new == 1) && (_ch->piece_in_old == 0)){//药粒刚进电眼状态
		_ch->length_start_ticks = get_sys_run_time ();//记录药粒进入电眼的时间戳，用于后面的长度计算
	}else if ((_ch->piece_in_new == 1) && (_ch->piece_in_old == 1)){//药粒进入电眼状态
	}else if ((_ch->piece_in_new == 0) && (_ch->piece_in_old == 1)){//药粒刚出电眼状态
		_ch->len.data_hl = get_sys_run_time () - _ch->length_start_ticks;
		if (_ch->len.data_hl >= g_counter.set_min_len.data_hl){//长度大于设定值最小长度才能计数
			/*药粒出了检测区，更新药粒相关信息****************************************************************/
			UPDATA_PIECE_INFO(); 
			///////////////////////////////////////////////////////////////////////////////////////////
			//计数/////////////////////////////////////////////////////////////////////////////////////
			_ch->cur_count++;
			g_counter.total_count_sum.data_hl++;
			///////////////////////////////////////////////////////////////////////////////////////////
			switch (_ch->counter_state)
			{
				case NORMAL_COUNT://通道正常数粒状态
					if (g_counter.count.data.normal_count >= g_counter.set_count){//错误状态
						g_counter.system_status = COUNTER_ERROR;
					}
					CHECK_NORMAL_COUNT_LENGTH();
					CHECK_NORMAL_COUNT_AREA();
					if (g_counter.rej_flag_buf.data.current_bottle != 0){//如果要剔除，就不用继续数了
						g_counter.count.data.normal_count = g_counter.set_count;
					}else{
						g_counter.count.data.normal_count++;
					}
					if (g_counter.count.data.normal_count == g_counter.set_count){//当前这一瓶的最后一粒
						SET_ALL_CHANEL_STATUS(SEPARATE_PRE_COUNT);//通知其他通道下一颗要进行分药动作
	//					g_counter.last_piece_chanel_id = _ch_id;//记录发出通知的通道ID
						SEND_COUNTER_FIN_SIGNAL (0);//数粒完成,发送数粒完成信号
						if (g_counter.count.data.pre_count >= g_counter.set_pre_count){
							VIBRATE_SWITCH = VIB_STOP;
						}
					}
					break;
				case SEPARATE_PRE_COUNT://每个通道的下一瓶的第一颗药，需要小料门分药动作
					_ch->ch_door_close_delay = _ch->set_ch_door_close_delay;/*小料门关闭延时*/
					CHECK_PRE_COUNT_LENGTH();
					CHECK_PRE_COUNT_AREA();
					CHECK_PRE_COUNT_CLOSE_DOOR_INTERVAL ();
					CHECK_PRE_COUNT_DOOR_SWITCH_INTERVAL();
					_ch->cur_count = 1;//每个通道的下一瓶的第一颗药
					g_counter.count.data.pre_count++;
					if (g_counter.rej_flag_buf.data.current_bottle != 0){//出现关门间隔太小和料门开关间隔太小需要补充当前这一瓶的剔除信号
						REJECT_FLAG = 0;
						g_counter.rej_flag = g_counter.rej_flag_buf.data.current_bottle; /*更新剔除原因*/
					}
					if (g_counter.rej_flag_buf.data.next_bottle != 0){
						VIBRATE_SWITCH = VIB_STOP;
					}
					if (g_counter.count.data.pre_count >= g_counter.set_pre_count){//达到设定的预数
						VIBRATE_SWITCH = VIB_STOP;
					}
					if (g_counter.count.data.pre_count > g_counter.set_count){//预数超过设定数
						g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_MORE;
					}
					_ch->counter_state = PRE_COUNT;
					PRE_COUNT_FLAG = 0;
					break;
				case PRE_COUNT://通道预数粒状态
					CHECK_PRE_COUNT_LENGTH();
					CHECK_PRE_COUNT_AREA();
					g_counter.count.data.pre_count++;
					if (g_counter.rej_flag_buf.data.next_bottle != 0){//如果要剔除，就不用继续数了
						VIBRATE_SWITCH = VIB_STOP;
					}
					if (g_counter.count.data.pre_count >= g_counter.set_pre_count){//达到设定的预数
						VIBRATE_SWITCH = VIB_STOP;
					}
					if (g_counter.count.data.pre_count > g_counter.set_count){//预数超过设定数
						g_counter.rej_flag_buf.data.next_bottle |= REJ_TOO_MORE;//更新剔除原因
					}
					break;
				default://错误状态
					g_counter.system_status = STATUS_ERROR;
					break;
				}
		}else{//长度小于设定值最小长度不计数
		}
		////////////////////////////////////////////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////
	_ch->piece_in_old = _ch->piece_in_new;
}
//




















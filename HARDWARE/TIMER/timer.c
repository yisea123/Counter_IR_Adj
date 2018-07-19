#include "main.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20120904
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  
unsigned int indexWave[41] = {1,1,2,2,3,4,6,8,10,14,19,25,33,44,59,80,
        107,143,191,210,230,210,191,143,107,80,59,44,33,25,19,14,10,8,6,4,3,2,2,1,1};
   	  
//通用定时器1中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_DeInit (TIM2);
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM2_INT_PREEM;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM2_INT_SUB;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设							 
}
//定时器2中断服务程序
u16 tim2_irq_process_time = 0;
#define CHECK_DOOR_CLOSE_FLAG(CH) if (g_counter.ch[CH].door_close_delay > 0){ \
				g_counter.ch[CH].door_close_delay--; \
				if ((g_counter.ch[CH].door_close_delay == 0) && (g_counter.counter_state == PRE_COUNT)){ \
					DOOR_##CH = 0; \
				} \
			}
//
#define CHECK_PIECE_IN_STATUS(CH) if (g_counter.ch[CH].piece_in == 1){ \
	g_counter.ch[CH].piece_in_time++; \
}
			


uint32_t sys_run_time	= 0;//100us的精度
void TIM2_IRQHandler(void)   //TIM2中断
{
	unsigned long long tick_old;
	tick_old = get_tim5_ticks();
///////////////////////////////////////////////////////////////////////////////////////////
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源  
		sys_run_time++;
		CHECK_DOOR_CLOSE_FLAG (0);
		CHECK_DOOR_CLOSE_FLAG (1);
		CHECK_DOOR_CLOSE_FLAG (2);
		CHECK_DOOR_CLOSE_FLAG (3);
		CHECK_DOOR_CLOSE_FLAG (4);
		CHECK_DOOR_CLOSE_FLAG (5);
		CHECK_DOOR_CLOSE_FLAG (6);
		CHECK_DOOR_CLOSE_FLAG (7);
		CHECK_DOOR_CLOSE_FLAG (8);
		CHECK_DOOR_CLOSE_FLAG (9);
		CHECK_DOOR_CLOSE_FLAG (10);
		CHECK_DOOR_CLOSE_FLAG (11);
		if (g_counter.counter_fin_signal_delay > 0){
			g_counter.counter_fin_signal_delay--;
			if (g_counter.counter_fin_signal_delay == 0){//数粒完成信号
				if (REJECT_FLAG == 0){
					g_counter.total_reject++;
				}else{
					g_counter.total_good++;
				}
				COUNTER_FINISH_OP ();
			}
		}
		if (g_counter.rej_flag_clear_delay > 0){
			g_counter.rej_flag_clear_delay--;
			if (g_counter.rej_flag_clear_delay == 0){
				if (g_counter.rej_flag_buf.data.l == 0){//如果当前没有剔除，则清零剔除原因
					g_counter.rej_flag = 0;
				}
			}
		}
		
		CHECK_PIECE_IN_STATUS (0);
		CHECK_PIECE_IN_STATUS (1);
		CHECK_PIECE_IN_STATUS (2);
		CHECK_PIECE_IN_STATUS (3);
		CHECK_PIECE_IN_STATUS (4);
		CHECK_PIECE_IN_STATUS (5);
		CHECK_PIECE_IN_STATUS (6);
		CHECK_PIECE_IN_STATUS (7);
		CHECK_PIECE_IN_STATUS (8);
		CHECK_PIECE_IN_STATUS (9);
		CHECK_PIECE_IN_STATUS (10);
		CHECK_PIECE_IN_STATUS (11);
	}
///////////////////////////////////////////////////////////////////////////////////////////
	tim2_irq_process_time = get_tim5_ticks () - tick_old + 2;
}


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = LED3_MAP; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM3_INT_PREEM;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM3_INT_SUB;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	//static u8 dir=1;
 	static u16 led0pwmval=0;
	static u16 delay = 0;
	static u16 tim3_count = 0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){ //检查指定的TIM中断发生与否:TIM 中断源 
	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		delay++;
		if (delay ==  (5 * (TIM3_ARR + 1) / PMW_WIDTH )){ //1ms	
			delay = 0;
			TIM_SetCompare2(TIM3, indexWave[led0pwmval++]);
			if( led0pwmval >=  41){
				led0pwmval = 0;                                             
			}
		}
		tim3_count++;
//////////////////////////////////////////////////////////////////////////////		
		if (g_counter.sim_flag == 0x55){
			g_counter.sim_ad_value -= 1000;
			if (g_counter.sim_ad_value == 5000){
				g_counter.sim_flag = 0xaa;
			}
		}else if (g_counter.sim_flag == 0xaa){	
			g_counter.sim_ad_value += 1000;
			if (g_counter.sim_ad_value > 35000){
				g_counter.sim_flag = 0;
			}
		}
		if (tim3_count == 1000){
		////////////////////////////////////////////////////////////////////////
			if (process_rdy < (PROCESS_RDY - 1)){
				process_rdy++;
			}
			check_data ();
			tim3_count = 0;
		////////////////////////////////////////////////////////////////////////
		}
		if (my_env.ad_8804_cmd_timeout > 0){
			my_env.ad_8804_cmd_timeout--;
		}
/////////////////////////////////////////////////////////////////////////////////		
	}
}




//TIM4 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB外设
 
   //设置该引脚为复用输出功能,输出TIM4 CH4的PWM脉冲波形	GPIOB.9
	GPIO_InitStructure.GPIO_Pin = LED1_MAP; //TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM4_INT_PREEM;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM4_INT_SUB;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	//初始化TIM4 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
}

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
 	static u16 led0pwmval=0;
	static u16 delay = 0;
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){ //检查指定的TIM中断发生与否:TIM 中断源 
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		delay++;
		if (delay == (4 * (TIM4_ARR + 1) / PMW_WIDTH)){ //2ms
			delay = 0;
			TIM_SetCompare4(TIM4, indexWave[led0pwmval++]);
			if( led0pwmval >=  41){
				led0pwmval = 0; 
			}				
		}
	}
}


//TIM5 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM5_PWM_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能定时器3时钟

   //初始化TIM5
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	
//	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //使能指定的TIM5中断,允许更新中断

//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM5_INT_PREEM;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM5_INT_SUB;  //从优先级2级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
	TIM_Cmd(TIM5, ENABLE);  //使能TIM5
}

//定时器4中断服务程序
//unsigned long long tim5_ticks = 0;
uint16_t tim5_adc1_cur_cnt = 0;
uint16_t tim5_adc1_pre_cnt = 0;
void TIM5_IRQHandler(void)   //TIM5中断
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		tim5_ticks++;
	}
}

//void refresh_dma1_cycle (void)
//{
//	//tim5_dma_cur_cnt = tim5_ticks * 65536 + TIM5->CNT
//	tim5_dma_cur_cnt = TIM5->CNT;
//	dma_irq_cycle = tim5_dma_cur_cnt - tim5_dma_pre_cnt;
//	tim5_dma_pre_cnt = tim5_dma_cur_cnt;
//	if ((dma_irq_cycle > 400) && (process_rdy >= PROCESS_RDY)){
//		counter_process_state = 0xE001;
//	}
//}

void refresh_adc1_cycle (void)
{
	//tim5_adc1_cur_cnt = tim5_ticks * 65536 + TIM5->CNT;
	tim5_adc1_cur_cnt = TIM5->CNT;
	ADC1_irq_cycle = tim5_adc1_cur_cnt - tim5_adc1_pre_cnt;
	tim5_adc1_pre_cnt = tim5_adc1_cur_cnt;
}
//TIM6 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM6_PWM_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	//使能定时器3时钟

   //初始化TIM6
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
//	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //使能指定的TIM6中断,允许更新中断

//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级2级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
	//TIM_Cmd(TIM6, ENABLE);  //使能TIM6
}


//定时器7初始化
void TIM7_PWM_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //TIM7时钟使能

	//TIM7初始化设置
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值 设置计数频率为10kHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );//TIM7 允许更新中断

	//TIM7中断分组配置
	NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;  //TIM7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM7_INT_PREEM;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM7_INT_SUB;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器                                                                  
}
///////////////////////////////////////////////////////////////////////////////////////
//用定时器7判断接收空闲时间，当空闲时间大于指定时间，认为一帧结束
//定时器7中断服务程序         
void TIM7_IRQHandler(void)
{  
	OSIntEnter();
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//清除中断标志
		TIM_Cmd(TIM7,DISABLE);//停止定时器
		if (my_env.system_runing == 1){
			OSQPost(modbusRTU_msg, (void *) 0x55);//发送消息
		}
	}
	OSIntExit();
}




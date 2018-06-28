#include "main.h"


u8 auchCRCHi[]=
{
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40

};

u8 auchCRCLo[] =
{
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};

u16 CRC16(u8 * _data_buf,u16 len)
{
	u8 uchCRCHi=0xff;
	u8 uchCRCLo=0xff;
	u16 uindex;
	while(len--){
		uindex = uchCRCHi^ *_data_buf++;
		uchCRCHi = uchCRCLo^auchCRCHi[uindex];
		uchCRCLo = auchCRCLo[uindex];
	}
	return (uchCRCHi<<8|uchCRCLo);
}



///////////////////////////////////////////////////////////

u8 RS485_tx_buf[256];//发送缓冲区

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Modbus寄存器和单片机寄存器的映射关系
static vu32 *Modbus_InputIO[MODBUS_INPUT_NUM];//输入开关量寄存器指针(这里使用的是位带操作)
vu32 *Modbus_OutputIO[MODBUS_OUTPUT_NUM];//输出开关量寄存器指针(这里使用的是位带操作)
u16 *Modbus_HoldReg[MODBUS_REG_NUM];//保持寄存器

vu32 virtual_input[MODBUS_VIRTUAL_INPUT_NUM];

#define MAP_MODBUS_INPUT(D,PORT,S) Modbus_InputIO[D]=(vu32*)&P##PORT##in(S)
#define MAP_MODBUS_OUTPUT(D,PORT,S) Modbus_OutputIO[D]=(vu32*)&P##PORT##out(S)
#define MAP_MODBUS_HOLDREG(D,V) {Modbus_HoldReg[D] = &V;}

U16 Modbus_HoldReg_CPU_Usage = 0;
U16 Modbus_HoldReg_NULL = 0xFFFF;
U16 Modbus_com_error = 0;
U16 data_change_flag = 0;

void Modbus_RegMap(void)
{
	int i;
	//输入开关量寄存器指针指向
	MAP_MODBUS_INPUT (0, C, 6);
	MAP_MODBUS_INPUT (1, C, 7);
	MAP_MODBUS_INPUT (2, A, 8);
	MAP_MODBUS_INPUT (3, G, 11);
	MAP_MODBUS_INPUT (4, G, 0);
	MAP_MODBUS_INPUT (5, G, 1);
	MAP_MODBUS_INPUT (6, G, 2);
	MAP_MODBUS_INPUT (7, G, 3);
//	Modbus_InputIO[0]=(vu32*)&PCin(6);//KEY0

	//输出开关量寄存器指针指向
	MAP_MODBUS_OUTPUT (0, F, 0);
	MAP_MODBUS_OUTPUT (1, F, 1);
	MAP_MODBUS_OUTPUT (2, F, 2);
	MAP_MODBUS_OUTPUT (3, F, 3);
	MAP_MODBUS_OUTPUT (4, F, 4);
	MAP_MODBUS_OUTPUT (5, F, 5);
	MAP_MODBUS_OUTPUT (6, F, 6);
	MAP_MODBUS_OUTPUT (7, F, 7);
	MAP_MODBUS_OUTPUT (8, F, 8);
	MAP_MODBUS_OUTPUT (9, F, 9);
	MAP_MODBUS_OUTPUT (10, F, 10);
	MAP_MODBUS_OUTPUT (11, F, 11);
	MAP_MODBUS_OUTPUT (12, F, 12);
	MAP_MODBUS_OUTPUT (13, F, 13);
	MAP_MODBUS_OUTPUT (14, F, 14);
	MAP_MODBUS_OUTPUT (15, F, 15);
	MAP_MODBUS_OUTPUT (16, E, 3);
	MAP_MODBUS_OUTPUT (17, E, 4);
	MAP_MODBUS_OUTPUT (18, E, 5);
	MAP_MODBUS_OUTPUT (19, E, 6);
//	Modbus_OutputIO[0]=(vu32*)&PFout(0);//LED0
	for (i = 0; i < MODBUS_VIRTUAL_INPUT_NUM; i++){
		virtual_input[i] = 1;
		Modbus_OutputIO[20 + i] = &virtual_input[i];
	}

	//初始化保持寄存器指针指向///////////////////////////////////
	for (i = 0; i < MODBUS_REG_NUM; i++){
		Modbus_HoldReg[i] = &Modbus_HoldReg_NULL;
	}
//	MAP_MODBUS_HOLDREG(0, OSCPUUsage);
//	for (i = 0; i < 12; i++){
//		MAP_MODBUS_HOLDREG(0 + i, g_counter.ch[i].cur_count);
//	}
	MAP_MODBUS_HOLDREG(12, dma_irq_cycle);
	MAP_MODBUS_HOLDREG(13, counter_process_time);
	MAP_MODBUS_HOLDREG(14, tim2_irq_process_time);
	MAP_MODBUS_HOLDREG(15, ADC1_irq_cycle);
	MAP_MODBUS_HOLDREG(16, ADC1_process_time);
	MAP_MODBUS_HOLDREG(17, g_counter.last_piece_chanel_id);

	MAP_MODBUS_HOLDREG(20, chanel_pos_index);
	MAP_MODBUS_HOLDREG(21, Modbus_com_error);
	MAP_MODBUS_HOLDREG(22, g_counter.total_count);
	MAP_MODBUS_HOLDREG(23, g_counter.pre_count);
	MAP_MODBUS_HOLDREG(24, g_counter.counter_step);
	MAP_MODBUS_HOLDREG(25, g_counter.total_reject);
	MAP_MODBUS_HOLDREG(26, my_env.print);
	MAP_MODBUS_HOLDREG(27, g_counter.rej_flag);
	MAP_MODBUS_HOLDREG(28, g_counter.total_good);
	MAP_MODBUS_HOLDREG(29, Modbus_HoldReg_CPU_Usage);

	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 0, 	g_counter.set_count);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 1, 	g_counter.set_pre_count);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 2, 	g_counter.set_door_close_delay);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 3, 	g_counter.set_adc_mode);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 4, 	g_counter.set_max_interval.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 5, 	g_counter.set_max_interval.data.l);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 6, 	g_counter.set_min_interval.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 7, 	g_counter.set_min_interval.data.l);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 8, 	g_counter.set_max_len.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 9, 	g_counter.set_max_len.data.l);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 10, g_counter.set_min_len.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 11, g_counter.set_min_len.data.l);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 12, g_counter.set_std_numerator);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 13, g_counter.set_std_denumerator);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 14, g_counter.set_wave_down_flag);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 15, g_counter.set_wave_up_flag);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 16, g_counter.set_wave_up_value);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 17, g_counter.set_watch_ch);



	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 20, g_counter.set_max_area_sum.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 21, g_counter.set_max_area_sum.data.l);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 22, g_counter.set_min_area_sum.data.h);
	MAP_MODBUS_HOLDREG(MODBUS_SAVE_DATA_START + 23, g_counter.set_min_area_sum.data.l);

	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(64 + i, g_counter.ch[i].ad_min);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(76 + i, g_counter.ch[i].ad_max);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(88 + i, g_counter.ch[i].std_v);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(100 + i, After_filter[i]);
	}

	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(112 + i, g_counter.ch[i].cur_count);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(128 + i, g_counter.ch[i].std_down_offset);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(140 + i, g_counter.ch[i].std_up_offset);
	}

	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(152 + i * 2, g_counter.ch[i].max_interval.data.h);
		MAP_MODBUS_HOLDREG(153 + i * 2, g_counter.ch[i].max_interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(176 + i * 2, g_counter.ch[i].interval.data.h);
		MAP_MODBUS_HOLDREG(177 + i * 2, g_counter.ch[i].interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(200 + i * 2, g_counter.ch[i].min_interval.data.h);
		MAP_MODBUS_HOLDREG(201 + i * 2, g_counter.ch[i].min_interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(224 + i * 2, g_counter.ch[i].max_len.data.h);
		MAP_MODBUS_HOLDREG(225 + i * 2, g_counter.ch[i].max_len.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(248 + i * 2, g_counter.ch[i].len.data.h);
		MAP_MODBUS_HOLDREG(249 + i * 2, g_counter.ch[i].len.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(272 + i * 2, g_counter.ch[i].min_len.data.h);
		MAP_MODBUS_HOLDREG(273 + i * 2, g_counter.ch[i].min_len.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(296 + i * 2, g_counter.ch[i].max_close_interval.data.h);
		MAP_MODBUS_HOLDREG(297 + i * 2, g_counter.ch[i].max_close_interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(320 + i * 2, g_counter.ch[i].close_interval.data.h);
		MAP_MODBUS_HOLDREG(321 + i * 2, g_counter.ch[i].close_interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(344 + i * 2, g_counter.ch[i].min_close_interval.data.h);
		MAP_MODBUS_HOLDREG(345 + i * 2, g_counter.ch[i].min_close_interval.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(368 + i * 2, g_counter.ch[i].max_area_sum.data.h);
		MAP_MODBUS_HOLDREG(369 + i * 2, g_counter.ch[i].max_area_sum.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(392 + i * 2, g_counter.ch[i].area_sum.data.h);
		MAP_MODBUS_HOLDREG(393 + i * 2, g_counter.ch[i].area_sum.data.l);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(416 + i * 2, g_counter.ch[i].min_area_sum.data.h);
		MAP_MODBUS_HOLDREG(417 + i * 2, g_counter.ch[i].min_area_sum.data.l);
	}


	MAP_MODBUS_HOLDREG(495, g_counter.max_area_sum.data.h);
	MAP_MODBUS_HOLDREG(496, g_counter.max_area_sum.data.l);
	MAP_MODBUS_HOLDREG(497, g_counter.min_area_sum.data.h);
	MAP_MODBUS_HOLDREG(498, g_counter.min_area_sum.data.l);
	MAP_MODBUS_HOLDREG(499, g_counter.max_close_interval.data.h);
	MAP_MODBUS_HOLDREG(500, g_counter.max_close_interval.data.l);
	MAP_MODBUS_HOLDREG(501, g_counter.min_close_interval.data.h);
	MAP_MODBUS_HOLDREG(502, g_counter.min_close_interval.data.l);
	MAP_MODBUS_HOLDREG(503, g_counter.max_len.data.h);
	MAP_MODBUS_HOLDREG(504, g_counter.max_len.data.l);
	MAP_MODBUS_HOLDREG(505, g_counter.min_len.data.h);
	MAP_MODBUS_HOLDREG(506, g_counter.min_len.data.l);
	MAP_MODBUS_HOLDREG(507, g_counter.min_interval.data.h);
	MAP_MODBUS_HOLDREG(508, g_counter.min_interval.data.l);
	MAP_MODBUS_HOLDREG(509, g_counter.system_states);//地址510
//
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(512 + i, g_counter.set_door_n_close_delay[i]);
	}
	for (i = 0; i < 12; i++){
		MAP_MODBUS_HOLDREG(524 + i, g_counter.view_IR_DA_value[i]);
	}
	
	MAP_MODBUS_HOLDREG(536, g_counter.std_ref_value_old);
	MAP_MODBUS_HOLDREG(537, g_counter.std_ref_value);
	//
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1024 + i, AD_DMA_buf.AD_Value_0[i][0]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1032 + i, AD_DMA_buf.AD_Value_0[i][1]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1040 + i, AD_DMA_buf.AD_Value_0[i][2]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1048 + i, AD_DMA_buf.AD_Value_0[i][3]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1056 + i, AD_DMA_buf.AD_Value_0[i][4]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1064 + i, AD_DMA_buf.AD_Value_0[i][5]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1072 + i, AD_DMA_buf.AD_Value_0[i][6]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1080 + i, AD_DMA_buf.AD_Value_0[i][7]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1088 + i, AD_DMA_buf.AD_Value_0[i][8]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1096 + i, AD_DMA_buf.AD_Value_0[i][9]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1104 + i, AD_DMA_buf.AD_Value_0[i][10]);
	}
	for (i = 0; i < 8; i++){
		MAP_MODBUS_HOLDREG(1112 + i, AD_DMA_buf.AD_Value_0[i][11]);
	}
	

	save_para (0); //save_para(1) 保存参数save_para(0) 读取参数
	Modbus_HoldReg_NULL = 0;
	g_counter.set_watch_ch = CHANEL_NUM;
}




#define SPI_FLASH_INFO_ADDR		(12*1024*1024)  	//第一个应用程序起始地址(存放在FLASH)
typedef struct{
	char app_name[16];
	u32 app_size;
	char reg_info[16];
	U16 SAVE_DATA[MODBUS_SAVE_DATA_NUM];
#ifdef USE_SAVE_DATA_EX
	U16 SAVE_DATA_EX[MODBUS_SAVE_DATA_NUM_EX];
#endif
}s_spi_file;

int save_para (int flag)
{
	int i;
	char id[32];
	char hash[16];
	s_spi_file *spi_flash_info = NULL;

	if (flag == 1){
		if (data_change_flag == 0)
			return 0;
		else
			data_change_flag = 0;
	}
	spi_flash_info = malloc (sizeof (s_spi_file));
	if (spi_flash_info == NULL){
		my_println ("malloc (sizeof (s_modbus_save_data)) failed! save para abort!");
		return -1;
	}
//check reg info*****************************************************************************
	memset (id, 0, sizeof(id));
	GetLockCode (id);
	MD5Digest(id, hash);
	W25QXX_Read ((U8*)spi_flash_info, SPI_FLASH_INFO_ADDR, sizeof(s_spi_file));
	for (i = 0; i < 16; i++){
		if (spi_flash_info->reg_info[i] != hash[i]){
			flag = -1;
			break;
		}
	}
//check reg info*****************************************************************************
	if (flag > 0){//保存参数
		for (i = 0; i < MODBUS_SAVE_DATA_NUM; i++){
			spi_flash_info->SAVE_DATA[i] = *Modbus_HoldReg[MODBUS_SAVE_DATA_START + i];
		}
	#ifdef USE_SAVE_DATA_EX
		for (i = 0; i < MODBUS_SAVE_DATA_NUM_EX; i++){
			spi_flash_info->SAVE_DATA_EX[i] = *Modbus_HoldReg[MODBUS_SAVE_DATA_START_EX + i];
		}
	#endif
		W25QXX_Write ((U8*)spi_flash_info, SPI_FLASH_INFO_ADDR, sizeof(s_spi_file));
	}else if(flag == 0){//读取参数
		for (i = 0; i < MODBUS_SAVE_DATA_NUM; i++){
			*Modbus_HoldReg[MODBUS_SAVE_DATA_START + i] = spi_flash_info->SAVE_DATA[i];
		}
	#ifdef USE_SAVE_DATA_EX
		for (i = 0; i < MODBUS_SAVE_DATA_NUM_EX; i++){
			*Modbus_HoldReg[MODBUS_SAVE_DATA_START_EX + i] = spi_flash_info->SAVE_DATA_EX[i];
		}
	#endif
	}
	if (flag == -1){
		my_env.is_registered = NOT_REGISTERED;
		my_println("-_-");//未注册
	}else{
		my_env.is_registered = REGISTERED;
		my_println("^_^");//已注册
	}

	if (spi_flash_info != NULL)
		free (spi_flash_info);
	return 0;
}

void check_data (void)
{
	int i;
	if ((g_counter.set_std_numerator < 1) || (g_counter.set_std_numerator > 100)){
		g_counter.set_std_numerator = 5;
	}
	if ((g_counter.set_wave_down_flag < 1) || (g_counter.set_wave_down_flag > 1000)){
		g_counter.set_wave_down_flag = 8;
	}
	if ((g_counter.set_wave_up_flag < 1) || (g_counter.set_wave_up_flag > 1000)){
		g_counter.set_wave_up_flag = 8;
	}
	if ((g_counter.set_wave_up_value < 1) || (g_counter.set_wave_up_value > 1000)){
		g_counter.set_wave_up_value = 16;
	}
	if (g_counter.set_std_denumerator < 1){
		g_counter.set_std_denumerator = 1;
	}
	if ((g_counter.set_adc_mode < 1) || (g_counter.set_adc_mode > 7)){
		g_counter.set_adc_mode = 3;
	}
	if (g_counter.set_min_interval.data_hl < 5){
		g_counter.set_min_interval.data_hl = 5;
	}
	for (i = 0; i < CHANEL_NUM; i++){
		if (g_counter.set_door_close_delay == 0){
			if (g_counter.set_door_n_close_delay[i] < 1){
				g_counter.set_door_n_close_delay[i] = 1;
			}
		}else{
			g_counter.set_door_n_close_delay[i] = g_counter.set_door_close_delay;
		}
		if (g_counter.std_ref_value != g_counter.std_ref_value_old){
			g_counter.view_IR_DA_value[i] = 200;
		}
		if (g_counter.view_IR_DA_value[i] > 255){
			g_counter.view_IR_DA_value[i] = 200;
		}
	}
	g_counter.std_ref_value_old = g_counter.std_ref_value;
	DATA_RANGE_CHECK ();
}

void modbus_init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启GPIOB和GPIOF的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG, ENABLE);
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	/*设置引脚速率为50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*选择要控制的GPIOB引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	/*调用库函数，初始化GPIOG*/
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/* 关闭所有led灯	*/
	GPIO_SetBits(GPIOG, GPIO_Pin_8);

	RS485_TX_EN=0;//开启接收模式

	Modbus_RegMap ();
	check_data ();
}
void Modbus_01_Handle(u8 * _data_buf);
void Modbus_02_Handle(u8 * _data_buf);
void Modbus_03_Handle(u8 * _data_buf);
void Modbus_05_Handle(u8 * _data_buf);
void Modbus_06_Handle(u8 * _data_buf);
void Modbus_15_Handle(u8 * _data_buf);
void Modbus_16_Handle(u8 * _data_buf);

//////////////////////////////////////////////////////////////////////////////
//发送n个字节数据
//buff:发送区首地址
//len：发送的字节数
void RS485_SendData(u8 *buff, u8 len)
{
	if (RS485_tx_buf[1] & 0x80){
		Modbus_com_error++;
	}
#if (MODBUS_RTU_USE_UART == 1)
	start_uart1_dma ((u32)RS485_tx_buf, len);
#endif
#if (MODBUS_RTU_USE_UART == 3)
	RS485_TX_EN = 1;//切换为发送模式
	start_uart3_dma ((u32)RS485_tx_buf, len);
#endif
}

void modbus_analyze(u8 * _data_buf)
{
	u16 crc;
	u16 startRegAddr;
	if((_data_buf[1]==01)||(_data_buf[1]==02)||(_data_buf[1]==03)||(_data_buf[1]==05)||(_data_buf[1]==06)||(_data_buf[1]==15)||(_data_buf[1]==16))//功能码正确
	{
		startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
		if(startRegAddr < MODBUS_REG_NUM+1){//寄存器地址在范围内
		#if (MODBUS_RTU_USE_UART == 1)
			crc = cmd_analyze.rec_buf[ - 2] << 8 | cmd_analyze.rec_buf[ - 1];
			if (crc == CRC16 (cmd_analyze.rec_buf,  - 2)){//CRC校验正确
		#elif (MODBUS_RTU_USE_UART == 3)
			crc = uart3_rec_buf[uart3_rec_count - 2] << 8 | uart3_rec_buf[uart3_rec_count - 1];
			if (crc == CRC16 (uart3_rec_buf, uart3_rec_count - 2)){//CRC校验正确
		#endif
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				switch(_data_buf[1])//根据不同的功能码进行处理
				{
					case 1:{//读输出开关量
						Modbus_01_Handle(_data_buf);
						break;
					}
					case 2:{//读输入开关量
						Modbus_02_Handle(_data_buf);
						break;
					}
					case 03:{//读多个寄存器
						Modbus_03_Handle(_data_buf);
						break;
					}
					case 5:{//写单个输出开关量
						Modbus_05_Handle(_data_buf);
						OSQPost(io_msg, (void *) 0xaa);//发送消息
						break;
					}
					case 06: {//写单个寄存器
						Modbus_06_Handle(_data_buf);
						break;
					}
					case 15:{//写多个输出开关量
						Modbus_15_Handle(_data_buf);
						OSQPost(io_msg, (void *) 0xaa);//发送消息
						break;
					}
					case 16:{ //写多个寄存器
						Modbus_16_Handle(_data_buf);
						break;
					}
				}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			else//CRC校验错误
			{
				RS485_tx_buf[0]=_data_buf[0];
				RS485_tx_buf[1]=_data_buf[1]| 0x80;
				RS485_tx_buf[2]=0x04; //异常码
				RS485_SendData(RS485_tx_buf,3);
			}
		}
		else//寄存器地址超出范围
		{
			RS485_tx_buf[0]=_data_buf[0];
			RS485_tx_buf[1]=_data_buf[1]|0x80;
			RS485_tx_buf[2]=0x02; //异常码
			RS485_SendData(RS485_tx_buf,3);
		}
	}
	else//功能码错误
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x01; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}


//Modbus功能码01处理程序
//读输出开关量
void Modbus_01_Handle(u8 * _data_buf)
{
	u16 ByteNum;
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//获取寄存器数量
	if((startRegAddr+RegNum - 1)<MODBUS_OUTPUT_NUM)//寄存器地址+数量在范围内
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		ByteNum=RegNum/8;//字节数
		if(RegNum%8) ByteNum+=1;//如果位数还有余数，则字节数+1
		RS485_tx_buf[2]=ByteNum;//返回要读取的字节数
		for(i=0;i<RegNum;i++)
		{
			if(i%8==0) RS485_tx_buf[3+i/8]=0x00; //新字节开始
			RS485_tx_buf[3+i/8] >>= 1;//低位先发送
			RS485_tx_buf[3+i/8] |= ((*Modbus_OutputIO[startRegAddr+i])<<7)&0x80;
			if(i==RegNum-1)//发送到最后一个位了
			{
				if(RegNum%8) RS485_tx_buf[3+i/8] >>= 8-(RegNum%8);//如果最后一个字节还有余数，则剩余MSB填充0
			}
		}
		calCRC=CRC16(RS485_tx_buf,ByteNum+3);
		RS485_tx_buf[ByteNum+3]=(calCRC>>8)&0xFF;
		RS485_tx_buf[ByteNum+4]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,ByteNum+5);
	}
	else//寄存器地址+数量超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}


//Modbus功能码02处理程序
//读输入开关量
void Modbus_02_Handle(u8 * _data_buf)
{
	u16 ByteNum;
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//获取寄存器数量
	if((startRegAddr+RegNum - 1)<MODBUS_INPUT_NUM)//寄存器地址+数量在范围内
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		ByteNum=RegNum/8;//字节数
		if(RegNum%8) ByteNum+=1;//如果位数还有余数，则字节数+1
		RS485_tx_buf[2]=ByteNum;//返回要读取的字节数
		for(i=0;i<RegNum;i++)
		{
			if(i%8==0) RS485_tx_buf[3+i/8]=0x00;
			RS485_tx_buf[3+i/8]>>=1;//低位先发送
			RS485_tx_buf[3+i/8]|=((*Modbus_InputIO[startRegAddr+i])<<7)&0x80;
			if(i==RegNum-1)//发送到最后一个位了
			{
				if(RegNum%8) RS485_tx_buf[3+i/8]>>=8-(RegNum%8);//如果最后一个字节还有余数，则剩余MSB填充0
			}
		}
		calCRC=CRC16(RS485_tx_buf,ByteNum+3);
		RS485_tx_buf[ByteNum+3]=(calCRC>>8)&0xFF;
		RS485_tx_buf[ByteNum+4]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,ByteNum+5);
	}
	else//寄存器地址+数量超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}


//Modbus功能码03处理程序
//读保持寄存器
void Modbus_03_Handle(u8 * _data_buf)
{
	u8 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//获取寄存器数量
	if((startRegAddr+RegNum - 1)<MODBUS_REG_NUM)//寄存器地址+数量在范围内
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		RS485_tx_buf[2]=RegNum * 2;
		for(i=0;i<RegNum;i++)
		{
			RS485_tx_buf[3+i*2] = (*Modbus_HoldReg[startRegAddr+i] >> 8) & 0xFF; //先发送高字节
			RS485_tx_buf[4+i*2] = *Modbus_HoldReg[startRegAddr+i] & 0xFF;//后发送低字节
		}
		calCRC=CRC16(RS485_tx_buf,RegNum*2+3);

        RS485_tx_buf[RegNum*2+3]=(calCRC>>8)&0xFF;
        RS485_tx_buf[RegNum*2+4]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,RegNum*2+5);
	}
	else//寄存器地址+数量超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}



//Modbus功能码05处理程序
//写单个输出开关量
void Modbus_05_Handle(u8 * _data_buf)
{
	u16 calCRC;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	if(startRegAddr < MODBUS_OUTPUT_NUM)//寄存器地址在范围内
	{
		if((_data_buf[4]==0xFF)||(_data_buf[5]==0xFF)) *Modbus_OutputIO[startRegAddr]=0x01;
		else *Modbus_OutputIO[startRegAddr]=0x00;

		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		RS485_tx_buf[2]=_data_buf[2];
		RS485_tx_buf[3]=_data_buf[3];
		RS485_tx_buf[4]=_data_buf[4];
		RS485_tx_buf[5]=_data_buf[5];

		calCRC=CRC16(RS485_tx_buf,6);
		RS485_tx_buf[6]=(calCRC>>8)&0xFF;
		RS485_tx_buf[7]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,8);
	}
	else//寄存器地址超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}


//Modbus功能码06处理程序
//写单个保持寄存器
void Modbus_06_Handle(u8 * _data_buf)
{
	u16 calCRC;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	if(startRegAddr < MODBUS_REG_NUM)//寄存器地址在范围内
	{
		*Modbus_HoldReg[startRegAddr] = ((u16)_data_buf[4]) << 8;//高字节在前
		*Modbus_HoldReg[startRegAddr] |= _data_buf[5];//低字节在后

		check_data ();
		if (((startRegAddr < MODBUS_SAVE_DATA_START + MODBUS_SAVE_DATA_NUM + 1) && (startRegAddr >= MODBUS_SAVE_DATA_START)) ||
			  ((startRegAddr < MODBUS_SAVE_DATA_START_EX + MODBUS_SAVE_DATA_NUM_EX + 1) && (startRegAddr >= MODBUS_SAVE_DATA_START_EX))
			 ){
			data_change_flag = 1;
			save_para (1); //save_para(1) 保存参数save_para(0) 读取参数
		}

		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		RS485_tx_buf[2]=_data_buf[2];
		RS485_tx_buf[3]=_data_buf[3];
		RS485_tx_buf[4]=_data_buf[4];
		RS485_tx_buf[5]=_data_buf[5];

		calCRC=CRC16(RS485_tx_buf,6);
		RS485_tx_buf[6]=(calCRC>>8)&0xFF;
		RS485_tx_buf[7]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,8);
	}
	else//寄存器地址超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}
//Modbus功能码15处理程序
//写多个输出开关量
void Modbus_15_Handle(u8 * _data_buf)
{
	u16 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	RegNum=(((u16)_data_buf[4])<<8)|_data_buf[5];//获取寄存器数量
	if((startRegAddr+RegNum - 1)<MODBUS_OUTPUT_NUM)//寄存器地址+数量在范围内
	{
		for(i=0;i<RegNum;i++)
		{
		        if(_data_buf[7+i/8]&0x01) *Modbus_OutputIO[startRegAddr+i]=0x01;
		        else *Modbus_OutputIO[startRegAddr+i]=0x00;
		        _data_buf[7+i/8]>>=1;//从低位开始
		}

		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		RS485_tx_buf[2]=_data_buf[2];
		RS485_tx_buf[3]=_data_buf[3];
		RS485_tx_buf[4]=_data_buf[4];
		RS485_tx_buf[5]=_data_buf[5];
		calCRC=CRC16(RS485_tx_buf,6);
		RS485_tx_buf[6]=(calCRC>>8)&0xFF;
		RS485_tx_buf[7]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,8);
	}
	else//寄存器地址+数量超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}
//Modbus功能码16处理程序
//写多个保持寄存器
void Modbus_16_Handle(u8 * _data_buf)
{
	u8 i;
	u16 calCRC;
	u16 RegNum;
	u16 startRegAddr;

	startRegAddr=(((u16)_data_buf[2])<<8)|_data_buf[3];//获取寄存器起始地址
	RegNum= (((u16)_data_buf[4])<<8)|_data_buf[5];//获取寄存器数量
	if((startRegAddr+RegNum - 1)<MODBUS_REG_NUM)//寄存器地址+数量在范围内
	{
		for(i=0;i<RegNum;i++){
			*Modbus_HoldReg[startRegAddr+i]=((u16)_data_buf[7+i*2])<<8; //高字节在前
			*Modbus_HoldReg[startRegAddr+i]|=_data_buf[8+i*2]; //低字节在后
			if ((startRegAddr+i < MODBUS_SAVE_DATA_START + MODBUS_SAVE_DATA_NUM + 1) && (startRegAddr+i >= MODBUS_SAVE_DATA_START)){
				data_change_flag = 1;
			}
		}
		check_data ();
		if (data_change_flag == 1){
			save_para (1); //save_para(1) 保存参数save_para(0) 读取参数
		}

		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1];
		RS485_tx_buf[2]=_data_buf[2];
		RS485_tx_buf[3]=_data_buf[3];
		RS485_tx_buf[4]=_data_buf[4];
		RS485_tx_buf[5]=_data_buf[5];

		calCRC=CRC16(RS485_tx_buf,6);
		RS485_tx_buf[6]=(calCRC>>8)&0xFF;
		RS485_tx_buf[7]=calCRC&0xFF;
		RS485_SendData(RS485_tx_buf,8);

		data_change_flag = 1;
	}
	else//寄存器地址+数量超出范围
	{
		RS485_tx_buf[0]=_data_buf[0];
		RS485_tx_buf[1]=_data_buf[1]|0x80;
		RS485_tx_buf[2]=0x02; //异常码
		RS485_SendData(RS485_tx_buf,3);
	}
}

void HardFault_Handler (void)
{
	while (1);
}











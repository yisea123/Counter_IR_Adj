#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

#define MODBUS_RTU_USE_UART 3
#define MODBUS_RTU_ADDR 0x02
#define MODBUS_RTU_MIN_LEN 8

#define MODBUS_VIRTUAL_INPUT_NUM 8
#define MODBUS_INPUT_NUM 8
#define MODBUS_OUTPUT_NUM 20 + MODBUS_VIRTUAL_INPUT_NUM
#define MODBUS_REG_NUM (512+512)



#define USE_SAVE_DATA_EX
#ifdef USE_SAVE_DATA_EX
	#define MODBUS_SAVE_DATA_NUM_EX 26
	#define MODBUS_SAVE_DATA_SIZE_EX (MODBUS_SAVE_DATA_NUM_EX * 2)
	#define MODBUS_SAVE_DATA_START_EX 512
#endif

#define MODBUS_SAVE_DATA_NUM 30
#define MODBUS_SAVE_DATA_SIZE (MODBUS_SAVE_DATA_NUM * 2)
#define MODBUS_SAVE_DATA_START 30

#define RS485_TX_EN PGout(8)


extern U16 Modbus_HoldReg_CPU_Usage;



u16 CRC16(u8 *data_buf, u16 len);
void modbus_analyze(u8 * data_buf);
void modbus_init(void);
int save_para (int flag);
int load_para (void);
void check_data (void);
extern vu32 virtual_input[MODBUS_VIRTUAL_INPUT_NUM];

extern u8 RS485_tx_buf[256];//·¢ËÍ»º³åÇø


#endif

 

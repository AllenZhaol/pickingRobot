#ifndef _COM_DATA_H
#define	_COM_DATA_H
#include "stm32f10x.h"
#include "stdio.h"	
#include "sys.h" 
#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void uart3_init(u32 bound);
int process_data(char argV1[]);
int process_data2(char argV1[],char argV3[],char argV2[]);
void resetCommand();
void RunCommand();
int process_adc(void);
#endif
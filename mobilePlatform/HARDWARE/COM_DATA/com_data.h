#ifndef _COM_DATA_H
#define	_COM_DATA_H
#include "stm32f10x.h"
#include "stdio.h"	
#include "sys.h" 
#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart3_init(u32 bound);
int process_data(char argV1[]);
int process_data2(char argV1[],char argV3[],char argV2[]);
void resetCommand();
void RunCommand();
int process_adc(void);
#endif
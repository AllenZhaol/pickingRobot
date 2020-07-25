/***************************************************************
   This program is a graduation design - motion control
	 of a basketball robot's control system - by zhaolun
   *************************************************************/
#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "stm32f10x_tim.h"
#include "timer.h"
#include "gpio.h"
#include "motor_and_encoder.h"
#include "command.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "com_data.h"
#include "pid.h"
#include "string.h"
#include "move.h"
#include "adc.h"
#define AUTO_STOP_INTERVAL 1000

extern char cmd;  //Control sign
extern int stepmotorDis;
unsigned int led0pwmval,led0pwmva2,led0pwmva3,led0pwmva4;
int l,r;
long lastMotorCommand = 0;
extern s32 A_rcnt,B_rcnt,C_rcnt;
extern long arg1;
extern long arg2;
extern long arg3;

int kan;
int kan1;
uint64_t  current1;

 int main(void){
	 
 	u8 t=0;
	int dianji_num = 500;
	int x=0;
	int motorF = 0;
	int flag =1;
	int dir = 1;
	 int motorV;
	stepmotorDis=0;
	delay_init();	    	     //Delayed initialization
	NVIC_Configuration(); 	 //Interrupt initialization
	UserNVIC_Configuration();
	GPIO_Configuration();
	uart_init(9600);	       //Baud rate 9600
	uart3_init(9600);	     //Baud rate 57600
	UserTIM_Configuration(); 
	Adc_Init();							//adc initialization
	arg1=0;arg2=0;arg3=0;
	motorF = 0;
	while(1){
	
	process_adc();
	delay_ms(1000);delay_ms(1000);
	
	
	}
	while(1){	
//	if(KEY0==0)motorF+=1;while(KEY0==0);
//	if(motorF >1 )motorF=0;

	pickingbotForward(900,motorF);
	//if(motorF==0){motorInt1A_A = 0;motorInt1A_B = 1;}
	//if(motorF==1){motorInt1A_A = 1;motorInt1A_B = 0;}
//	TIM1->CCR1 = motorV; 
//	TIM1->CCR2 = motorV;
//	TIM1->CCR3 = motorV;
//	TIM1->CCR4 = motorV;
//	
//	TIM8->CCR1 = motorV; 
//	TIM8->CCR2 = motorV;
//	TIM8->CCR3 = motorV;
//	TIM8->CCR4 = motorV;
	
	}
		 
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   

			printf("\r\n您发送的消息为:\r\n\r\n");

			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}
	}	 
 	while(1){
	;
	
	}
	while(1){
		stepperMotorControl(5000,1);
		delay_ms(1000);
		stepperMotorControl(5000,0);
		delay_ms(1000);
	} 
	
  
		
}


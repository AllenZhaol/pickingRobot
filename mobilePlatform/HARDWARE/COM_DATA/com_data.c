#include "com_data.h"	
#include "sys.h"
#include "timer.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "command.h"
#include "motor_and_encoder.h"
#include "pid.h"
#include "move.h"
#include "adc.h"
#define BAUDRATE     57600
u8 cmd_data[20];
int tiaoshi=0;
int aa1;
int aa2;
int aa3;
extern unsigned char moving; 
char r_command;
// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int my_index = 0;
char com_flag='a';
// Variable to hold an input character
u8 Res;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[32];
char argv2[32];
char argv3[32];
int arg33[32];

// The arguments converted to integers
long arg1 = 0;
long arg2 = 0;
long arg3 = 0;

long arg11 = 0;
long arg21 = 0;
long arg31 = 0;
void uart3_init(u32 bound){
   
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);                    

}

u8 USART3_RX_BUF[USART3_REC_LEN];    

u16 USART3_RX_STA=0;      
void USART3_IRQHandler(){
	int d_distance=0;
  int d_angle=0;
	
	u8 t;
	u8 i=0;	
	u8 j=0;
	u8 len=0;	
	u8 data[8];
	tiaoshi=1;
	
  while(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
		Res = USART_ReceiveData(USART3);
		//printf("aaaaaa");
		if(Res == 0x0d){
			//printf("index:%d  ",my_index);
			my_index=0;
		  com_flag='a';
			process_data(argv1);
			RunCommand();
		  break;
		}

		if(com_flag=='b'){
			argv1[my_index]=Res;
			my_index++;
			//printf("index:%d",my_index);
			//printf("argv1%d",argv1[my_index]);
		}
	  if(Res == 0x55){com_flag='b';}
	}	

}

int process_data(char argV1[]){
	//处理数据
  int i,j;
	long numarg1,numarg2;
	uint16_t batteryVolt;
	arg1=0;arg2=0;arg3=0;
	cmd = argV1[0];
	numarg1 = (((int)(argV1[2])) << 8) | (argV1[1]);
	numarg2 = (((int)(argV1[4])) << 8) | (argV1[3]);
	arg11 = numarg1-2000;arg21 = numarg2-2000;
	//printf("cmd:%c-arg11:%d-arg21:%d",cmd,arg11,arg21);
	
}


int process_data2(char argV1[32],char argV2[32],char argV3[32]){
	
		arg1=0;arg2=0;arg3=0;
		arg1=strtol(argV1,NULL,10);
		arg2=strtol(argV2,NULL,10);
		arg3=strtol(argV3,NULL,10);
	
	  arg11=arg1;
	  arg21=arg2;
	  arg31=arg3;
}

int process_adc(void){
		
		int data_adc0,data_adc1,data_adc2,data_adc3;
		data_adc0=Get_Adc_Average(ADC_Channel_0,10);
		data_adc1=Get_Adc_Average(ADC_Channel_1,10);
		data_adc2=Get_Adc_Average(ADC_Channel_2,10);
		data_adc3=Get_Adc_Average(ADC_Channel_3,10);
		printf("%d ",data_adc0);
		printf("%d ",data_adc1);
		printf("%d ",data_adc2);
		printf("%d\r\n",data_adc3);
	

}

void resetCommand(void){
	   r_command=NULL;
     arg1=0;arg2=0;arg3=0;//Reset speed
     arg=0;my_index=0;
}


void RunCommand(){
	r_command=cmd;
	switch(r_command){
		case GET_BAUDRATE: //0x0d 获取通信波特率
				 printf("%d\n\r",BAUDRATE);
				 break;
		case ANALOG_READ://获取ADC
				 process_adc();
				 printf("ok");
				 break;
		case DIGITAL_READ:
				 printf("%d\n\r",BAUDRATE);
				 break;
		case MOTOR_SPEEDS:
				 tiaoshi=13;
				 //Transmission speed information 
				 if (arg1 == 0 && arg2 == 0&& arg3 == 0){
						 setMotorSpeeds(0, 0, 0);
						 //resetPID();
						 moving = 0;
					}
				 else moving = 1;
				 setTargetTicks(arg1,arg2,arg3);
				 printf("%ld:%ld",arg11,arg21);
				 pickingbotTest(arg11,arg21);

				 //pickingbotTest(arg11,arg21);
				 //pickingbotForward(arg11,0);	 
				 printf("ok\n\r");
				 break;
				
		case READ_ENCODERS://e
				 printf("%ld ",readEncoder('A'));
				 printf("%ld ",readEncoder('B'));
				 printf("%ld\n\r", readEncoder('C'));
				 break;
				 
		case RESET_ENCODERS://r
				 resetEncoders();
				 resetPID();
				 printf("ok\n\r");
				 break;
		
		case UPDATE_PID://'u'
				 setPID();
				 printf("ok\n\r");
				 break;

		case PIN_MODE://'c'
				 printf("ok\n\r");
				 if(arg11==1){
						pickingbotTest(1100,-1100);
						delay_ms(1000);delay_ms(1000);
						pickingbotTest(0,0); 
					}
				 if(arg11==2){
						pickingbotTest(-1100,1100);
						delay_ms(1000);delay_ms(1000);
						pickingbotTest(0,0); 
					}
				 break;	
		
		case STEPMOTOR_WRITE: //0x76
				//printf("servo write\n");
				//printf("%d",arg11);
				stepperMotorControl(arg11,0);
				break;
		case STEPMOTOR_READ: //0x77
				stepperMotorInit();
				break;
	}
	 
}






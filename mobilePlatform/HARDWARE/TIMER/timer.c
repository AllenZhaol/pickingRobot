#include "timer.h"
#include "gpio.h"
#include "usart.h"
uint64_t time_micros=0;

void TIM1_Configuration(u16 psc,u16 arr){
			/*TIM1--Motor interface settings*/
			//(PWM1/PWM2/PWM3/PWM4)--(PA6/AC7/PA8/PA9)
			GPIO_InitTypeDef GPIO_InitStructure; 
			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			TIM_OCInitTypeDef TIM_OCInitStructure;

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
			GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE); 

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9  | GPIO_Pin_11 | GPIO_Pin_13  | GPIO_Pin_14; 
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
			GPIO_Init(GPIOE, &GPIO_InitStructure);
	
			TIM_TimeBaseStructure.TIM_Period = psc;
			TIM_TimeBaseStructure.TIM_Prescaler = arr;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC2Init(TIM1, &TIM_OCInitStructure);
			TIM_OC3Init(TIM1, &TIM_OCInitStructure);
			TIM_OC4Init(TIM1, &TIM_OCInitStructure);

			TIM1->CCR1 = 0;  //PE7 
			TIM1->CCR2 = 0;  //PE9 
			TIM1->CCR3 = 0;  //PE11
			TIM1->CCR4 = 0;  //PE13

			TIM_Cmd(TIM1, ENABLE);
			TIM_CtrlPWMOutputs(TIM1, ENABLE);	
}

/*TIM8--Motor interface settings*/
void TIM8_Configuration(u16 psc,u16 arr)//(PWM1/PWM2/PWM3/PWM4)--(PC6/PC7/PC8/PC9)
{
			GPIO_InitTypeDef GPIO_InitStructure; 
			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			TIM_OCInitTypeDef TIM_OCInitStructure;

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;    
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       
			GPIO_Init(GPIOC, &GPIO_InitStructure); 

			TIM_TimeBaseStructure.TIM_Prescaler = arr;
			TIM_TimeBaseStructure.TIM_Period = psc;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
			TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

			TIM_OC1Init(TIM8, &TIM_OCInitStructure);
			TIM_OC2Init(TIM8, &TIM_OCInitStructure);
			TIM_OC3Init(TIM8, &TIM_OCInitStructure);
			TIM_OC4Init(TIM8, &TIM_OCInitStructure);

			TIM8->CCR1 = 0; //PC6
			TIM8->CCR2 = 0; //PC7
			TIM8->CCR3 = 0; //PC8
			TIM8->CCR4 = 0; //PC9

			TIM_Cmd(TIM8, ENABLE);
			TIM_CtrlPWMOutputs(TIM8, ENABLE);	

}

void TIM2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	
	TIM_TimeBaseStructure.TIM_Period = 9;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199; //
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //

	


	TIM_Cmd(TIM2, ENABLE);  //
}

void TIM3_Configuration(void){
			/*TIM3 encoder interface settings/PA6--A  PA7--B*/
			GPIO_InitTypeDef GPIO_InitStructure; 
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_ICInitTypeDef  TIM_ICInitStructure;

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
																																	
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
			GPIO_Init(GPIOA, &GPIO_InitStructure);				   
			GPIO_WriteBit(GPIOA, GPIO_Pin_6,Bit_SET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); 

			TIM_TimeBaseStructure.TIM_Period = Encoder_period; //
			TIM_TimeBaseStructure.TIM_Prescaler = 0; //
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

			
			TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 6;      
			TIM_ICInit(TIM3, &TIM_ICInitStructure);
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);     
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
			TIM3->CNT = 0;
			TIM_Cmd(TIM3, ENABLE);
}

void TIM4_Configuration(void){
			/*TIM4 encoder interface settings/PB6--A  PB7--B*/
			GPIO_InitTypeDef GPIO_InitStructure; 
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_ICInitTypeDef  TIM_ICInitStructure;

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  
																																
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
			GPIO_Init(GPIOB, &GPIO_InitStructure);				  
			GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
			GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET); 

			TIM_TimeBaseStructure.TIM_Period = Encoder_period; 	
			TIM_TimeBaseStructure.TIM_Prescaler = 0; 	
			TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

		
			TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
			TIM_ICStructInit(&TIM_ICInitStructure);	   
			TIM_ICInitStructure.TIM_ICFilter = 6;     
			TIM_ICInit(TIM4, &TIM_ICInitStructure);
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);     
			TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
			TIM4->CNT = 0;
			TIM_Cmd(TIM4, ENABLE);
}


void TIM5_Configuration(void){
			/*TIM5 encoder interface settings/PB0--A  PB1--B*/
			GPIO_InitTypeDef GPIO_InitStructure; 
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_ICInitTypeDef  TIM_ICInitStructure;

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
																																	
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);				 
			GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET); 

			TIM_TimeBaseStructure.TIM_Period = Encoder_period;
			TIM_TimeBaseStructure.TIM_Prescaler = 0;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
			TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 6;  
			TIM_ICInit(TIM5, &TIM_ICInitStructure);
			TIM_ClearFlag(TIM5, TIM_FLAG_Update); 
			TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);			TIM5->CNT = 0;

			TIM_Cmd(TIM5, ENABLE);
}

 /*Timer initialization*/
void UserTIM_Configuration(void){      
	   TIM1_Configuration(1999,0);
	   TIM2_Configuration();
	   TIM3_Configuration();
	   TIM4_Configuration();
	   TIM5_Configuration();
	   TIM8_Configuration(1999,0);
	  
}

void UserNVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure; 

	 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	 NVIC_Init(&NVIC_InitStructure); 
	
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

  
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 		 
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   //*******************************************************

   NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

}

void TIM2_IRQHandler(void)
{
	 
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  ); 
		time_micros++;
		}
}
uint64_t micros()
{
	uint64_t  current;
	current = time_micros;
	return current;
}


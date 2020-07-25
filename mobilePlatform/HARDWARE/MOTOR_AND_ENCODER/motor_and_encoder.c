/***************************************************************
   Motor and Encoder driver function definitions - by zhaolun
   *************************************************************/
	 
#include "motor_and_encoder.h"
#include "usart.h"
#include "gpio.h"

int stepmotorDis;
s32 A_rcnt=0,B_rcnt=0,C_rcnt=0;
int ASpeed1;
int BSpeed1;
int CSpeed1;

/*A convenience function for setting both motor speeds*/
void setMotorSpeeds(int ASpeed, int BSpeed, int CSpeed){
	 ASpeed1=ASpeed;
	 BSpeed1=BSpeed;
	 CSpeed1=CSpeed;
	 if(ASpeed<0){
	    TIM1->CCR1 = 0; 
	    TIM1->CCR4 = -ASpeed; 
	 }
	 else{
	    TIM1->CCR1 = ASpeed; 
	    TIM1->CCR4 = 0; 
	 }
	 if(BSpeed<0){
	    TIM8->CCR1 = 0; 
	    TIM8->CCR2 = -BSpeed; 
	 }
	 else{
	    TIM8->CCR1 = BSpeed; 
	    TIM8->CCR2 = 0; 
	 }
	 if(CSpeed<0){
	    TIM8->CCR3 = 0; 
	    TIM8->CCR4 = -CSpeed; 
	 }
	 else{
	    TIM8->CCR3 = CSpeed; 
	    TIM8->CCR4 = 0; 
	 }
	
 }
 
 /*TIM3 encoder count interrupt*/
/* Interrupt routine for A encoder, taking care of actual counting */
void TIM3_IRQHandler(void)
{
  if (TIM3 -> CR1 & 0X0010)		 
   {
    A_rcnt -= 1;
//		 A_rcnt=TIM3 -> CNT;
   }
   else A_rcnt += 1;

   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //Clear flag
}

/*TIM4 encoder count interrupt*/
/* Interrupt routine for B encoder, taking care of actual counting */
void TIM4_IRQHandler(void)
{
  if (TIM4 -> CR1 & 0X0010)	
   {
    B_rcnt -= 1;
   }
   else B_rcnt += 1;
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //Clear flag
}


/*TIM5 encoder count interrupt*/
/* Interrupt routine for C encoder, taking care of actual counting */
void TIM5_IRQHandler(void)
{
  if (TIM5 -> CR1 & 0X0010)		 
   {
    C_rcnt -= 1;
   }
   else C_rcnt += 1;
   TIM_ClearITPendingBit(TIM5, TIM_IT_Update);//Clear flag 
}


/* Wrap the encoder reset function */
void resetEncoders() {
  A_rcnt = 0;
  B_rcnt = 0;
  C_rcnt = 0;
	
}

/* Wrap the encoder reading function */
long readEncoder(char i){
  if (i == 'A'){
    return A_rcnt;
  }
  else if (i == 'B'){
    return B_rcnt;
  }
  else{
    return C_rcnt;
  }
}

int stepperMotorControl(long stepperMotorL,int stepperMotorC){
	int timex = 500;
	long numz;
	int x =0,y=0;
	if(stepperMotorL>1000)stepperMotorL=1000;
	if(stepperMotorL>=stepmotorDis){
		numz = stepperMotorL-stepmotorDis;
		stepperMotorC=1;
	}
	else {
		stepperMotorC=0;
		numz =stepmotorDis-stepperMotorL;
	}
	motorcon2=stepperMotorC;
	printf("numz:%d",numz);
	for(x=numz;x>0;x--)
		for(y=10;y>0;y--){
			motorcon1 = 1;
			delay_us(timex);
			motorcon1 = 0;
			delay_us(timex);
			if(x<1500&&timex<600)
				timex += 2;
	}
	stepmotorDis=stepperMotorL;
	printf("stepmotorDis:%d",stepmotorDis);
	return 1;
}
int stepperMotorInit(){
	int stepperMotorC;
	int timex = 500;
	long numz;
	int x =0,y=0;
	motorcon2=0;
	while(1){
		motorcon1 = 1;
		delay_us(timex);
		motorcon1 = 0;
		delay_us(timex);
		if(KEY0==0){
			delay_ms(50);
			if(KEY0==0){
				stepmotorDis=0;
				break;
			}
		}
	}
	return 1;
}



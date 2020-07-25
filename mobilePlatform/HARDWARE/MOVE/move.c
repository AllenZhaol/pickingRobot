#include "move.h"
#include "gpio.h"
#include "timer.h"
#include "stm32f10x_tim.h"
#include "delay.h"
int pickingbotForward(long motorV,int motorF){
		int motorM;

		TIM1->CCR1 = motorV-40;  //PE9 motor1-A
		if(motorF==0){motorInt1A_A = 0;motorInt1A_B = 1;}
		if(motorF==1){motorInt1A_A = 1;motorInt1A_B = 0;}
		if(motorF==2){motorInt1A_A = 1;motorInt1A_B = 1;}
		
		TIM1->CCR2 = motorV-30; 	//PE11 motor1-B
		if(motorF==0){motorInt1B_A = 0;motorInt1B_B = 1;}
		if(motorF==1){motorInt1B_A = 1;motorInt1B_B = 0;}
		if(motorF==2){motorInt1B_A = 1;motorInt1B_B = 1;}
		
		TIM1->CCR3 = motorV-80;  //PE13 motor2-A
		if(motorF==0){motorInt2A_A = 0;motorInt2A_B = 1;}
		if(motorF==1){motorInt2A_A = 1;motorInt2A_B = 0;}
		if(motorF==2){motorInt2A_A = 1;motorInt2A_B = 1;}
		
		TIM1->CCR4= motorV+50; 	//PE14 motor2-B
		if(motorF==0){motorInt2B_A = 0;motorInt2B_B = 1;}
		if(motorF==1){motorInt2B_A = 1;motorInt2B_B = 0;}
		if(motorF==2){motorInt2B_A = 1;motorInt2B_B = 1;}	
		
		TIM8->CCR1 = motorV-190;  //PC6 motor3-A
		if(motorF==0){motorInt3A_A = 0;motorInt3A_B = 1;}
		if(motorF==1){motorInt3A_A = 1;motorInt3A_B = 0;}
		if(motorF==2){motorInt3A_A = 1;motorInt3A_B = 1;}
		
		TIM8->CCR2= motorV-150; 	//PC7 motor3-B
		if(motorF==0){motorInt3B_A = 0;motorInt3B_B = 1;}
		if(motorF==1){motorInt3B_A = 1;motorInt3B_B = 0;}
		if(motorF==2){motorInt3B_A = 1;motorInt3B_B = 1;}
		
		TIM8->CCR3 = motorV-280;  //PC8 motor4-A
		if(motorF==0){motorInt4A_A = 0;motorInt4A_B = 1;}
		if(motorF==1){motorInt4A_A = 1;motorInt4A_B = 0;}
		if(motorF==2){motorInt4A_A = 1;motorInt4A_B = 1;}
		
		TIM8->CCR4= motorV-70; 	//PC9 motor4-B
		if(motorF==0){motorInt4B_A = 0;motorInt4B_B = 1;}
		if(motorF==1){motorInt4B_A = 1;motorInt4B_B = 0;}
		if(motorF==2){motorInt4B_A = 1;motorInt4B_B = 1;}
		
		return 1;
	
}
int pickingbotTest(long motorV1,long motorV2){
		int motorF = 1;
		long numm1,numm2;
		
		if(motorV1==0){motorV1=0;motorV2=0;}
		numm1=motorV1;numm2=motorV2;
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt1A_A = 0;motorInt1A_B = 1;}
		if(motorF==1){motorInt1A_A = 1;motorInt1A_B = 0;}
		if(motorF==2){motorInt1A_A = 1;motorInt1A_B = 1;}
		TIM8->CCR1 = numm1+50;//PC6 motor1-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt1B_A = 0;motorInt1B_B = 1;}
		if(motorF==1){motorInt1B_A = 1;motorInt1B_B = 0;}
		if(motorF==2){motorInt1B_A = 1;motorInt1B_B = 1;}
		TIM8->CCR2 = numm2; 	//PC7 motor1-B
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt2A_A = 0;motorInt2A_B = 1;}
		if(motorF==1){motorInt2A_A = 1;motorInt2A_B = 0;}
		if(motorF==2){motorInt2A_A = 1;motorInt2A_B = 1;}
		TIM8->CCR3 = numm1;  //PC8 motor2-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt2B_A = 0;motorInt2B_B = 1;}
		if(motorF==1){motorInt2B_A = 1;motorInt2B_B = 0;}
		if(motorF==2){motorInt2B_A = 1;motorInt2B_B = 1;}	
		TIM8->CCR4= numm2; 	//PC9 motor2-B
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt3A_A = 0;motorInt3A_B = 1;}
		if(motorF==1){motorInt3A_A = 1;motorInt3A_B = 0;}
		if(motorF==2){motorInt3A_A = 1;motorInt3A_B = 1;}
		TIM1->CCR1 = numm1;  //PA8 motor3-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt3B_A = 0;motorInt3B_B = 1;}
		if(motorF==1){motorInt3B_A = 1;motorInt3B_B = 0;}
		if(motorF==2){motorInt3B_A = 1;motorInt3B_B = 1;}	
		TIM1->CCR4= numm2; 	//PA11 motor3-B
		
		return 1;
}



int pickingbotTest1(long motorV1,long motorV2){

		int motorF = 1;
		long numm1,numm2;
		if(motorV1==0){motorV1=0;motorV2=0;}
		numm1=motorV1;
		numm2=motorV2;
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt1A_A = 0;motorInt1A_B = 1;}
		if(motorF==1){motorInt1A_A = 1;motorInt1A_B = 0;}
		if(motorF==2){motorInt1A_A = 1;motorInt1A_B = 1;}
		TIM8->CCR1 = numm1+50; //PC6 motor1-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt1B_A = 0;motorInt1B_B = 1;}
		if(motorF==1){motorInt1B_A = 1;motorInt1B_B = 0;}
		if(motorF==2){motorInt1B_A = 1;motorInt1B_B = 1;}
		TIM8->CCR2 = numm2; 	//PC7 motor1-B
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt2A_A = 0;motorInt2A_B = 1;}
		if(motorF==1){motorInt2A_A = 1;motorInt2A_B = 0;}
		if(motorF==2){motorInt2A_A = 1;motorInt2A_B = 1;}
		TIM8->CCR3 = numm1;   //PC8 motor2-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt2B_A = 0;motorInt2B_B = 1;}
		if(motorF==1){motorInt2B_A = 1;motorInt2B_B = 0;}
		if(motorF==2){motorInt2B_A = 1;motorInt2B_B = 1;}	
		TIM8->CCR4= numm2; 	 //PC9 motor2-B
		
		if(motorV1<0){motorF=0;numm1=-motorV1;}else motorF=1;
		if(motorF==0){motorInt3A_A = 0;motorInt3A_B = 1;}
		if(motorF==1){motorInt3A_A = 1;motorInt3A_B = 0;}
		if(motorF==2){motorInt3A_A = 1;motorInt3A_B = 1;}
		TIM1->CCR1 = numm1;  //PA8 motor3-A
		
		if(motorV2<0){motorF=0;numm2=-motorV2;}else motorF=1;
		if(motorF==0){motorInt3B_A = 0;motorInt3B_B = 1;}
		if(motorF==1){motorInt3B_A = 1;motorInt3B_B = 0;}
		if(motorF==2){motorInt3B_A = 1;motorInt3B_B = 1;}	
		TIM1->CCR4= numm2; 	//PA11 motor3-B
		
		return 1;

}



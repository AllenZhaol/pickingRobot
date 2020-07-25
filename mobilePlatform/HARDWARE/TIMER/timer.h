#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"

#define PWMPeriod   1000   //PWM period
#define Encoder_period  10 //Encoder sampling period
#define MotorOneForward  0 //
#define MotorTwoForward  0  
#define MotorOneBack     1
#define MotorTwoBack     1
#define MotorSpdZero     0

extern void UserTIM_Configuration(void);
extern void UserNVIC_Configuration(void);

uint64_t micros();

#endif

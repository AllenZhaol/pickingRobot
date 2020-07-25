#ifndef __MOTOR_AND_ENCODER_H
#define __MOTOR_AND_ENCODER_H
#include "delay.h"
#include "timer.h"

//////////////////////////Motor driver function //////////////////////////////
void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int ASpeed, int BSpeed, int CSpeed);
int stepperMotorControl(long stepperMotorL,int stepperMotorC);

//////////////////////////Encoder driver function ////////////////////////////////////
long readEncoder(char i);
void resetEncoder(int i);
void resetEncoders();
void initEncoders();
int stepperMotorInit();

#endif
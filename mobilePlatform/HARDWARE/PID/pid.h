#ifndef __PID_H
#define __PID_H
/* PID setpoint info For a Motor */
typedef struct {
  double TargetTicksPerFrame;    // target speed in ticks per frame
  long Encoder;                  // encoder count
  long PrevEnc;                  // last encoder count
  int PrevInput;                // last input
  int ITerm;                    //integrated term
  long output;                  //last motor setting
}
SetPointInfo;
void resetPID(void);
void setPID(void);
void setTargetTicks(long A_arg,long B_arg,long C_arg);
void doAWheelPID(SetPointInfo *p,long max);
void doBWheelPID(SetPointInfo *p,long max);
void doCWheelPID(SetPointInfo *p,long max);
void updatePID();
long readPidIn(char wheel);
long readPidOut(char wheel);
#endif
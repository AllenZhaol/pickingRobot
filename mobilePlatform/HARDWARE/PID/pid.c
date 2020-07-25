#include "pid.h"
#include "math.h"
#include "motor_and_encoder.h"
SetPointInfo AWheelPID, BWheelPID, CWheelPID;
int sa,sb,sc;
extern long arg11;
extern long arg21;
extern long arg31;

/*default PID Parameters*/
int AWheel_Kp = 5;
int AWheel_Kd = 15;
int AWheel_Ki = 0;
int AWheel_Ko = 50;

int BWheel_Kp = 5;
int BWheel_Kd = 15;
int BWheel_Ki = 0;
int BWheel_Ko = 50;

int CWheel_Kp = 5;
int CWheel_Kd = 15;
int CWheel_Ki = 0;
int CWheel_Ko = 50;

unsigned char moving = 0; // is the base in motion?

void resetPID(){
			AWheelPID.TargetTicksPerFrame = 0.0;
			AWheelPID.Encoder = readEncoder('A');
			AWheelPID.PrevEnc = AWheelPID.Encoder;
			AWheelPID.output    = 0;
			AWheelPID.PrevInput = 0;
			AWheelPID.ITerm     = 0;

			BWheelPID.TargetTicksPerFrame = 0.0;
			BWheelPID.Encoder = readEncoder('B');
			BWheelPID.PrevEnc = BWheelPID.Encoder;
			BWheelPID.output    = 0;
			BWheelPID.PrevInput = 0;
			BWheelPID.ITerm     = 0;

			CWheelPID.TargetTicksPerFrame = 0.0;
			CWheelPID.Encoder = readEncoder('C');
			CWheelPID.PrevEnc = CWheelPID.Encoder;
			CWheelPID.output    = 0;
			CWheelPID.PrevInput = 0;
			CWheelPID.ITerm     = 0;
	    moving = 0;
}



void setPID(void){

//	AWheel_Kp=
//	AWheel_Kd=
//	AWheel_Ki=
//	AWheel_Ko=
}

void setTargetTicks(long A_arg,long B_arg,long C_arg){
	
	    sa=A_arg;sb=B_arg;sc=C_arg;

			AWheelPID.TargetTicksPerFrame = A_arg;
			BWheelPID.TargetTicksPerFrame = B_arg;
			CWheelPID.TargetTicksPerFrame = C_arg;
	    
}


void doAWheelPID(SetPointInfo *p,long max){
			/* PID routine to compute the next A motor commands */
			long Perror = 0;
			long output = 0;
			int input   = 0;
	
      if(max>PWMPeriod)max=PWMPeriod;
			p->Encoder = readEncoder('A');
			input  = p->Encoder - p->PrevEnc;
			Perror = p->TargetTicksPerFrame - input;
			output = (AWheel_Kp * Perror - AWheel_Kd * (input - p->PrevInput) + p->ITerm) / AWheel_Ko;
			p->PrevEnc = p->Encoder;  //save current encoder value to preEncoder
			output += p->output;
			
			if (output >= max){
			    output = max;
			    }
			else if (output <= -max){
			    output = -max;
			    }
			else{
			    p->ITerm += AWheel_Ki * Perror;
			    }

			p->output    = output;  //save current pid output for next pid
			p->PrevInput = input;
}


void doBWheelPID(SetPointInfo *p,long max){
			/* PID routine to compute the next motor commands */
			long Perror = 0;
			long output = 0;
			int input   = 0;
	
      if(max>PWMPeriod)max=PWMPeriod;
			p->Encoder = readEncoder('B');
			input  = p->Encoder - p->PrevEnc;
			Perror = p->TargetTicksPerFrame - input;
			output = (BWheel_Kp * Perror - BWheel_Kd * (input - p->PrevInput) + p->ITerm) / BWheel_Ko;
			p->PrevEnc = p->Encoder;
			output += p->output;

			if (output >= max){
			    output = max;
			    }
			else if (output <= -max){
			    output = -max;
			    }
			else{
			    p->ITerm += BWheel_Ki * Perror;
			    }

			p->output = output;
			p->PrevInput = input;
}


void doCWheelPID(SetPointInfo *p,long max){
			/* PID routine to compute the next motor commands */
			long Perror = 0;
			long output = 0;
			int input   = 0;
	
      if(max>PWMPeriod)max=PWMPeriod;
			p->Encoder = readEncoder('C');
			input  = p->Encoder - p->PrevEnc;
			Perror = p->TargetTicksPerFrame - input;
			output = (CWheel_Kp * Perror - CWheel_Kd * (input - p->PrevInput) + p->ITerm) / CWheel_Ko;
			p->PrevEnc = p->Encoder;
			output += p->output;

			if (output >= max){
			    output = max;
			    }
			else if (output <= -max){
			    output = -max;
			    }
			else{
			    p->ITerm += CWheel_Ki * Perror;
			    }

			p->output    = output;
			p->PrevInput = input;
}


void updatePID(){
			/* Read the encoder values and call the PID routine */
	    long maxA;
	    long maxB;
		  long maxC;
			
			if (!moving){
      if (AWheelPID.PrevInput != 0 || BWheelPID.PrevInput != 0 || CWheelPID.PrevInput != 0){
			    resetPID();
			    }
			 return;
			 }
       maxA=labs(arg11);
			 maxB=labs(arg21);
			 maxC=labs(arg31);
			/* Compute PID update for each motor */
			doAWheelPID(&AWheelPID,maxA);
			doBWheelPID(&BWheelPID,maxB);
			doCWheelPID(&CWheelPID,maxC);

			/* Set the motor speeds accordingly */
			setMotorSpeeds(AWheelPID.output, BWheelPID.output, CWheelPID.output);
}

long readPidIn(char wheel){
			long pidin = 0;
			if (wheel == 'A'){
			    pidin = AWheelPID.PrevInput;
			    }
			else if (wheel == 'B'){
			    pidin = BWheelPID.PrevInput;
			    }
			else{
			    pidin = CWheelPID.PrevInput;
			    }

			return pidin;
}

long readPidOut(char wheel){
			long pidout = 0;
			if (wheel == 'A'){
			    pidout = AWheelPID.output;
			    }
			else if (wheel == 'B'){
			    pidout = BWheelPID.output;
			    }
			else{
			    pidout = CWheelPID.output;
			    }

			return pidout;
}


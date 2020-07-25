#ifndef __GPIO_H
#define __GPIO_H	 
#include "sys.h"


#define motorcon1 PDout(14)   // PB4
#define motorcon2 PDout (15)   // PB5	
#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)   
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)   

#define motorInt1A_A PGout(0)   // PG0
#define motorInt1A_B PGout(1)   // PG1
#define motorInt1B_A PGout(2)   // PG2
#define motorInt1B_B PGout(3)   // PG3

#define motorInt2A_A PGout(4)   // PG4
#define motorInt2A_B PGout(5)   // PG5
#define motorInt2B_A PGout(7)   // PG6
#define motorInt2B_B PGout(6)   // PG7

#define motorInt3A_A PGout(8)   // PG4
#define motorInt3A_B PGout(9)   // PG5
#define motorInt3B_A PGout(10)   // PG6
#define motorInt3B_B PGout(11)   // PG7

#define motorInt4A_A PGout(12)   // PG4
#define motorInt4A_B PGout(13)   // PG5
#define motorInt4B_A PGout(14)   // PG6
#define motorInt4B_B PGout(15)   // PG7

void motorConfiguration(void);
void KEY_Configuration(void);
void LED_Configuration(void); 
void GPIO_Configuration(void);
#endif
#include "gpio.h"

//void GPIO_Configuration(void)										 
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG |  RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIOG外设模块时钟使能

//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;              
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //最大速率50Mhz
//	GPIO_Init(GPIOG, &GPIO_InitStructure);			  //初始化端口G
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;              
//  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;		     //上拉输入
//	
//  GPIO_Init(GPIOE, &GPIO_InitStructure);			  //初始化端口E
//  
//}


void KEY_Configuration(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;              
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;		     //上拉输入
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);			  //初始化端口E
	
}	

void LED_Configuration(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);          
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 |GPIO_Pin_15 ;        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOB,GPIO_Pin_14);    //B3    
	GPIO_SetBits(GPIOB,GPIO_Pin_15);    //B5
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//	GPIO_Init(GPIOE, &GPIO_InitStructure);  
//	GPIO_SetBits(GPIOE,GPIO_Pin_5);     //E5    
//	
}	

                                                                                                                                                                              

void motorConfiguration(void){
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);  //使能GPIOG外设模块时钟使能

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
																 GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
																 GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;              
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		   //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //最大速率50Mhz
	GPIO_Init(GPIOG, &GPIO_InitStructure);			  //初始化端口G



}


void GPIO_Configuration(void){
	LED_Configuration();
	KEY_Configuration();
	motorConfiguration();
}		
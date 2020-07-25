/* 
Define single-letter commands that will be sent by the PC over the serial link.
																																	--by zhaolun
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define ANALOG_READ    0x61//模拟读取'a'
#define GET_BAUDRATE   0x62//获取波特率'b'
#define PIN_MODE       0x63//PIN模式'c'
#define DIGITAL_READ   0x64//数字读取'd'
#define READ_ENCODERS  0x65//'e'获取编码器累积量
#define MOTOR_SPEEDS   0x6d //'m'电机速度
#define PING           0x70//'p'
#define RESET_ENCODERS 0x72//'r'重置编码器累积量
#define SERVO_WRITE    0x73//'s'伺服写入 舵机
#define SERVO_READ     0x74//'t'伺服读取 舵机
#define UPDATE_PID     0x75//更新pid'u'
#define STEPMOTOR_WRITE 0x76//'V' 步进电机写入，控制步进电机的运动
#define STEPMOTOR_READ 0x77//'W'步进电机读取，读取步进电机当前的位置

#define A_WHEEL         1
#define B_WHEEL         2
#define C_WHEEL         3

#define FORWARDS        true
#define BACKWARDS       false


#endif
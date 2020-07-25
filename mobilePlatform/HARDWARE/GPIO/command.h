/* 
Define single-letter commands that will be sent by the PC over the serial link.
																																	--by zhaolun
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define ANALOG_READ    0x61//ģ���ȡ'a'
#define GET_BAUDRATE   0x62//��ȡ������'b'
#define PIN_MODE       0x63//PINģʽ'c'
#define DIGITAL_READ   0x64//���ֶ�ȡ'd'
#define READ_ENCODERS  0x65//'e'��ȡ�������ۻ���
#define MOTOR_SPEEDS   0x6d //'m'����ٶ�
#define PING           0x70//'p'
#define RESET_ENCODERS 0x72//'r'���ñ������ۻ���
#define SERVO_WRITE    0x73//'s'�ŷ�д�� ���
#define SERVO_READ     0x74//'t'�ŷ���ȡ ���
#define UPDATE_PID     0x75//����pid'u'
#define STEPMOTOR_WRITE 0x76//'V' �������д�룬���Ʋ���������˶�
#define STEPMOTOR_READ 0x77//'W'���������ȡ����ȡ���������ǰ��λ��

#define A_WHEEL         1
#define B_WHEEL         2
#define C_WHEEL         3

#define FORWARDS        true
#define BACKWARDS       false


#endif
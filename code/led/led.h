#ifndef __LED_H
#define __LED_H

#include "main.h"


//P0_4��ͷ�ļ�ioCC2530.h����
#define LED             P0_4

//����LED�Ŀ���״̬�Ͷ�Ӧ��ֵ
#define LED_ON          1 
#define LED_OFF         0 

void initLed();

#endif
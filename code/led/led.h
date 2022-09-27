#ifndef __LED_H
#define __LED_H

#include "main.h"


//P0_4由头文件ioCC2530.h定义
#define LED             P0_4

//定义LED的开关状态和对应的值
#define LED_ON          1 
#define LED_OFF         0 

void initLed();

#endif
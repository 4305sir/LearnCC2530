#ifndef __KEY_H
#define __KEY_H

#include "main.h"

/**
 *  @brief  按钮及其状态的定义。其中，P0_1是在头文件ioCC2530.h，可以检测其值来判断P0_1引脚的电平状态
 */
#define BUTTON  P0_1

#define BUTTON_NORMAL   1//按钮的默认状态
#define BUTTON_DOWN     0//按钮被按下


void initButton();
void initButton_exit(void);

#endif
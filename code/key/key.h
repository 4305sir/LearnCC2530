#ifndef __KEY_H
#define __KEY_H

#include "main.h"

/**
 *  @brief  ��ť����״̬�Ķ��塣���У�P0_1����ͷ�ļ�ioCC2530.h�����Լ����ֵ���ж�P0_1���ŵĵ�ƽ״̬
 */
#define BUTTON  P0_1

#define BUTTON_NORMAL   1//��ť��Ĭ��״̬
#define BUTTON_DOWN     0//��ť������


void initButton();
void initButton_exit(void);

#endif
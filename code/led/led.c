#include "led.h"


/**
 * @fn      initLed
 * 
 * @brief	��ʼ��LED�����P0_4��ؼĴ���������
 */
void initLed()
{
    P0SEL &= ~(1<<4);
    P0DIR |=  (1<<4);
}
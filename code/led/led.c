#include "led.h"


/**
 * @fn      initLed
 * 
 * @brief	初始化LED，完成P0_4相关寄存器的配置
 */
void initLed()
{
    P0SEL &= ~(1<<4);
    P0DIR |=  (1<<4);
}
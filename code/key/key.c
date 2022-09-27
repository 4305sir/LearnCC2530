#include "key.h"


/*
 * @fn      initButton
 * 
 * @brief	初始化Button，完成P0_1相关寄存器的配置
 */
void initButton()
{
    P0SEL &= ~(1<<1);//把P0SEL寄存器的第1位设置为0，即让P0_1用作通用IO口 
    P0DIR &= ~(1<<1);//把P0DIR寄存器的第1位设置为0，即让让P0_1处于输入信号模式
    P0INP &= ~(1<<1);//把P0INP寄存器的第1位设置为0，即让P0_1处于上拉/下拉输入模式
    P2INP &= ~(1<<5);//把P2INP寄存器的第5位设置为0，即让端口0处于上拉输入模式

}

void initButton_exit(void)  
{  
    PICTL |= 0x01;//P0ICON=1，指定端口0在输入下降沿信号时触发中断，即输入电平由高电平转为低电平时触发中断
    P0IFG = 0x00;//清零P0IFG寄存器
    P0IEN |= (1<<1);// 把P0\_1设置为允许引发中断
    P0IF = 0x00;//清零P0IF寄存器
    EA = 1;//允许所有中断
    IEN1 |= 0x20;//P0IE=1，允许端口0引起中断
}

#pragma vector = P0INT_VECTOR
__interrupt void buttonISR(void)
{   
    delayMs_circle(10); //处理机械按键抖动

    if (BUTTON == BUTTON_DOWN) {
        LED = (LED == LED_ON)? LED_OFF : LED_ON;//翻转LED灯的状态
    }  
    //处理完中断后，需要清零相关寄存器
    P0IFG = 0;
    P0IF  = 0;
}
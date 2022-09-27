#include "timer.h"


void InitTimer1()
{
  T1CTL = 0x0D; // 0000 1101：128分频，自由计数(从0~65535)                     CC2530的默认系统时钟频率是16MHz（16000000Hz）
  T1STAT= 0x21; // bit0写1，清空通道0中断状态位  
                 // bit5写1，清空计数器中断状态位
}
 

void InitTimer3()
{
  T3CTL = 0xE8;   // Bit[7:5]  :   111 -> 128分频；  
                  // Bit3     ： 1 -> 打开溢出中断  
                  // Bit[1:0]  ：  00 -> 自由计数，反复从0到255  
  T3IE = 1;       // 使能定时器3中断  
  EA  = 1;        // 开启中断总开关  
  T3CTL |= 0x10;  // 启动定时器
}

/*
 *  Timer3 interrupt service function 
 */
#pragma vector = T3_VECTOR
__interrupt void Timer3_ISR(void)
{
    static int counter_g = 0;
    // ~5s
    if (++counter_g == 2441) {
        counter_g = 0;
        LED = !LED;
    }
}

void initWatchDogTimer()
{
    WDCTL = 0x00;  // 打开 IDLE模式才能设置看门狗  
    WDCTL = 0x08;  // 看门狗模式、定时1秒
}
void watchDogFeet()
{
  WDCTL |= (0xA << 4);  // 在Bit[7:4]依次写入0xA和0x5，定时器被清除  
  WDCTL |= (0x5 << 4);
}

void InitsleepTimer()
{
  ST2 = 0;  ST1 = 0;  ST0 = 0;  // 清零休眠定时器计数器  
  STIE = 1;  // 开启休眠定时器中断  
  STIF = 0;  // 清零休眠定时器中断标志  
  EA  = 1;   // 打开中断总开关
}

void setSleepPeriod(uint8_t nS)
{
    uint32_t sleepTimer = 0;
    sleepTimer  = (uint32_t)ST0;
    sleepTimer |= (uint32_t)ST1 << 8;
    sleepTimer |= (uint32_t)ST2 << 16;
    
    sleepTimer += (uint32_t)nS * 32768;
    
    ST2 = (uint8_t)(sleepTimer >> 16);
    ST1 = (uint8_t)(sleepTimer >> 8);
    ST0 = (uint8_t)(sleepTimer);
}

void setPowerMode(PowerMode_t mode)
{
    if (mode > _POWER_MODE_MAX) {
        DEBUG_LOG("Power mode not found: %d\r\n", (int)mode);
        return;
    }
    
    if (mode == POWER_MODE_ACTIVE) {
        PCON = 0x00;
        return;       // Don't sleep
    }
    
    SLEEPCMD |= mode; // Set power mode      
    PCON = 0x01;      // Entering sleep mode
}

/*
 *  Sleep timer ISR
 */
#pragma vector = ST_VECTOR
__interrupt void SleepTimer_ISR(void)
{
    STIF = 0;                        // Clear interrupt flag
    setPowerMode(POWER_MODE_ACTIVE); // Entry active power mode

    DEBUG_LOG("Activing...\r\n");
}
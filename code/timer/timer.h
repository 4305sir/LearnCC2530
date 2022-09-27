#ifndef __TIMER_H_
#define __TIMER_H_

#include "main.h"

#define isTimer1Flow (IRCON & 0x02)    //一般用于查询中断
#define ClearTimer1_interruptFlag (IRCON &= ~(0x02))

/*
 *  Power modes: Active mode, PM1, PM2, PM3
 */
typedef enum
{
    POWER_MODE_IDLE   = 0,
    POWER_MODE_PM1    = 1,
    POWER_MODE_PM2    = 2,
    POWER_MODE_PM3    = 3,
    POWER_MODE_ACTIVE = 4,
    
    _POWER_MODE_MAX = POWER_MODE_ACTIVE
}PowerMode_t;


void InitTimer1();
void InitTimer3();
void initWatchDogTimer();
void watchDogFeet();
void InitsleepTimer();
void setSleepPeriod(uint8_t nS);
void setPowerMode(PowerMode_t mode);

#endif
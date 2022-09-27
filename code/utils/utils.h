#ifndef __UTILS_H
#define __UTILS_H

#include "main.h"

#define DEBUG
//#define xDEBUG

#ifdef  DEBUG
  #define DEBUG_LOG(...) printf(__VA_ARGS__)
#else
  #define DEBUG_LOG(...)
#endif

/** @brief    设置系统时钟为32MHz
 */
#define setSystemClk32MHZ() do { \
    CLKCONCMD &= ~0x40;        \
    while(CLKCONSTA & 0x40);   \
    CLKCONCMD &= ~0x47;        \
} while(0)

void delayMs_circle(uint16_t nMs);
typedef enum { SYSCLK_16MHZ, SYSCLK_32MHZ } halDelaySysClk_t;

void delayUsIn32Mhz(uint16_t nUs);
void delayMs(halDelaySysClk_t sysClk, uint16_t nMs);

#endif
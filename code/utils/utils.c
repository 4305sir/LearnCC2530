#include "utils.h"



/**
 * @fn      delayMs_circle
 * 
 * @brief	让程序延后指定的时间才接着运行
 *
 * @param 	nMs - 时间长度，以毫秒为单位，值范围：165535
 *
 * @return 	none

 */
void delayMs_circle(uint16_t nMs)
{
    uint16_t i,j;
  
    for (i = 0; i < nMs; i++)
        //经由实际测试可以得出执行535次循环耗时最接近1ms
        for (j = 0; j < 535; j++);
}

#pragma optimize=none
void delayUsIn32Mhz(uint16_t nUs)
{
    for(uint16_t i = 0; i < nUs; i++)
    {
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
    }
}

#pragma optimize=none
void delayMs(halDelaySysClk_t sysClk, uint16_t nMs)
{
  uint16_t i, j;
  uint16_t loop1Ms;
  
  if (sysClk == SYSCLK_16MHZ) loop1Ms = 535;
  else loop1Ms = 1070;

  for(i = 0; i < nMs; i++) for(j = 0; j < loop1Ms; j++);
}
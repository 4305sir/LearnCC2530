#include "utils.h"



/**
 * @fn      delayMs_circle
 * 
 * @brief	�ó����Ӻ�ָ����ʱ��Ž�������
 *
 * @param 	nMs - ʱ�䳤�ȣ��Ժ���Ϊ��λ��ֵ��Χ��165535
 *
 * @return 	none

 */
void delayMs_circle(uint16_t nMs)
{
    uint16_t i,j;
  
    for (i = 0; i < nMs; i++)
        //����ʵ�ʲ��Կ��Եó�ִ��535��ѭ����ʱ��ӽ�1ms
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
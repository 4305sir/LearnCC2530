#include "timer.h"


void InitTimer1()
{
  T1CTL = 0x0D; // 0000 1101��128��Ƶ�����ɼ���(��0~65535)                     CC2530��Ĭ��ϵͳʱ��Ƶ����16MHz��16000000Hz��
  T1STAT= 0x21; // bit0д1�����ͨ��0�ж�״̬λ  
                 // bit5д1����ռ������ж�״̬λ
}
 

void InitTimer3()
{
  T3CTL = 0xE8;   // Bit[7:5]  :   111 -> 128��Ƶ��  
                  // Bit3     �� 1 -> ������ж�  
                  // Bit[1:0]  ��  00 -> ���ɼ�����������0��255  
  T3IE = 1;       // ʹ�ܶ�ʱ��3�ж�  
  EA  = 1;        // �����ж��ܿ���  
  T3CTL |= 0x10;  // ������ʱ��
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
    WDCTL = 0x00;  // �� IDLEģʽ�������ÿ��Ź�  
    WDCTL = 0x08;  // ���Ź�ģʽ����ʱ1��
}
void watchDogFeet()
{
  WDCTL |= (0xA << 4);  // ��Bit[7:4]����д��0xA��0x5����ʱ�������  
  WDCTL |= (0x5 << 4);
}

void InitsleepTimer()
{
  ST2 = 0;  ST1 = 0;  ST0 = 0;  // �������߶�ʱ��������  
  STIE = 1;  // �������߶�ʱ���ж�  
  STIF = 0;  // �������߶�ʱ���жϱ�־  
  EA  = 1;   // ���ж��ܿ���
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
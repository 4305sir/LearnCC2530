#include "key.h"


/*
 * @fn      initButton
 * 
 * @brief	��ʼ��Button�����P0_1��ؼĴ���������
 */
void initButton()
{
    P0SEL &= ~(1<<1);//��P0SEL�Ĵ����ĵ�1λ����Ϊ0������P0_1����ͨ��IO�� 
    P0DIR &= ~(1<<1);//��P0DIR�Ĵ����ĵ�1λ����Ϊ0��������P0_1���������ź�ģʽ
    P0INP &= ~(1<<1);//��P0INP�Ĵ����ĵ�1λ����Ϊ0������P0_1��������/��������ģʽ
    P2INP &= ~(1<<5);//��P2INP�Ĵ����ĵ�5λ����Ϊ0�����ö˿�0������������ģʽ

}

void initButton_exit(void)  
{  
    PICTL |= 0x01;//P0ICON=1��ָ���˿�0�������½����ź�ʱ�����жϣ��������ƽ�ɸߵ�ƽתΪ�͵�ƽʱ�����ж�
    P0IFG = 0x00;//����P0IFG�Ĵ���
    P0IEN |= (1<<1);// ��P0\_1����Ϊ���������ж�
    P0IF = 0x00;//����P0IF�Ĵ���
    EA = 1;//���������ж�
    IEN1 |= 0x20;//P0IE=1������˿�0�����ж�
}

#pragma vector = P0INT_VECTOR
__interrupt void buttonISR(void)
{   
    delayMs_circle(10); //�����е��������

    if (BUTTON == BUTTON_DOWN) {
        LED = (LED == LED_ON)? LED_OFF : LED_ON;//��תLED�Ƶ�״̬
    }  
    //�������жϺ���Ҫ������ؼĴ���
    P0IFG = 0;
    P0IF  = 0;
}
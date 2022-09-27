#include "main.h"



void main(void)
{
    setSystemClk32MHZ();
    halOLED12864Init();
    while(1)
    {
        /* Test1 - ��ʾ 8��16 ���ַ� */
        halOLED12864ShowX16(0, 0, "0123456789");//�ڵ�1����ʾ
        halOLED12864ShowX16(1, 0, "abcdefghiABCDE");//�ڵ�2����ʾ
        halOLED12864ShowX16(2, 0, "{}[]()!@#$%");//�ڵ�3����ʾ
        halOLED12864ShowX16(3, 0, "==========>");//�ڵ�3����ʾ

        delayMs(SYSCLK_32MHZ, 4000);//�ӳ�
        halOLED12864ClearScreen();//���
    
        /* Test2 - ��ʾ 8��16 �ַ� �� 16��16 ���� */
        halOLED12864ShowX16(0, 0,  "�������£�");
        halOLED12864ShowX16(1, 30, "�¶ȣ�22 ��");
        halOLED12864ShowX16(2, 30, "ʪ�ȣ�30 %");
        /* ע�⣺���ں��֣�������ȡ��ģ���ŵ������ֿ��ļ�font_chinese_v_16x16.h��*/
        
        delayMs(SYSCLK_32MHZ, 4000);//�ӳ�
        halOLED12864ClearScreen();//���

        /* Test3 - �����꣨30����, 30���أ�����ʾ�ֱ���Ϊ 32x32 ���ص�ͼƬ*/
        halOLED12864ShowPicture(30, 30, 32, 32, Picture_32x32_AppleIco);
        /*ע�⣺����ͼƬ��ϵ��Ҫ��ȡģ������ͼ���ļ�font_v_picture.h��*/
        
        delayMs(SYSCLK_32MHZ, 4000);//�ӳ�
        halOLED12864ClearScreen();//���

         /* Test4 - ȫ����ʾ 128x64 ͼƬ���������꣨30����, 30���أ�����ʾһ�ŷֱ���Ϊ128x64���ص�ͼƬ */
        halOLED12864ShowPicture(0, 0, 128, 64, Picture_128x128_SuccessPic);

        delayMs(SYSCLK_32MHZ, 4000);//�ӳ�
        halOLED12864ClearScreen();//��
    }
}
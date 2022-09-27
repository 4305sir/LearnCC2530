#include "main.h"



void main(void)
{
    setSystemClk32MHZ();
    halOLED12864Init();
    while(1)
    {
        /* Test1 - 显示 8×16 的字符 */
        halOLED12864ShowX16(0, 0, "0123456789");//在第1行显示
        halOLED12864ShowX16(1, 0, "abcdefghiABCDE");//在第2行显示
        halOLED12864ShowX16(2, 0, "{}[]()!@#$%");//在第3行显示
        halOLED12864ShowX16(3, 0, "==========>");//在第3行显示

        delayMs(SYSCLK_32MHZ, 4000);//延迟
        halOLED12864ClearScreen();//清空
    
        /* Test2 - 显示 8×16 字符 和 16×16 汉字 */
        halOLED12864ShowX16(0, 0,  "今天气温：");
        halOLED12864ShowX16(1, 30, "温度：22 ℃");
        halOLED12864ShowX16(2, 30, "湿度：30 %");
        /* 注意：对于汉字，必须先取字模后存放到汉字字库文件font_chinese_v_16x16.h中*/
        
        delayMs(SYSCLK_32MHZ, 4000);//延迟
        halOLED12864ClearScreen();//清空

        /* Test3 - 在坐标（30像素, 30像素）处显示分辨率为 32x32 像素的图片*/
        halOLED12864ShowPicture(30, 30, 32, 32, Picture_32x32_AppleIco);
        /*注意：对于图片，系需要先取模后存放在图库文件font_v_picture.h中*/
        
        delayMs(SYSCLK_32MHZ, 4000);//延迟
        halOLED12864ClearScreen();//清空

         /* Test4 - 全屏显示 128x64 图片，即在坐标（30像素, 30像素）处显示一张分辨率为128x64像素的图片 */
        halOLED12864ShowPicture(0, 0, 128, 64, Picture_128x128_SuccessPic);

        delayMs(SYSCLK_32MHZ, 4000);//延迟
        halOLED12864ClearScreen();//清
    }
}
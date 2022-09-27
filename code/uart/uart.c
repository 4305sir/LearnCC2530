#include "uart.h"




/*
 * 初始化串口0
 */
void InitUart0(void)  
{  
    PERCFG = 0x00;//配置P0_2和P0_3用作串口0的TX（发送端）和RX（接收端）
    P0SEL  = 0x3c;//配置P0_2和P0_3用作外设功能，而不是GPIO
    P2DIR &= ~0xc0;//配置端口0优先用作USART0
  
    U0CSR |= 0x80;//设置USART0工作模式为UART0
  
    /* 设置波特率为115200 */  
    U0GCR  |= 11;//BAUD_E  
    U0BAUD |= 216;//BAUD_M  
  
    UTX0IF = 0;// 清零UART0发送中断标志位    
    URX0IF = 0;// 清零UART0接收中断标志位  
    URX0IE = 1;//使能串口0接收中断  
    EA = 1;//打开中断总开关
  
    U0CSR |= 0x40;//启用数据接收功能
}

#pragma vector = URX0_VECTOR 
__interrupt void URX0_ISR(void)  
{  
    uint8_t rxChar;

    URX0IF = 0;//清零中断标志位

    rxChar = U0DBUF;//U0DBUF存放了从串口0接收到的数据
    uart0Send(&rxChar, 1); //通过串口0发送数据，即把从串口0接收到的数据又从串口0发送回去
}

/**
 * @fn      uart0Send
 * 
 * @brief	通过串口0发送数据
 *
 * @param pMsg - 待发送数据的地址
 * @param msgLen - 待发送数据的长度，以字节为单位

 *
 * @return 	none
 */
void uart0Send(uint8_t *pMsg, uint8_t msgLen)  
{  
    uint8_t i;  
    for (i = 0; i < msgLen; i++) {  
        U0DBUF = pMsg[i];//把数据存放到串口0数据缓存寄存器U0DBUF中
        while (UTX0IF == 0);//等待发送完成
        UTX0IF = 0;//清零中断标志位
    }  
}

void initUart0_modeIs(Usart_BaudrateIn32MHz_t baudrate)
{
    PERCFG = 0x00;  // USART 0 I/O location: alternative 1 location
    P0SEL  = 0x3c;  // P0_2, P0_3 as peripheral function
    P2DIR &= ~0xc0; // Port 0 periphera 1st priority: USART 0

    U0CSR |= 0x80;  // USART mode select: UART mode

    struct {
        Usart_BaudrateIn32MHz_t B;
        unsigned char E;
        unsigned char M;
    } baudrate_list[] = {
      { USART_BAUDRATE_2400,   6,  59  },
      { USART_BAUDRATE_4800,   7,  59  },
      { USART_BAUDRATE_9600,   8,  59  },
      { USART_BAUDRATE_14400,  8,  216 },
      { USART_BAUDRATE_19200,  9,  59  },
      { USART_BAUDRATE_28800,  9,  216 },
      { USART_BAUDRATE_38400,  10, 59  },
      { USART_BAUDRATE_57600,  10, 216 },
      { USART_BAUDRATE_76800,  11, 59  },
      { USART_BAUDRATE_115200, 11, 216 },
      { USART_BAUDRATE_230400, 12, 216 },
    };
    
    unsigned char i;
    for (i = 0; i < (sizeof(baudrate_list)/sizeof(baudrate_list[0])); i++) {
        if (baudrate_list[i].B != baudrate)  continue;
        
        U0GCR  |= baudrate_list[i].E;
        U0BAUD |= baudrate_list[i].M;
        
        break;
    }

    UTX0IF = 0;     // Clear tx-interrupt flag
    URX0IF = 0;     // Clear rx-interrupt flag
    URX0IE = 1;     // Enable rx interrupt
    EA = 1;         // Enable interrupts

    U0CSR |= 0x40;  // Enable UART-Rx
}
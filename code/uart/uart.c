#include "uart.h"




/*
 * ��ʼ������0
 */
void InitUart0(void)  
{  
    PERCFG = 0x00;//����P0_2��P0_3��������0��TX�����Ͷˣ���RX�����նˣ�
    P0SEL  = 0x3c;//����P0_2��P0_3�������蹦�ܣ�������GPIO
    P2DIR &= ~0xc0;//���ö˿�0��������USART0
  
    U0CSR |= 0x80;//����USART0����ģʽΪUART0
  
    /* ���ò�����Ϊ115200 */  
    U0GCR  |= 11;//BAUD_E  
    U0BAUD |= 216;//BAUD_M  
  
    UTX0IF = 0;// ����UART0�����жϱ�־λ    
    URX0IF = 0;// ����UART0�����жϱ�־λ  
    URX0IE = 1;//ʹ�ܴ���0�����ж�  
    EA = 1;//���ж��ܿ���
  
    U0CSR |= 0x40;//�������ݽ��չ���
}

#pragma vector = URX0_VECTOR 
__interrupt void URX0_ISR(void)  
{  
    uint8_t rxChar;

    URX0IF = 0;//�����жϱ�־λ

    rxChar = U0DBUF;//U0DBUF����˴Ӵ���0���յ�������
    uart0Send(&rxChar, 1); //ͨ������0�������ݣ����ѴӴ���0���յ��������ִӴ���0���ͻ�ȥ
}

/**
 * @fn      uart0Send
 * 
 * @brief	ͨ������0��������
 *
 * @param pMsg - ���������ݵĵ�ַ
 * @param msgLen - ���������ݵĳ��ȣ����ֽ�Ϊ��λ

 *
 * @return 	none
 */
void uart0Send(uint8_t *pMsg, uint8_t msgLen)  
{  
    uint8_t i;  
    for (i = 0; i < msgLen; i++) {  
        U0DBUF = pMsg[i];//�����ݴ�ŵ�����0���ݻ���Ĵ���U0DBUF��
        while (UTX0IF == 0);//�ȴ��������
        UTX0IF = 0;//�����жϱ�־λ
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
#include "driverlib.h"
#include "mpu.h"

uint8_t receive[11];

void MPU_init(void)
{
    int8_t i, transmit[5];

    transmit[0]=0xFF;
    transmit[1]=0xAA;
    transmit[2]=0x69;
    transmit[3]=0x88;
    transmit[4]=0xB5;

    for(i = 0; i < 5; i++)
        USCI_A_UART_transmitData(USCI_A0_BASE, transmit[i]);

    transmit[0]=0XFF;
    transmit[1]=0XAA;
    transmit[2]=0X00;
    transmit[3]=0XFF;
    transmit[4]=0X00;

    for(i = 0; i < 5; i++)
        USCI_A_UART_transmitData(USCI_A0_BASE, transmit[i]);
}

float MPU_getRoll(void)
{
    return ((float)(receive[3] << 8 | receive[2]) / 32768 * 180);
}

float MPU_getPitch(void)
{
    return ((float)(receive[5] << 8 | receive[4]) / 32768 * 180);
}

float MPU_getYaw(void)
{
    return ((float)(receive[7] << 8 | receive[6]) / 32768 * 180);
}

//#pragma vector=USCI_A0_VECTOR
//__interrupt void USCI_A0_ISR (void)
//{
//    static uint16_t i = 0;
//    switch (__even_in_range(UCA0IV,4))
//    {
//        //Vector 2 - RXIFG
//        case 2:
//            receive[i] = USCI_A_UART_receiveData(USCI_A0_BASE);
//            i++;
//            i %= 11;
//            if(i == 2 && (receive[0] != 0x55 || receive[1] != 0x53))
//                i = 0;
//            break;
//        default:
//            break;
//    }
//}


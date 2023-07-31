#include "driverlib.h"
#include "track.h"

void TRACK_init(void)
{
    // LL Ȩֵ 16
    GPIO_setAsInputPin(LL_PORT, LL_PIN);
    // L  Ȩֵ 8
    GPIO_setAsInputPin(L_PORT, L_PIN);
    // M  Ȩֵ 4
    GPIO_setAsInputPin(M_PORT, M_PIN);
    // R  Ȩֵ 2
    GPIO_setAsInputPin(R_PORT, R_PIN);
    // RR Ȩֵ 1
    GPIO_setAsInputPin(RR_PORT, RR_PIN);
}

/*******************************
 * ����-����-�ߵ�ƽ---�Ǻ���-����-�͵�ƽ
 * Value : 0 ~ 31
 *******************************/
uint8_t TRACK_getValue(void)
{

    uint8_t Value = 0;
    if(GPIO_getInputPinValue(LL_PORT, LL_PIN))
        Value |= 0x10;
    if(GPIO_getInputPinValue(L_PORT, L_PIN))
        Value |= 0x08;
    if(GPIO_getInputPinValue(M_PORT, M_PIN))
        Value |= 0x04;
    if(GPIO_getInputPinValue(R_PORT, R_PIN))
        Value |= 0x02;
    if(GPIO_getInputPinValue(RR_PORT, RR_PIN))
        Value |= 0x01;
    return Value;
}

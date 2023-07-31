#include "driverlib.h"
#include "track.h"

void TRACK_init(void)
{
    // LL 权值 16
    GPIO_setAsInputPin(LL_PORT, LL_PIN);
    // L  权值 8
    GPIO_setAsInputPin(L_PORT, L_PIN);
    // M  权值 4
    GPIO_setAsInputPin(M_PORT, M_PIN);
    // R  权值 2
    GPIO_setAsInputPin(R_PORT, R_PIN);
    // RR 权值 1
    GPIO_setAsInputPin(RR_PORT, RR_PIN);
}

/*******************************
 * 黑线-灯灭-高电平---非黑线-灯亮-低电平
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

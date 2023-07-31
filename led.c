#include "driverlib.h"
#include "led.h"

void LED_init(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    LED_greenOff();
    LED_redOff();
}

void LED_redOn(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_greenOn(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
}
void LED_redToggle(void)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_greenToggle(void)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN7);
}

void LED_redOff(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_greenOff(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
}

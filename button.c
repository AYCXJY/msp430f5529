#include "driverlib.h"

void BUTTON_init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
}
//#pragma vector=PORT1_VECTOR
//__interrupt void PORT1_ISR (void)
//{
//    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1))
//    {
//        delay_ms(20);
//        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
//        {
//        }
//        GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
//    }
//}
//#pragma vector=PORT2_VECTOR
//__interrupt void PORT2_ISR (void)
//{
//    if(GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
//    {
//        delay_ms(20);
//        if(GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
//        {
//        }
//        GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
//    }
//}

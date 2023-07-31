#include "driverlib.h"
#include "sys.h"
#include "uart.h"
#include "oled.h"
#include "mpu.h"
#include "button.h"
#include "led.h"
#include "track.h"
#include "pid.h"
#include "motor.h"

float Roll, Pitch, Yaw;
uint8_t modify_p_enable;
uint8_t modify_i_enable;
uint8_t modify_d_enable;
uint8_t modify_s_enable;

uint8_t TrackValue;

void main(void)
{
    // 关闭看门狗
    WDT_A_hold(WDT_A_BASE);
    // 系统时钟初始化
    SYS_clockInit();
    // 串口0初始化
    UART_init(USCI_A0_BASE, 115200);
    // 串口1初始化
//    UART_init(USCI_A1_BASE, 115200);
    // OLED初始化
    OLED_init();
    // MPU初始化
    MPU_init();
    // 按键初始化
    BUTTON_init();
    // LED灯初始化
    LED_init();
    // 灰度传感器初始化
    TRACK_init();
    // 电机初始化
    MOTOR_init();
    // PID定时器使能
    PID_intervalTimerInit();
    // 打开全局中断
    _enable_interrupt();

    MOTOR_forward();
    while(1)
    {
        Roll = MPU_getRoll();
        Pitch = MPU_getPitch();
        Yaw = MPU_getYaw();
        OLED_showSignNum(0, 0, Roll, 4, 12);
        OLED_showSignNum(0, 2, Pitch, 4, 12);
        OLED_showSignNum(0, 4, Yaw, 4, 12);
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void)
{
    // 右按键
    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1))
    {
        delay_ms(20);
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
        {
            LED_greenToggle();
        }
        GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    }
}
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR (void)
{
    // 左 编码器
    if(GPIO_getInterruptStatus(L_ENCODER_PORT, L_ENCODER_PIN))
    {
        L_count++;
        GPIO_clearInterrupt(L_ENCODER_PORT, L_ENCODER_PIN);
    }
    // 右 编码器
    if(GPIO_getInterruptStatus(R_ENCODER_PORT, R_ENCODER_PIN))
    {
        R_count++;
        GPIO_clearInterrupt(R_ENCODER_PORT, R_ENCODER_PIN);
    }
    // 左按键
    if(GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
    {
        delay_ms(20);
        if(GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
        {
            LED_redToggle();
        }
        GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
    }

}

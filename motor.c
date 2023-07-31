#include "driverlib.h"
#include "motor.h"
#include "track.h"
#include "mpu.h"

void MOTOR_init(void)
{
    // 前左 IN1 -> P3.7
    GPIO_setAsOutputPin(FL_IN1_PORT, FL_IN1_PIN);
    // 前左 IN2 -> P8.2
    GPIO_setAsOutputPin(FL_IN2_PORT, FL_IN2_PIN);
    // 后左 IN1 -> P4.0
    GPIO_setAsOutputPin(BL_IN1_PORT, BL_IN1_PIN);
    // 后左 IN2 -> P4.3
    GPIO_setAsOutputPin(BL_IN2_PORT, BL_IN2_PIN);
    // 前右 IN1 -> P6.0
    GPIO_setAsOutputPin(FR_IN1_PORT, FR_IN1_PIN);
    // 前右 IN2 -> P6.1
    GPIO_setAsOutputPin(FR_IN2_PORT, FR_IN2_PIN);
    // 后右 IN1 -> P6.2
    GPIO_setAsOutputPin(BR_IN1_PORT, BR_IN1_PIN);
    // 后右 IN2 -> p6.3
    GPIO_setAsOutputPin(BR_IN2_PORT, BR_IN2_PIN);
    // 前左 编码器 ->P2.4
    GPIO_setAsInputPin(L_ENCODER_PORT, L_ENCODER_PIN);
    GPIO_enableInterrupt(L_ENCODER_PORT, L_ENCODER_PIN);
    GPIO_selectInterruptEdge(L_ENCODER_PORT, L_ENCODER_PIN, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(L_ENCODER_PORT, L_ENCODER_PIN);
    // 前右 编码器 ->P2.5
    GPIO_setAsInputPin(R_ENCODER_PORT, R_ENCODER_PIN);
    GPIO_enableInterrupt(R_ENCODER_PORT, R_ENCODER_PIN);
    GPIO_selectInterruptEdge(R_ENCODER_PORT, R_ENCODER_PIN, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(R_ENCODER_PORT, R_ENCODER_PIN);
    //  前左 PWM -> P1.2
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);
    //  后左 PWM -> P1.3
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);
    //  前右 PWM -> P1.4
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);
    //  后右 PWM -> P1.5
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);

    Timer_A_outputPWMParam htim_pwm = {0};
    htim_pwm.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    htim_pwm.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_5;
    htim_pwm.timerPeriod = 500 - 1;
    htim_pwm.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    htim_pwm.dutyCycle = (500 - 1) * 0.23;
    //  前左 PWM -> P1.2
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  后左 PWM -> P1.3
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  前右 PWM -> P1.4
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  后右 PWM -> P1.5
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
}

void MOTOR_forward(void)
{
    // 左侧正转
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // 右侧正转
    FR_IN1_SET;
    FR_IN2_RESET;
    BR_IN1_SET;
    BR_IN2_RESET;
}

void MOTOR_leftTurn(void)
{
    // 左侧反转
    FL_IN1_RESET;
    FL_IN2_SET;
    BL_IN1_RESET;
    BL_IN2_SET;
    // 右侧正转
    FR_IN1_SET;
    FR_IN2_RESET;
    BR_IN1_SET;
    BR_IN2_RESET;
    // 获得当前占空比
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // 加速转弯
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURN_DUTYCYCLE);
    // 等待转到位
    while(TRACK_getValue() != 4);
//    while(MPU_getYaw() < 90);
    // 复原占空比
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // 小车前进
    MOTOR_forward();
}

void MOTOR_rightTurn(void)
{
    // 左侧正转
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // 右侧反转
    FR_IN1_RESET;
    FR_IN2_SET;
    BR_IN1_RESET;
    BR_IN2_SET;
    // 获得当前占空比
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // 加速转弯
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURN_DUTYCYCLE);
    // 等待转到位
    while(TRACK_getValue() != 4);
    // 复原占空比
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // 小车前进
    MOTOR_forward();
}

void MOTOR_turnAround(void)
{
    // 左侧正转
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // 右侧反转
    FR_IN1_RESET;
    FR_IN2_SET;
    BR_IN1_RESET;
    BR_IN2_SET;
    // 获得当前占空比
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // 加速转弯
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURNAROUND_DUTYCYCLE);
    // 等待转到位
    while(TRACK_getValue() != 4);
    // 复原占空比
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // 小车前进
    MOTOR_forward();
}

void MOTOR_stop(void)
{
    // 左侧停止
    FL_IN1_RESET;
    FL_IN2_RESET;
    BL_IN1_RESET;
    BL_IN2_RESET;
    // 右侧停止
    FR_IN1_RESET;
    FR_IN2_RESET;
    BR_IN1_RESET;
    BR_IN2_RESET;
}

void MOTOR_leftCorrect(void)
{
    // 获得当前占空比
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // 左侧停止，右侧加速
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, CORRECT_DUTYCYCLE);
    // 等待转到位
    while(TRACK_getValue() != 4);
    // 复原占空比
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
}

void MOTOR_rightCorrect(void)
{
    // 获得当前占空比
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // 左侧加速，右侧停止
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, 0);
    // 等待转到位
    while(TRACK_getValue() != 4);
    // 复原占空比
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
}


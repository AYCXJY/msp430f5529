#include "driverlib.h"
#include "motor.h"
#include "track.h"
#include "mpu.h"

void MOTOR_init(void)
{
    // ǰ�� IN1 -> P3.7
    GPIO_setAsOutputPin(FL_IN1_PORT, FL_IN1_PIN);
    // ǰ�� IN2 -> P8.2
    GPIO_setAsOutputPin(FL_IN2_PORT, FL_IN2_PIN);
    // ���� IN1 -> P4.0
    GPIO_setAsOutputPin(BL_IN1_PORT, BL_IN1_PIN);
    // ���� IN2 -> P4.3
    GPIO_setAsOutputPin(BL_IN2_PORT, BL_IN2_PIN);
    // ǰ�� IN1 -> P6.0
    GPIO_setAsOutputPin(FR_IN1_PORT, FR_IN1_PIN);
    // ǰ�� IN2 -> P6.1
    GPIO_setAsOutputPin(FR_IN2_PORT, FR_IN2_PIN);
    // ���� IN1 -> P6.2
    GPIO_setAsOutputPin(BR_IN1_PORT, BR_IN1_PIN);
    // ���� IN2 -> p6.3
    GPIO_setAsOutputPin(BR_IN2_PORT, BR_IN2_PIN);
    // ǰ�� ������ ->P2.4
    GPIO_setAsInputPin(L_ENCODER_PORT, L_ENCODER_PIN);
    GPIO_enableInterrupt(L_ENCODER_PORT, L_ENCODER_PIN);
    GPIO_selectInterruptEdge(L_ENCODER_PORT, L_ENCODER_PIN, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(L_ENCODER_PORT, L_ENCODER_PIN);
    // ǰ�� ������ ->P2.5
    GPIO_setAsInputPin(R_ENCODER_PORT, R_ENCODER_PIN);
    GPIO_enableInterrupt(R_ENCODER_PORT, R_ENCODER_PIN);
    GPIO_selectInterruptEdge(R_ENCODER_PORT, R_ENCODER_PIN, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(R_ENCODER_PORT, R_ENCODER_PIN);
    //  ǰ�� PWM -> P1.2
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);
    //  ���� PWM -> P1.3
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);
    //  ǰ�� PWM -> P1.4
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);
    //  ���� PWM -> P1.5
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);

    Timer_A_outputPWMParam htim_pwm = {0};
    htim_pwm.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    htim_pwm.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_5;
    htim_pwm.timerPeriod = 500 - 1;
    htim_pwm.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    htim_pwm.dutyCycle = (500 - 1) * 0.23;
    //  ǰ�� PWM -> P1.2
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  ���� PWM -> P1.3
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  ǰ�� PWM -> P1.4
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
    //  ���� PWM -> P1.5
    htim_pwm.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
    Timer_A_outputPWM(TIMER_A0_BASE, &htim_pwm);
}

void MOTOR_forward(void)
{
    // �����ת
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // �Ҳ���ת
    FR_IN1_SET;
    FR_IN2_RESET;
    BR_IN1_SET;
    BR_IN2_RESET;
}

void MOTOR_leftTurn(void)
{
    // ��෴ת
    FL_IN1_RESET;
    FL_IN2_SET;
    BL_IN1_RESET;
    BL_IN2_SET;
    // �Ҳ���ת
    FR_IN1_SET;
    FR_IN2_RESET;
    BR_IN1_SET;
    BR_IN2_RESET;
    // ��õ�ǰռ�ձ�
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // ����ת��
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURN_DUTYCYCLE);
    // �ȴ�ת��λ
    while(TRACK_getValue() != 4);
//    while(MPU_getYaw() < 90);
    // ��ԭռ�ձ�
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // С��ǰ��
    MOTOR_forward();
}

void MOTOR_rightTurn(void)
{
    // �����ת
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // �Ҳ෴ת
    FR_IN1_RESET;
    FR_IN2_SET;
    BR_IN1_RESET;
    BR_IN2_SET;
    // ��õ�ǰռ�ձ�
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // ����ת��
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURN_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURN_DUTYCYCLE);
    // �ȴ�ת��λ
    while(TRACK_getValue() != 4);
    // ��ԭռ�ձ�
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // С��ǰ��
    MOTOR_forward();
}

void MOTOR_turnAround(void)
{
    // �����ת
    FL_IN1_SET;
    FL_IN2_RESET;
    BL_IN1_SET;
    BL_IN2_RESET;
    // �Ҳ෴ת
    FR_IN1_RESET;
    FR_IN2_SET;
    BR_IN1_RESET;
    BR_IN2_SET;
    // ��õ�ǰռ�ձ�
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // ����ת��
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, TURNAROUND_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, TURNAROUND_DUTYCYCLE);
    // �ȴ�ת��λ
    while(TRACK_getValue() != 4);
    // ��ԭռ�ձ�
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
    // С��ǰ��
    MOTOR_forward();
}

void MOTOR_stop(void)
{
    // ���ֹͣ
    FL_IN1_RESET;
    FL_IN2_RESET;
    BL_IN1_RESET;
    BL_IN2_RESET;
    // �Ҳ�ֹͣ
    FR_IN1_RESET;
    FR_IN2_RESET;
    BR_IN1_RESET;
    BR_IN2_RESET;
}

void MOTOR_leftCorrect(void)
{
    // ��õ�ǰռ�ձ�
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // ���ֹͣ���Ҳ����
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, CORRECT_DUTYCYCLE);
    // �ȴ�ת��λ
    while(TRACK_getValue() != 4);
    // ��ԭռ�ձ�
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
}

void MOTOR_rightCorrect(void)
{
    // ��õ�ǰռ�ձ�
    uint16_t dutyCycle = Timer_A_getCaptureCompareCount(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
    // �����٣��Ҳ�ֹͣ
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, CORRECT_DUTYCYCLE);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, 0);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, 0);
    // �ȴ�ת��λ
    while(TRACK_getValue() != 4);
    // ��ԭռ�ձ�
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, dutyCycle);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, dutyCycle);
}


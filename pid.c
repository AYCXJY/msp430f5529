#include "driverlib.h"
#include "pid.h"
#include "uart.h"
#define COMPARE_CCR0_INTERVAL_VALUE     16


uint16_t L_count, R_count;
float L_speed, R_speed, ActualSpeed;
float TargetSpeed = 100;
struct PID
{
    volatile double   kp;
    volatile double   ki;
    volatile double   kd;
    volatile int      err;
    volatile int      last_err;
    volatile int      last_last_err;
}pid ={0.1, 0.1, 0, 0, 0, 0};


float PID_incrementalCalculate(uint16_t TargetSpeed, uint16_t actual_value, struct PID* pid)
{
    float result = 0;
    pid->err = TargetSpeed - actual_value;
    result = pid->kp * (pid->err - pid->last_err) + pid->ki * pid->err + pid->kd * (pid->err - 2 * pid->last_err + pid->last_last_err);
    pid->last_last_err = pid->last_err;
    pid->last_err = pid->err;
    return result;
}
/*采样周期 = 31.25ms*/
void PID_intervalTimerInit(void)
{
    Timer_A_initContinuousModeParam initContinuousParam = {0};
    initContinuousParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;// 32768
    initContinuousParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;//512 HZ
    initContinuousParam.timerClear = TIMER_A_DO_CLEAR;
    initContinuousParam.startTimer = true;
    Timer_A_initContinuousMode(TIMER_A2_BASE, &initContinuousParam);

    Timer_A_initCompareModeParam initCompareParam = {0};
    initCompareParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompareParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompareParam.compareValue = COMPARE_CCR0_INTERVAL_VALUE;
    Timer_A_initCompareMode(TIMER_A2_BASE, &initCompareParam);
}

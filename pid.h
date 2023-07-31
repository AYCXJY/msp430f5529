#ifndef PID_H_
#define PID_H_

extern struct PID pid;
extern uint16_t L_count, R_count;
extern float L_speed, R_speed, ActualSpeed, TargetSpeed;

float PID_incrementalCalculate(uint16_t target_value, uint16_t actual_value, struct PID* pid);

void PID_intervalTimerInit(void);

#endif /* PID_H_ */

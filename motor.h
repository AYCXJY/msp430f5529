#ifndef MOTOR_H_
#define MOTOR_H_
// IO ∂®“Â
#define FL_IN1_PORT     GPIO_PORT_P3
#define FL_IN1_PIN      GPIO_PIN7
#define FL_IN2_PORT     GPIO_PORT_P8
#define FL_IN2_PIN      GPIO_PIN2

#define BL_IN1_PORT     GPIO_PORT_P4
#define BL_IN1_PIN      GPIO_PIN0
#define BL_IN2_PORT     GPIO_PORT_P4
#define BL_IN2_PIN      GPIO_PIN3

#define FR_IN1_PORT     GPIO_PORT_P6
#define FR_IN1_PIN      GPIO_PIN0
#define FR_IN2_PORT     GPIO_PORT_P6
#define FR_IN2_PIN      GPIO_PIN1

#define BR_IN1_PORT     GPIO_PORT_P6
#define BR_IN1_PIN      GPIO_PIN2
#define BR_IN2_PORT     GPIO_PORT_P6
#define BR_IN2_PIN      GPIO_PIN3

#define L_ENCODER_PORT GPIO_PORT_P2
#define L_ENCODER_PIN  GPIO_PIN4

#define R_ENCODER_PORT GPIO_PORT_P2
#define R_ENCODER_PIN  GPIO_PIN5

#define FL_IN1_SET      GPIO_setOutputHighOnPin(FL_IN1_PORT, FL_IN1_PIN);
#define FL_IN1_RESET    GPIO_setOutputLowOnPin(FL_IN1_PORT, FL_IN1_PIN);
#define FL_IN2_SET      GPIO_setOutputHighOnPin(FL_IN2_PORT, FL_IN2_PIN);
#define FL_IN2_RESET    GPIO_setOutputLowOnPin(FL_IN2_PORT, FL_IN2_PIN);

#define BL_IN1_SET      GPIO_setOutputHighOnPin(BL_IN1_PORT, BL_IN1_PIN);
#define BL_IN1_RESET    GPIO_setOutputLowOnPin(BL_IN1_PORT, BL_IN1_PIN);
#define BL_IN2_SET      GPIO_setOutputHighOnPin(BL_IN2_PORT, BL_IN2_PIN);
#define BL_IN2_RESET    GPIO_setOutputLowOnPin(BL_IN2_PORT, BL_IN2_PIN);

#define FR_IN1_SET      GPIO_setOutputHighOnPin(FR_IN1_PORT, FR_IN1_PIN);
#define FR_IN1_RESET    GPIO_setOutputLowOnPin(FR_IN1_PORT, FR_IN1_PIN);
#define FR_IN2_SET      GPIO_setOutputHighOnPin(FR_IN2_PORT, FR_IN2_PIN);
#define FR_IN2_RESET    GPIO_setOutputLowOnPin(FR_IN2_PORT, FR_IN2_PIN);

#define BR_IN1_SET      GPIO_setOutputHighOnPin(BR_IN1_PORT, BR_IN1_PIN);
#define BR_IN1_RESET    GPIO_setOutputLowOnPin(BR_IN1_PORT, BR_IN1_PIN);
#define BR_IN2_SET      GPIO_setOutputHighOnPin(BR_IN2_PORT, BR_IN2_PIN);
#define BR_IN2_RESET    GPIO_setOutputLowOnPin(BR_IN2_PORT, BR_IN2_PIN);

#define CORRECT_DUTYCYCLE       dutyCycle + 70
#define TURN_DUTYCYCLE          dutyCycle + 70
#define TURNAROUND_DUTYCYCLE    dutyCycle + 70

void MOTOR_init(void);

void MOTOR_forward(void);

void MOTOR_leftTurn(void);

void MOTOR_rightTurn(void);

void MOTOR_turnAround(void);

void MOTOR_stop(void);

void MOTOR_leftCorrect(void);

void MOTOR_rightCorrect(void);

#endif /* MOTOR_H_ */

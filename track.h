#ifndef TRACK_H_
#define TRACK_H_

#define LL_PORT     GPIO_PORT_P8
#define LL_PIN      GPIO_PIN1

#define L_PORT      GPIO_PORT_P2
#define L_PIN       GPIO_PIN3

#define M_PORT      GPIO_PORT_P2
#define M_PIN       GPIO_PIN6

#define R_PORT      GPIO_PORT_P3
#define R_PIN       GPIO_PIN1

#define RR_PORT     GPIO_PORT_P3
#define RR_PIN      GPIO_PIN0

void TRACK_init(void);

uint8_t TRACK_getValue(void);

#endif /* TRACK_H_ */

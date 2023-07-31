#ifndef UART_H_
#define UART_H_

void UART_printf(uint16_t baseAddress, const char *format,...);
bool UART_init(uint16_t baseAddress, uint32_t Baudrate);

#endif /* UART_H_ */


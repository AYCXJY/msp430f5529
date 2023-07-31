#ifndef __OLED_H
#define __OLED_H

#define SCL_PORT        GPIO_PORT_P4
#define SCL_PIN         GPIO_PIN2
#define SCL_SET         GPIO_setOutputHighOnPin(SCL_PORT, SCL_PIN)
#define SCL_RESET       GPIO_setOutputLowOnPin(SCL_PORT, SCL_PIN)

#define SDA_PORT        GPIO_PORT_P4
#define SDA_PIN         GPIO_PIN1
#define SDA_SET         GPIO_setOutputHighOnPin(SDA_PORT, SDA_PIN)
#define SDA_RESET       GPIO_setOutputLowOnPin(SDA_PORT, SDA_PIN)

#define OLED_MODE       0
#define SIZE            8
#define XLevelL         0x00
#define XLevelH         0x10
#define Max_Column      128
#define Max_Row         64
#define Brightness      0xFF
#define X_WIDTH         128
#define Y_WIDTH         64
#define OLED_CMD        0
#define OLED_DATA       1

#define OLED_SCLK_Clr()     SCL_RESET
#define OLED_SCLK_Set()     SCL_SET
#define OLED_SDIN_Clr()     SDA_RESET
#define OLED_SDIN_Set()     SDA_SET

void OLED_init(void);

void OLED_clear(void);

void OLED_showChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);

void OLED_showNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);

void OLED_showSignNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t size2);

void OLED_showString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);

#endif

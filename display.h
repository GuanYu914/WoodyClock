#ifndef _DISPLAY_H
#define _DISPLAY_H

// display digit switch
#define BUT_DIGIT0  PD3 // digit_0 switch
#define BUT_DIGIT1  PD4 // digit_1 switch
#define BUT_DIGIT2  PD5 // digit_2 switch 
#define BUT_DIGIT3  PD6 // digit_3 switch

// sn74hc595 shift register
#define DISPLAY_PORT PORTD
#define DISPLAY_DDR  DDRD

#define HC595_SER   PD0 // Serial data input
#define HC595_RCLK  PD1 // Shift register clock
#define HC595_SRCLK PD2 // Storage register clock

// Low level macros to change SER Line
#define HC595DataHigh() (DISPLAY_PORT|=(1<<HC595_SER))
#define HC595DataLow()  (DISPLAY_PORT&=(~(1<<HC595_SER)))

// define display num hex code
#define SEG_0 0x3f 
#define SEG_1 0x06
#define SEG_2 0x5b
#define SEG_3 0x4f
#define SEG_4 0x66
#define SEG_5 0x6d
#define SEG_6 0x7d
#define SEG_7 0x27
#define SEG_8 0x7f
#define SEG_9 0X6f
#define SEG_E 0x79

// mathod description
void HC595Init();
void HC595Pulse();
void HC595Latch();
void HC595Write(uint8_t);
void SevenSegDisplay(uint8_t);

#endif

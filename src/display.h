#ifndef _DISPLAY_H
#define _DISPLAY_H

#define DISPLAY_PORT PORTD
#define DISPLAY_DDR  DDRD
// display digit switch
#define BUT_DIGIT0  PD3 // digit_0 switch
#define BUT_DIGIT1  PD4 // digit_1 switch
#define BUT_DIGIT2  PD5 // digit_2 switch 
#define BUT_DIGIT3  PD6 // digit_3 switch
#define BUT_DIGIT4  PD7 // time switch

// sn74hc595 shift register
#define SHIFT_PORT PORTC
#define SHIFT_DDR  DDRC

#define HC595_SER   PC3 // Serial data input
#define HC595_RCLK  PC2 // Shift register clock
#define HC595_SRCLK PC1 // Storage register clock

// Low level macros to change SER Line
#define HC595DataHigh() (SHIFT_PORT|=(1<<HC595_SER))
#define HC595DataLow()  (SHIFT_PORT&=(~(1<<HC595_SER)))

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

// define special characters
#define SEG_Colon 0x80 // : display character
#define SEG_O     0x63 // o display character
#define SEG_LOGO  0x5c // logo display character
#define SEG_C     0x39 // c display character

// mathod description
void HC595Init();
void HC595Pulse();
void HC595Latch();
void HC595Write(uint8_t);
void SevenSegDisplay(uint8_t);
void TimeBlinkDisplay();

#endif

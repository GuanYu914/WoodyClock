MCU   = atmega328p
# UL -> unsigned long
F_CPU = 16000000UL 
BAUD  = 19200UL

PROGRAMMER_TYPE = usbasp

# program for building
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude
PROGRAMMER = usbasp

# get current directory name as TARGET 
TARGET = $(lastword $(subst /, ,$(CURDIR)))

# find all .c/.h files in current dirctory
SOURCES = $(wildcard *.c $(LIBDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(SOURCES:.c=.h)

# compilation options
CFLAGS = -std=c99 -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I.

.PHONY: build flash clean info dis_bootloader en_bootloader

all: build flash

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $^ $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

build: $(TARGET).hex 

info:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) 

# ignore arduino optimal bootloader
# use this feature, then you can use whole flash program memory
dis_bootloader:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U hfuse:w:0xdf:m

# enable arduino optimal bootloader
en_bootloader:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U hfuse:w:0xde:m

flash:
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(TARGET).hex:i 

clean:
	rm -f *.o *.hex *.elf

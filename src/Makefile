# define the target of microcontroller and frequency
MCU   = atmega328p
# UL -> unsigned long
F_CPU = 16000000UL 

# program for building
# avr-gcc     -> gcc for avr
# avr-objcopy -> copy and translate object files
# avr-objdump -> display information from object files
# avrdude     -> avr flash software
# usbasp      -> avr flash hardware

#OBJDUMP = avr-objdump
#AVRSIZE = avr-size
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
PROGRAMMER = usbasp

# get current directory name as TARGET 
TARGET = $(lastword $(subst /, ,$(CURDIR)))

# find all .c/.h files in current dirctory
SOURCES = $(wildcard *.c $(LIBDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

#include lib config
LIB0 =.

# compilation options
# -std    -> select the language standard
# -Wall   -> enable all the warnings about construction
# -g      -> enable debug
# -Os     -> optimize for size
# -mmcu   -> specify ATMEL avr instructionset or MCU type
# -DF_CPU -> predefine F_CPU as macro name
# -I      -> add the directory to list of directories to be searched for header files
CFLAGS = -std=c99 -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(LIB0)

.PHONY: build flash clean info dis_bootloader en_bootloader

all: build flash

# cpoy .text and .data area to produce hex file
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

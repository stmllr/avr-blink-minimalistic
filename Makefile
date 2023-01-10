TARGET = blink
MCU    = atmega328p
CC     = avr-gcc

CFLAGS  =-mmcu=$(MCU) -Ofast -Wall -g
LDFLAGS =-mmcu=$(MCU) -Ofast -Wall

$(TARGET): $(TARGET).o

$(TARGET).hex : $(TARGET)
	avr-objcopy -j .data -j .text -O ihex $< $@

PROGRAMMER = -c
PROGRAMMER += arduino
PARTNO     = -p
PARTNO     += $(MCU)
PORT       = -P
PORT       += /dev/ttyUSB0
BAUDRATE   = -b
BAUDRATE   += 57600

program: $(TARGET).hex
	avrdude $(PARTNO) $(PROGRAMMER) $(PORT) $(BAUDRATE) -U flash:w:$(TARGET).hex -v

all: $(TARGET) program

clean:
	rm -f *.o  *.hex $(TARGET)

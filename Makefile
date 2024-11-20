TARGET = blink

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $(TARGET).o $(TARGET).c
	avr-gcc -mmcu=atmega328p $(TARGET).o -o $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

upload: default
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex

clean:
	rm -f *.o *.bin *.hex

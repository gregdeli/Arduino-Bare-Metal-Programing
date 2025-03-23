#TARGET = blink_inter_ctc

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $(TARGET).o $(TARGET).c
	avr-gcc -mmcu=atmega328p $(TARGET).o -o $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

upload: default
	avrdude -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex

arduino:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p \
	-I ArduinoCore-avr/cores/arduino \
	-I ArduinoCore-avr/variants/standard \
	-o $(TARGET).elf $(TARGET).c \
	-L ArduinoCore-avr/cores/arduino -lcore
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex

assembly:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -S -o $(TARGET).s $(TARGET).c

clean:
	rm -f *.o *.bin *.hex *.s *.elf $(TARGET)

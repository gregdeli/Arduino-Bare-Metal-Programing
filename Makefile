# Define the target file name
TARGET = blink

# Specify the MCU and clock frequency
MCU = atmega328p
F_CPU = 16000000UL

# Compiler and programmer settings
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
PROGRAMMER = arduino
PORT = /dev/ttyACM0
BAUD = 115200

# Optimization flags
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# Define the output file names
OBJ = $(TARGET).o
BIN = $(TARGET).bin
HEX = $(TARGET).hex

# Default target
all: $(HEX)

# Compile the source file to object file
$(OBJ): $(TARGET).c
	$(CC) $(CFLAGS) -c -o $(OBJ) $(TARGET).c

# Link the object file to create a binary
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

# Create the hex file from the binary
$(HEX): $(BIN)
	$(OBJCOPY) -O ihex -R .eeprom $(BIN) $(HEX)

# Upload the hex file to the Arduino
upload: $(HEX)
	$(AVRDUDE) -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

# Clean the generated files
clean:
	rm -f *.o *.bin *.hex


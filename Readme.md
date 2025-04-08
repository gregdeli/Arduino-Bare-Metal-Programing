
# Arduino Bare Metal Programming Basics

This repo is part of an introductory presentation on programming the ATmega328P (Arduino Uno's MCU), for the Upatras ACM Student Chapter Hardware Special Interest Group.


## Requirements
On a Linux system the following tools need to be installed 
```bash
  sudo apt install avr-libc avrdude binutils-avr gcc-avr
```
## Usage/Examples 
To run any of the code examples run:
```bash
./run_makefile.sh <rule> <target>
```
The rules are: 
- **default**: To compile the code and create an executable hex file.
- **upload**: To also upload the code to the microcontroller through port /dev/ttyACM0.
- **assembly**: To compile the code to assembly.

### Example
```bash
./run_makefile.sh upload blink
```


## Presentation
The slides presented at the Upatras ACM Student Chapter are located in: **Presentation/Arduino Bare Metal Programming.pdf**

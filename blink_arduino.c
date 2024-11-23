#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int main(void){
    init();

    DDRB = DDRB | (1<<DDB5);

    while(1){
        PORTB |= (1<<PORTB5);

        delay(1000);

        PORTB &= ~(1<<PORTB5);

        delay(1000);
    }

    return 0;
}

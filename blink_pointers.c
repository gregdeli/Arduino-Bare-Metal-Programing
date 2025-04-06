#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRB = DDRB | (1<<DDB5);
    // volatile uint8_t* ddrb = (volatile uint8_t*)0x24;
    // *ddrb |= (1<<DDB5);
    // *(volatile uint8_t*)0x24 |= (1<<PORTB5);


    while(1){
        PORTB |= (1<<PORTB5);
        // volatile uint8_t* portb = (volatile uint8_t*)0x25;
        // *portb |= (1<<PORTB5);
        // *(volatile uint8_t*)0x25 |= (1<<PORTB5);

        _delay_ms(1000);

        PORTB &= ~(1<<PORTB5);
        // *portb &= ~(1<<PORTB5);
        // *(volatile uint8_t*)0x25 &= ~(1<<PORTB5);

        _delay_ms(1000);
    }
}
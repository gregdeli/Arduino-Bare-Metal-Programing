#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void confTimer1(uint16_t delay_ms);

int main(void) {
    // Digital pin 2
    DDRD |= (1 << DDD2);

    PORTD |= (1 << PORTD2);

    sei(); // Enable global interrupts

    uint16_t delay_ms = 1000;

    confTimer1(delay_ms);
    
    // Do something else
    // Digital pin 3
    DDRD |= (1 << DDD3);
    while(1) {
        PORTD ^= (1 << PORTD3);
        _delay_ms(500);
    }

    return 0;
}

void confTimer1(uint16_t delay_ms) {
    // Configure Timer1 in CTC mode
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler 1024

    uint32_t ticks = (F_CPU / 1024 * delay_ms / 1000) - 1; // Calculate number of ticks for the delay
    
    if (ticks > 0xFFFF) {
        ticks = 0xFFFF; // Ensure ticks is within the 16-bit range
    }

    OCR1AH = (ticks >> 8); // Load the high byte of the OCR1A register
    OCR1AL = ticks; // Load the low byte of the OCR1A register
    
    TIMSK1 = (1 << OCIE1A); // Enable Timer1 compare match A interrupt
}



ISR(TIMER1_COMPA_vect) {
    PORTD ^= (1 << PORTD2); // Toggle LED
}
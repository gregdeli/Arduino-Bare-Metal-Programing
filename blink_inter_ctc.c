#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

void confTimer1(uint16_t delay_ms);

int main(void) {
    DDRB |= (1 << DDB5);

    // Turn on LED
    PORTB |= (1 << PORTB5);

    sei(); // Enable global interrupts

    uint16_t delay_ms = 1000;

    confTimer1(delay_ms);
    
    while(1) {
        // Do something else
    }

    return 0;
}

void confTimer1(uint16_t delay_ms) {
    // Calculate the number of ticks needed for the delay.
    uint32_t ticks = (F_CPU / 1024 * delay_ms / 1000) - 1;
    
    if (ticks > 0xFFFF) {
        ticks = 0xFFFF; // Limit ticks to 16-bit range.
    }

    // Load the OCR1A register (high byte then low byte)
    OCR1AH = (ticks >> 8);
    OCR1AL = ticks;

    // Configure Timer1 in CTC mode, prescaler 1024.
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    // Enable Timer1 compare match A interrupt.
    TIMSK1 = (1 << OCIE1A);
}



ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PORTB5); // Toggle LED
}
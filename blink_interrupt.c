#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL //unsigned long
#define PRESCALER 1024

void initTimer1(int delay_ms);

int main(void){
    // Led pin as output
    DDRB |= (1<<DDB5);

    // Enable the timer overflow interrupt
    TIMSK1 |= (1<<TOIE1);

    // Global interrupt enable
    sei();

    initTimer1(500);

    while(1){
        // Do nothing
    }

    return 0;
}

uint16_t init_val;

void initTimer1(int delay_ms){
    // Calculate the timer frequency
    float t_freq = F_CPU / PRESCALER;

    // Calculate the timer period
    float t_period = 1 / t_freq;

    // Number of timer ticks for the delay
    uint16_t ticks = (delay_ms / t_period) / 1000;

    // Set the timers initial value 
    init_val = 0xFFFF - ticks;

    // Load the timer with the initial value
    TCNT1H = (init_val >> 8);
    TCNT1L = init_val; 

    // Start the timer in Normal mode
    TCCR1B |= (1<<CS12) | (1<<CS10);
}

ISR(TIMER1_OVF_vect){
    // Toggle led pin
    PORTB ^= (1<<PORTB5);

    // Reload timer
    TCNT1H = (init_val >> 8);
    TCNT1L = init_val;
}
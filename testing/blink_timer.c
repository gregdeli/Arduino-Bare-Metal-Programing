#include <avr/io.h>

#define F_CPU 16000000UL //unsigned long
#define PRESCALER 1024


void my_delay(int delay_ms);

int main(void){
    // Led pin as output
    DDRB |= (1<<DDB5);

    while(1){
        // Toggle led pin
        PORTB ^= (1<<PORTB5);
        my_delay(1000);

        /*PORTB |= (1<<PORTB5);
        my_delay(1000);
        PORTB &= ~(1<<PORTB5);
        my_delay(1000);*/
    }

    return 0;

}

void my_delay(int delay_ms){
    // Calculate the timer frequency
    float t_freq = F_CPU / PRESCALER;

    // Calculate the timer period
    float t_period = 1 / t_freq;

    // Number of timer ticks for the delay
    uint16_t ticks = (delay_ms / t_period) / 1000;

    // Set the timers initial value 
    uint16_t init_val = 0xFFFF - ticks;

    // Load the timer with the initial value
    TCNT1H = (init_val >> 8);
    TCNT1L = init_val; 

    // Start the timer in Normal mode
    TCCR1B |= (1<<CS12) | (1<<CS10);

    // Wait for the timer to overflow
    while((TIFR1 & (1<<TOV1)) == 0);

    // Stop the timer and clear the timer clock 
    TCCR1B = 0;
    // or TCCR1B &= ~(1<<CS12) & ~(1<<CS10);

    // Clear the overflow flag
    TIFR1 |= (1<<TOV1);
}

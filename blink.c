#ifndef F_CPU
#define F_CPU 16000000L
#endif

#define DDRB *(volatile unsigned char *) 0x24
#define DDB5 5

#define PORTB *(volatile unsigned char *) 0x25
#define PORTB5 5

#define DELAY_MS 500

#include <util/delay.h>

int main(void) {
    // https://wiki.wpi.edu/robotics/Port_manipulation_and_digitalWrite()#Example:_Controlling_Arduino_pin_13

    // initialize digital pin LED_BUILTIN as an output.
    // equivalent to: pinMode(LED_BUILTIN, OUTPUT); // D13
    // or: DDRB |= 0b00100000;
    DDRB |= 1 << DDB5;

    // equivalent to: if (digitalRead(LED_BUILTIN) == LOW) { digitalWrite(LED_BUILTIN, HIGH); } else { digitalWrite(LED_BUILTIN, LOW); }
    while (1) {
        // Flip LED_BUILTIN (D13) bit
        PORTB ^= 1 << PORTB5;
        _delay_ms(DELAY_MS);
    }

    return 0;
}

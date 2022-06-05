#include <avr/io.h>

void blink(void) {
	PORTB ^= (1 << PB5);
}

#include "timer.h"
#include <stdio.h>

static void (*Timer1ms_Callback)(void) =
    NULL; // Pointer to the callback function

void Timer1ms_Init(void) {
  // Set CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);

  // Set prescaler to 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Set compare match register for 1 ms interrupts
  OCR1A = 249;

  // Enable compare match interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable global interrupts
  sei();
}

void Timer1ms_SetCallback(void (*callback)(void)) {
  Timer1ms_Callback = callback;
}

// ISR for Timer1 compare match A
ISR(TIMER1_COMPA_vect) {
  if (Timer1ms_Callback != NULL) {
    Timer1ms_Callback(); // Call the user-defined callback
  }
}

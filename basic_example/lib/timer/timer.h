// Timer1ms.h

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Function to initialize Timer1 for 1 ms interrupts
void Timer1ms_Init(void);

// Function to set the callback for the 1 ms interrupt
void Timer1ms_SetCallback(void (*callback)(void));

#endif // TIMER1MS_H


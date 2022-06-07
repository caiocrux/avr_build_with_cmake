/*
 * gpio.c
 *
 * Copyright 2022 Caio Felipe Soares da Cruz <caio.crux@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <avr/io.h>
#include <gpio.h>


void GPIO_Init(void) {
    /* Sets PORT B.5 as an output */
    DDRB |= (1 << PB5);
}
/*
void GPIO_SetHighPort(int port, int pin) {
    SetBit(port, pin);
//  PORTB |= (1 << PB5);
}

void GPIO_SetLowPort(int port, int pin) {
    ClrBit(port, pin);
//    PORTB &= ~(1 << PB5);
}

void GPIO_TogglePort(int port, int pin) {
    PORTB ^= (1 << PB5);
}

void GPIO_GetPort( int port, int pin){
}

*/

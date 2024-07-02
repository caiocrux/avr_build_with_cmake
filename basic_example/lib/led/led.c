/*
 * led.c
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
#include <led.h>
#include <usart.h>
#include <gpio.h>

void Led(Led_Type* const me, LedColors_Type color, LedState_Type state) {
    me->m_color = color;
    me->m_state = state;
    switch (me->m_color) {
        case GREEN:
            if (me->m_state) {
                SetBit(PORTB, PB5);
            } else {
                ClrBit(PORTB, PB5);
              }
        break;
        default:
        break;
    }
}

void LED_setState(Led_Type *const me, LedState_Type state) {
    me->m_state = state;
    // TODO(caio_crux): Remove this part in future.
    // It is the same code of Constructor !
    switch (me->m_color) {
        case GREEN:
            if (me->m_state) {
                SetBit(PORTB, PB5);
            } else {
                ClrBit(PORTB, PB5);
              }

        break;
        default:
        break;
    }
}

LedState_Type LED_getState(Led_Type *const me) {
    return me->m_state;
}

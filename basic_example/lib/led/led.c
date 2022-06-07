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

#include <led.h>
#include <usart.h>

void Led(Led_Type* const me, LedColors_Type color, LedState_Type state){
    me->m_color = color;
    me->m_state = state;
}


void LED_setState(Led_Type *const me, LedState_Type state) {
   me->m_state = state;
}

LedState_Type LED_getState(Led_Type *const me) {
   return me->m_state;
}

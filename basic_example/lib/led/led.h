/** @file led.h
 * 
 * @brief A description of the module’s purpose. 
 *
 * @par       
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

 */ 

#ifndef LIB_LED_LED_H_
#define LIB_LED_LED_H_

#include <stdint.h>
typedef enum {
    RED = 0,
    GREEN,
    YELLOW,
    BLUE
} LedColors_Type;

typedef enum {
    OFF = 0,
    ON
} LedState_Type;


/*  Led's attributes */
typedef struct {
    LedColors_Type m_color;
    LedState_Type m_state;
    uint32_t m_last_update;
} Led_Type;


void Led(Led_Type* const me, LedColors_Type color, LedState_Type state);
void LED_setState(Led_Type *const me, LedState_Type state);
LedState_Type LED_getState(Led_Type *const me);

#endif  //  LIB_LED_LED_H_

/*** end of file ***/


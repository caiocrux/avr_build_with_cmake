/** @file powerled.h                                                                                                                         
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

#ifndef POWERLED_H
#define POWERLED_H

#include <stdint.h>
#include <led.h>

typedef uint8_t led_elec_type;
typedef uint8_t led_dim_type;


typedef enum {
    CURR_LOW = 10, /* 10 mA*/
    CURR_NORMAL = 20,
    CURR_HIGH = 35,
    CURR_VERY_HIGH = 60
}LedCurrent_Type;

typedef enum {
    DIAM_2MM = 2, /* 2 mm */
    DIAM_5MM = 4,
    DIAM_7MM = 7,
}LedDiameter_Type;

typedef enum {
    VOL_LOW = 3, /* 3 Volts */
    VOL_NORMAL = 5,
    VOL_HIGH = 7
}LedVoltage_Type;

/* Power Led attributes */

typedef struct {
    Led_Type super;
    LedCurrent_Type m_current;
    LedDiameter_Type m_diameter;
    LedVoltage_Type m_voltage;
} PowerLed_Type;

/* Constructor */
void PowerLed(PowerLed_Type* const me,
              LedColors_Type color,
              LedColors_Type state,
              LedCurrent_Type current,
              LedDiameter_Type diameter,
              LedVoltage_Type voltage);

/* getters and setters */
void PowerLed_setCurrent(PowerLed_Type* const me, LedCurrent_Type current);
void PowerLed_setDiameter(PowerLed_Type* const me, LedDiameter_Type diameter);
void PowerLed_setVoltage(PowerLed_Type* const me, LedVoltage_Type voltage);
led_dim_type PowerLed_getCurrent(PowerLed_Type* const me);
led_dim_type PowerLed_getDiameter(PowerLed_Type* const me);
led_dim_type PowerLed_getVoltage(PowerLed_Type* const me);

/* Power Led methods */
led_elec_type PowerLed_ComputePower(PowerLed_Type* const me);

#endif /* POWERLED_H */

/*** end of file ***/


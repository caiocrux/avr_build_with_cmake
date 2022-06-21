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
#include <powerled.h>
#include <usart.h>
#include <gpio.h>

void PowerLed(PowerLed_Type* const me, LedColors_Type color,
              LedColors_Type state, LedCurrent_Type current,
              LedDiameter_Type diameter, LedVoltage_Type voltage) {

    /* Inheriting led class */
    Led(&me->super, color, state);
    /*setting attributes */
    me->m_current = current;
    me->m_diameter = diameter;
    me->m_voltage = voltage;
}

void PowerLed_setCurrent(PowerLed_Type* const me, LedCurrent_Type current) {
   me->m_current = current; 
}

void PowerLed_setDiameter(PowerLed_Type* const me, LedDiameter_Type diameter) {
    me->m_diameter = diameter;
}

void PowerLed_setVoltage(PowerLed_Type* const me, LedVoltage_Type voltage) {
    me->m_voltage = voltage;
}

led_dim_type PowerLed_getCurrent(PowerLed_Type* const me) {
    return me->m_current;
}

led_dim_type PowerLed_getDiameter(PowerLed_Type* const me) {
    return me->m_diameter;
}

led_dim_type PowerLed_getVoltage(PowerLed_Type* const me) {
    return me->m_voltage;
}

led_elec_type PowerLed_ComputePower(PowerLed_Type* const me) {
    return (me->m_current * me->m_voltage);
}

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

#define SetBit(RES, BIT)(RES |= (1 << BIT))   // Por BIT em nível alto
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo
#define TstBit(RES, BIT)(RES &  (1 << BIT)) // testar BIT, retorna 0 ou 1
#define CplBit(RES, BIT)(RES ^= (1 << BIT)) // Inverter estado do BIT

void GPIO_Init(void);
/*void GPIO_SetHighPort(int port, int pin);
void GPIO_SetLowPort(int port, int pin);
void GPIO_TogglePort(int port, int pin);
void GPIO_GetPort( int port, int pin);
*/

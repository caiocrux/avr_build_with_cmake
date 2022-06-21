/*
 * @file usart.h
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

#ifndef USART_H
#define USART_H

#include <stdio.h>

typedef enum serial_speed {
	E_BAUD_2400 = 0,
	E_BAUD_4800,
	E_BAUD_9600,
	E_BAUD_14400,
	E_BAUD_19200,
	E_BAUD_28800,
	E_BAUD_38400,
	E_BAUD_57600,
    E_BAUD_1000000
} e_serial_speed;

int USART0_Init(e_serial_speed iSpeed);
void USART0_SendByte(uint8_t u8Data);
uint8_t USART0_ReceiveByte(void);
void USART0_SendString(char* cStringPtr);
void USART0_SendInterger(int iValue);
#endif /* USART_H */

/*** end of file ***/

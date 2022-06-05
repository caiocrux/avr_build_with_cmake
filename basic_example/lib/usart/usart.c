/** @file usart.c
 *
 * @brief A description of the module’s purpose.
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
#include <usart.h>
#include <stdio.h>

int USART0_Init(e_serial_speed iSpeed){
    int iBaudRate = 0;
    // see http://wormfood.net/avrbaudcalc.php to understand iBaudRate values
	switch (iSpeed){
	    case E_BAUD_2400:	UCSR0A |= (1<<U2X0);     iBaudRate = 832; break;
	    case E_BAUD_4800:						     iBaudRate = 207; break;
	    case E_BAUD_9600:						     iBaudRate = 103; break;
	    case E_BAUD_19200:						     iBaudRate =  51; break;
	    case E_BAUD_28800:						     iBaudRate =  34; break;
	    case E_BAUD_38400:						     iBaudRate =  25; break;
	    case E_BAUD_57600:	UCSR0A |= (1<<U2X0);     iBaudRate =  34; break;
	    case E_BAUD_1000000:	UCSR0A |= (1<<U2X0); iBaudRate = 1; break;
	    default : return -1; break;
	}
	UBRR0H = (iBaudRate >> 8) & 0xff;
	UBRR0L = iBaudRate & 0xff;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
    // Turn on the transmission and reception
  	UCSR0B |= (1 << RXEN0 ) | (1 << TXEN0 );
    return 1;
}

void USART0_SendByte(uint8_t u8Data) {
    //wait while previous byte is completed
    while(!(UCSR0A&(1<<UDRE0)));
    // Transmit data
    UDR0 = u8Data;
}
uint8_t USART0_ReceiveByte(void) {
    // Wait for byte to be received
    while(!(UCSR0A&(1<<RXC0)));
    // Return received data
    return UDR0;
}
void USART0_SendString(char* cStringPtr){
	while(*cStringPtr != 0x00) {
        USART0_SendByte(*cStringPtr);
        cStringPtr++;
    }
}


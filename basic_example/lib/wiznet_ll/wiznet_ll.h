/*
 * wiznet_ll.h
 *
 *  Created on: 2 July 2024
 *      Author: Caio Felipe Cruz 
 */

#ifndef WIZNET_LL_H_
#define WIZNET_LL_H_
#include <stdint.h>
#include <avr/io.h>

// Define SPI pin configuration for Arduino Uno
#define SS_PIN PB2   // Arduino Uno digital pin 10
#define MOSI_PIN PB3 // Arduino Uno digital pin 11
#define MISO_PIN PB4 // Arduino Uno digital pin 12
#define SCK_PIN PB5  // Arduino Uno digital pin 13

void cs_sel(void);
void cs_desel(void);
uint8_t spi_rb(void);
void spi_wb(uint8_t b);
void initWiznetSPI(void);
#endif /* WIZNET_LL_H_ */

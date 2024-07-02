#include "wiznet_ll.h"
#include <stdint.h>

void cs_sel(void) {
  // Set SS (PB2) low to select W5100
  PORTB &= ~(1 << SS_PIN); // Set SS (PB2) low to select W5100
}

void cs_desel(void) {
  // Set SS (PB2) high to deselect W5100
  PORTB |= (1 << SS_PIN); // Set SS (PB2) high to deselect W5100
}

uint8_t spi_rb(void) {
    SPDR = 0xFF; // Start transmission, send dummy byte
    while (!(SPSR & (1 << SPIF))); // Wait for transmission complete
    return SPDR; // Return received data
}

void spi_wb(uint8_t b) {
  // Start transmission
  SPDR = b;
  // Wait for transmission complete
  while (!(SPSR & (1 << SPIF)));
}

void initWiznetSPI(void) {
    // Set MOSI (PB3), SCK (PB5), and SS (PB2) as outputs
    DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
    // Enable SPI, Master mode, clock rate fosc/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

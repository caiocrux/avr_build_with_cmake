/* Example of CMake usage with AVR. Shows how to add lib directories and  include in main program */
#include <avr/io.h>
#include <blink.h>
#include <wait.h>
#include <usart.h>

int main(void) {
    USART0_Init(E_BAUD_1000000);
    USART0_SendString("Hello World !!\r\n");
	/* Sets PORT B.5 as an output */
    DDRB |= (1 << PB5);
    while(1){
        blink();
        wait();
        USART0_SendByte(USART0_ReceiveByte());
    }
}

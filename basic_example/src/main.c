/* Example of CMake usage with AVR. Shows how to add lib directories and  include in main program */
#include <avr/io.h>
#include <util/delay.h>

#include <usart.h>
#include <led.h>
#include <gpio.h>

int main(void) {
    //GPIO_Init();
    USART0_Init(E_BAUD_1000000);
    Led_Type arduino_led = {0};
    Led(&arduino_led,GREEN, OFF);
    USART0_SendString("Hello World !!\r\n");
    while(1) {
        LED_setState(&arduino_led, ON);
        if(LED_getState(&arduino_led) == ON) {
            USART0_SendString("LED state is ON !\r\n");
        }
        _delay_ms(1000);
        LED_setState(&arduino_led, OFF);
         if(LED_getState(&arduino_led) == OFF) {
            USART0_SendString("LED state is OFF !\r\n");
        }
        
        _delay_ms(1000);
        // USART0_SendByte(USART0_ReceiveByte());
//        GPIO_TogglePort(1,1);
    }
}

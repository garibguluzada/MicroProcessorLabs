#define F_CPU 16000000UL                 
#include <avr/io.h>                      

void uart_init() {                      // initialize UART (RX only)
    uint16_t ubrr = 103;                // UBRR value for 9600 baud
    UBRR0H = (uint8_t)(ubrr >> 8);       
    UBRR0L = (uint8_t)(ubrr & 0xFF);     
    UCSR0B = (1 << RXEN0);               // enable UART receiver only
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

uint8_t uart_receive() {                
    while (!(UCSR0A & (1 << RXC0)));     
    return UDR0;                         
}

int main(void) {
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4);      // set PD2, PD3, PD4 as outputs (LEDs)

    uart_init();                         

    uint8_t last_val = 0;                

    while (1) {                          
        uint8_t val = uart_receive();    // receive command from master

        if (val == '1' || val == '2' || val == '3') {        // validate received command

            if (val != last_val) {                         // update only if command changed
                last_val = val;                           // save new command

                PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4)); // turn off all LEDs

                if (val == '1')                            // command 1 selected
                    PORTD |= (1 << PD2);                  // turn on LED on PD2
                else if (val == '2')                     // command 2 selected
                    PORTD |= (1 << PD3);                // turn on LED on PD3
                else if (val == '3')                   // command 3 selected
                    PORTD |= (1 << PD4);              // turn on LED on PD4
            }
        }
    }
}
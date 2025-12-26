#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU/16/BAUD)-1)

#include <avr/io.h>

void uart_init() {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE & 0xFF);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8-bit data
}

void uart_transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

uint8_t uart_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

int main(void) {
    uart_init();

    while (1) {
        uint8_t val = uart_receive();      // read from PC terminal

        // valid inputs: 1,2,3,4
        if (val == '1' || val == '2' || val == '3' || val == '4') {
            uart_transmit(val);            // send to slave
        }
    }
}
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t digit = 0;
volatile uint8_t paused = 0;


const uint8_t segTable[10][2] = {
    {0b11110000, 0b00000011}, // 0
    {0b01100000, 0b00000000}, // 1
    {0b10110000, 0b00000101}, // 2
    {0b11110000, 0b00000100}, // 3
    {0b01100000, 0b00000110}, // 4
    {0b11010000, 0b00000110}, // 5
    {0b11010000, 0b00000111}, // 6
    {0b01110000, 0b00000000}, // 7
    {0b11110000, 0b00000111}, // 8
    {0b11110000, 0b00000110}  // 9
};

void displayDigit(uint8_t n)
{
    PORTD = (PORTD & 0x0F) | segTable[n][0];
    PORTB = (PORTB & 0xF0) | segTable[n][1];
}

ISR(TIMER1_COMPA_vect)
{
    if (!paused) {
        digit++;
        if(digit > 9) digit = 0;
        displayDigit(digit);
    }
}

ISR(INT0_vect)
{
    paused = !paused;
}

void timer1_init()
{
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12);
    OCR1A = 31250;
    TIMSK1 |= (1 << OCIE1A);
}

void external_interrupt_init()
{
    DDRD &= ~(1 << PD2); 
    PORTD |= (1 << PD2); 

    EICRA |= (1 << ISC01); 
    EICRA &= ~(1 << ISC00);

    EIMSK |= (1 << INT0); 
}

int main(void)
{
    DDRD |= 0xF0; 
    DDRB |= 0x0F; 

    PORTD &= ~0xF0; 
    PORTB &= ~0x0F;

    displayDigit(0);        
    timer1_init();            
    external_interrupt_init(); 
    sei();                   

    while(1) { }               
}

#include <avr/io.h>
#include <Arduino.h>             

void SPI_SlaveInit(void)                           // initialize SPI in slave mode
{
    DDRB |= (1 << DDB4);                         // set MISO as output
    SPCR = (1 << SPE);
}

uint8_t SPI_SlaveReceive(void)  
{
    while (!(SPSR & (1 << SPIF)));                  // wait until data is received
    return SPDR;                                  // return received data
}

void setup()
{
    Serial.begin(9600);                       // initialize serial communication
    SPI_SlaveInit();                         // initialize SPI slave
}

void loop()
{
    uint8_t received = SPI_SlaveReceive();               // receive data from master

    Serial.print("Received: ");                         // print label
    Serial.println(received);                          // print received value
}
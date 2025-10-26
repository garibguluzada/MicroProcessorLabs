#include <avr/io.h>
#include <avr/eeprom.h>
#include <Arduino.h>

const int buttonPin = 2;
volatile int counter = 0;

void EEPROMWriteInt(int address, int value) {
  // wait for previous write to finish
  while (EECR & (1 << EEPE));
  EEAR = address;        // set EEPROM address
  EEDR = (value & 0xFF); // low byte
  EECR |= (1 << EEMPE);  // master write enable
  EECR |= (1 << EEPE);   // start write

  while (EECR & (1 << EEPE));  // wait again
  EEAR = address + 1;          // high byte
  EEDR = (value >> 8) & 0xFF;
  EECR |= (1 << EEMPE);
  EECR |= (1 << EEPE);
}

int EEPROMReadInt(int address) {
  while (EECR & (1 << EEPE));
  EEAR = address;        // low byte
  EECR |= (1 << EERE);   // start read
  byte low = EEDR;

  while (EECR & (1 << EEPE));
  EEAR = address + 1;    // high byte
  EECR |= (1 << EERE);
  byte high = EEDR;

  return (high << 8) | low;
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  counter = EEPROMReadInt(0);

  if (counter < 0 || counter > 10000) {
    counter = 0;
    EEPROMWriteInt(0, counter);
  }

  Serial.print("Starting counter from EEPROM: ");
  Serial.println(counter);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // button pressed
    counter++;
    EEPROMWriteInt(0, counter);
    Serial.print("Counter: ");
    Serial.println(counter);
    delay(500);  // crude debounce
  }
}

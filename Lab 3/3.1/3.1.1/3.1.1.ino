#define LED PB5   // Pin 13 = Port B, Bit 5

void setup() {
  // Set PB5 (LED pin) as output
  DDRB |= (1 << LED);
}

void loop() {
  PORTB = 0b00100000;  // LED ON (PB5 = 1, others = 0)
  delay(500);
  PORTB = 0b00000000;  // LED OFF (all Port B = 0)
  delay(500);

}

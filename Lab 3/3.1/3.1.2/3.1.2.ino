#define LED PB5   // Pin 13 = Port B, Bit 5

void setup() {
  // Set PB5 (LED pin) as output
  DDRB |= (1 << LED);
}

void loop() {
  PORTB |= (1 << LED);   // LED ON (set bit 5, leave others unchanged)
  delay(500);
  PORTB &= ~(1 << LED);  // LED OFF (clear bit 5, leave others unchanged)
  delay(500);

}

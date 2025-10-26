#define LED PB5

void setup() {
  DDRB |= (1 << LED);
}

void loop() {
  PORTB |= (1 << (0 + 5));
  delay(70);
  PORTB &= ~(1 << (0 + 5));
  delay(70);
}

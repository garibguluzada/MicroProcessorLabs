#define LED PB5

void setup() {
  DDRB |= (1 << LED);
}
void loop() {
  PORTB ^= (1 << LED);  
  delay(50);
  PORTB ^= (1 << LED);
  delay(50);
}

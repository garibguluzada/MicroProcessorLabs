void setup() {
  DDRB |= (1 << DDB5);
}

void loop() {
  PORTB |= (1 << PORTB5);
  delay(500);
  PORTB &= ~(1 << PORTB5);
  delay(500);
} 

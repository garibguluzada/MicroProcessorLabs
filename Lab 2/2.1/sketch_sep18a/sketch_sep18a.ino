void setup() {
  DDRB |= (1 << DDB5); 
  DDRD &= ~(1 << DDD2); 
}

void loop() {
 if (PIND & (1 << PIND2)) {  
    PORTB ^= (1 << PORTB5);     
    delay(500);                 
    }
}

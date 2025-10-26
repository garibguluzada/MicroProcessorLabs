#define LED1 9    // Timer1 - slow blink
#define LED2 13   // Software blink
#define LED3 3    // Timer2 - fast blink

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // ===== TIMER1 (16-bit) → LED1 =====
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 15624;                       // ~1 Hz
  TCCR1B |= (1 << WGM12);               // CTC
  TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler 1024
  TIMSK1 |= (1 << OCIE1A);              // interrupt enable

  // ===== TIMER2 (8-bit) → LED3 =====
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A  = 195;                         // ~10 Hz
  TCCR2A |= (1 << WGM21);               // CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21);  // prescaler 256
  TIMSK2 |= (1 << OCIE2A);              // interrupt enable

  // fully disconnect OC2 pins (make sure no hardware overrides)
  TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1) | (1 << COM2B0) | (1 << COM2B1));

  sei();  // enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
  static bool s1 = 0;
  s1 = !s1;
  digitalWrite(LED1, s1);
}

ISR(TIMER2_COMPA_vect) {
  static bool s3 = 0;
  s3 = !s3;
  digitalWrite(LED3, s3);
}

void loop() {
  // Software blink for LED2 (pin 13)
  static unsigned long lastToggle = 0;
  if (millis() - lastToggle > 500) {
    digitalWrite(LED2, !digitalRead(LED2));
    lastToggle = millis();
  }
}

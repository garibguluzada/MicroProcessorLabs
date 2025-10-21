void setup() {
  Serial.begin(9600);

  uint8_t R12 = 5;
  uint8_t R13 = 8;
  uint8_t R18;

  R18 = R12 + R13;

  Serial.print("Result (R18) = ");
  Serial.println(R18);
}

void loop() {
}

void setup() {
  Serial.begin(9600);

  uint8_t X = 50;
  uint8_t Y = 200;
  uint8_t R18;

  R18 = X - Y; 

  Serial.print("Result (R18) = ");
  Serial.println(R18);

  // Simulating flags:
  if (R18 == 0) {
    Serial.println("Zero flag (Z) = 1");
  } else {
    Serial.println("Zero flag (Z) = 0");
  }

  if (X < Y) {
    Serial.println("Carry flag (C) = 1 (borrow occurred)");
  } else {
    Serial.println("Carry flag (C) = 0");
  }
}

void loop() { }

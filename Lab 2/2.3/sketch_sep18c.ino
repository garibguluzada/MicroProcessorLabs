void setup() {
  Serial.begin(9600);
  while (!Serial) { } // wait for Serial on some boards
  delay(200);

  uint8_t sreg_val = 0;
  uint8_t r18_val = 0;

  asm volatile (
    // load immediates into registers r18 and r19 (allowed with LDI r16..r31)
    "ldi r18, %[vx]\n\t"
    "ldi r19, %[vy]\n\t"
    // subtract r19 from r18 -> result in r18; SREG updated
    "sub r18, r19\n\t"
    // read SREG into a compiler output register
    "in %[sreg_out], __SREG__\n\t"
    // move r18 into a compiler output register so we can print it
    "mov %[r18_out], r18\n\t"
    : [sreg_out] "=r" (sreg_val), [r18_out] "=r" (r18_val)    // outputs
    : [vx] "i" (50), [vy] "i" (200)                           // inputs (immediates)
    : "r18", "r19"                                            // clobbered registers
  );

  // SREG bit positions (ATmega328P etc):
  // bit 1 -> Z (Zero)
  // bit 0 -> C (Carry)
  bool Zflag = (sreg_val & (1 << 1)) != 0;
  bool Cflag = (sreg_val & (1 << 0)) != 0;

  Serial.print("R18 (result) = ");
  Serial.println(r18_val);        // expected 106 (50 - 200 modulo 256)

  Serial.print("SREG = 0b");
  for (int i = 7; i >= 0; --i) {
    Serial.print((sreg_val >> i) & 1);
  }
  Serial.println();

  Serial.print("Zero flag (Z) = ");
  Serial.println(Zflag ? 1 : 0);

  Serial.print("Carry flag (C) = ");
  Serial.println(Cflag ? 1 : 0);
}

void loop() {}

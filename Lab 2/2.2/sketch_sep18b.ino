void setup() {
  Serial.begin(9600);
  uint8_t result;

  asm volatile(
    "ldi r12, 5      \n\t"
    "ldi r13, 8      \n\t"
    "mov r18, r12    \n\t"
    "add r18, r13    \n\t"
    "sts %[res], r18 \n\t"   // store r18 into 'result' variable
    : [res] "=m" (result)    // output
    :                        // no input
    : "r12", "r13", "r18"    // clobbered registers
  );

  Serial.print("Result (R18) = ");
  Serial.println(result);   // should print 13
}

void loop() {}

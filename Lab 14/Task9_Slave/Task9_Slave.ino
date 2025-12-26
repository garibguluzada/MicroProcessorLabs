#define SECRET_KEY 0x5A              
uint8_t decrypt(uint8_t cipher, uint8_t counter) { 
  uint8_t keystream = SECRET_KEY ^ counter;        
  return cipher ^ keystream;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() >= 2) {                         // wait for cipher + counter
    uint8_t cipher = Serial.read();                     // read ciphertext
    uint8_t ctr    = Serial.read();                    // read counter

    uint8_t plain = decrypt(cipher, ctr);                  // decrypt

    Serial.print("Decrypted value: ");
    Serial.println(plain);                                   // display plaintext
  }
}
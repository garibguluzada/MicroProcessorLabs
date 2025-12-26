#define SECRET_KEY 0x5A                 // secret key for XOR decryption

uint8_t decrypt(uint8_t cipher) {       // simple XOR decryption function
  return cipher ^ SECRET_KEY;          
}

void setup() {
  Serial.begin(9600);                   
}

void loop() {
  if (Serial.available() > 0) {                           // check if data is available
    uint8_t cipher = Serial.read();                      // read encrypted byte from UART

    uint8_t plain = decrypt(cipher);                    // decrypt received data

    Serial.print("Decrypted value: ");                     // print label
    Serial.println(plain);                                 // print decrypted value
  }
}
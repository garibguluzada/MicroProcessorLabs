#define SECRET_KEY 0x5A              

uint8_t counter = 0;                                     // counter used for CTR mode

uint8_t encrypt(uint8_t plain) {                        //encryption
  uint8_t keystream = SECRET_KEY ^ counter;             // generate keystream byte
  return plain ^ keystream;                             // XOR plaintext with keystream
}

void setup() {
  Serial.begin(9600);                                // initialize UART
}

void loop() {
  uint8_t plaintext = counter;      
  uint8_t ciphertext = encrypt(plaintext);                   // encrypt using CTR mode

  Serial.write(ciphertext);                                       // send encrypted byte
  Serial.write(counter);                                     // send counter value

  counter++;                                                  // increment counter

  delay(100);                                                  // 0.1 second delay
}

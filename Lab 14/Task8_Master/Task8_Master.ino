#define SECRET_KEY 0x5A                  

uint8_t counter = 0;                    // counter value to be encrypted and sent

uint8_t encrypt(uint8_t plain) {        // simple XOR encryption function
  return plain ^ SECRET_KEY;            // encrypt plaintext using XOR
}

void setup() {
  Serial.begin(9600);                   // initialize UART serial communication
}

void loop() {
  uint8_t plaintext = counter;          // use counter as plaintext data
  uint8_t ciphertext = encrypt(plaintext);              // encrypt plaintext
  Serial.write(ciphertext);                          // send encrypted byte over UART
  counter++;                                            // increment counter for next send
  delay(100);                                             // delay 0.1 seconds 
}

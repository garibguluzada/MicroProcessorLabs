#include <Wire.h>

#define SLAVE_ADDR 0x08                  // I2C slave address
#define NUM_MESSAGES 50                  // number of messages to send

void setup() {
  Serial.begin(9600);                    // initialize serial communication

  TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); // set I2C prescaler to 1

  // TWBR = 312;                         // 25 kHz I2C clock
  // TWBR = 72;                          // 100 kHz I2C clock
  // TWBR = 12;                          // 400 kHz I2C clock

  Wire.begin();                          // initialize I2C as master
}

void loop() {
  unsigned long startTime = millis();    // record start time

  for (int i = 0; i < NUM_MESSAGES; i++) { 

    Wire.beginTransmission(SLAVE_ADDR);         // start transmission to slave
    Wire.write(1);                              // send dummy data
    Wire.endTransmission();                          // end transmission

    Wire.requestFrom(SLAVE_ADDR, 1);    
    while (Wire.available()) {          // wait for received data
      Wire.read();                      // read received byte
    }
  }

  unsigned long endTime = millis();      

  Serial.print("Time for 50 messages: "); 
  Serial.print(endTime - startTime);             // calculate elapsed time
  Serial.println(" ms");                        // print time unit

  delay(3000);                                 // wait before next measurement
}
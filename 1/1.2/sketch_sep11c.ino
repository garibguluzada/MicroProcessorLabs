void setup() {
  // put your setup code here, to run once:
  DDRB |= (1 << DDB5);
}

void loop() {
  // put your main code here, to run repeatedly:
 PORTB |= (1 << PORTB5);
 delay(25);

 PORTB &= ~(1<<PORTB5);
 delay(25);
}
//maximum bytes =2048   storgae space =640 byte,Maximum is 32256 bytes.


//Sketch uses 924 bytes (2%) of program storage space. Maximum is 32256 bytes.
//Global variables use 9 bytes (0%) of dynamic memory, leaving 2039 bytes for local variables. Maximum is 2048 bytes.

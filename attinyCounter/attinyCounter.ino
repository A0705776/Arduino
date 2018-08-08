/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
#define clk 1
#define input 2
#define rst 0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(clk, OUTPUT);
  pinMode(input, OUTPUT);
  pinMode(rst, OUTPUT);
  digitalWrite(rst, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0; i < 256; i++){
    shift_8_bit(i);
    delay(1000);
  } 
}

void shift_8_bit(int value){
  digitalWrite(input, (value & 128));
  clk_pulse();
  digitalWrite(input, (value & 64));
  clk_pulse();
  digitalWrite(input, (value & 32));
  clk_pulse();
  digitalWrite(input, (value & 16));
  clk_pulse();
  digitalWrite(input, (value & 8));
  clk_pulse();
  digitalWrite(input, (value & 4));
  clk_pulse();
  digitalWrite(input, (value & 2));
  clk_pulse();
  digitalWrite(input, (value & 1));
  clk_pulse();
}
void clk_pulse(){
  digitalWrite(clk, HIGH);
  delayMicroseconds(1);
  digitalWrite(clk, LOW); 
  delayMicroseconds(1);
}

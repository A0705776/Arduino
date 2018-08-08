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
#define ledLamp 3
#define moon 1
#define stars 4
#define stars2 0

int lamp = 0;
int star = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledLamp, OUTPUT);
  pinMode(moon, OUTPUT);
  pinMode(stars, OUTPUT);
  pinMode(stars2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0; i < 255; i++){
    analogWrite(moon, i);
    analogWrite(stars2, 255 - i);
    delay(100);
    lamp++;
    if(lamp > 5) {
      toggleLamp();
      lamp = 0;
    }
    star++;
    if(star > 7) {
      toggleLamp();
      toggleStar();
      star = 0;
    }
  }
  for(int i = 255; i > 0; i--){
    analogWrite(moon, i);
    analogWrite(stars2, 255 - i);
    delay(100);
    lamp++;
    if(lamp > 5) {
      toggleLamp();
      lamp = 0;
    }
    star++;
    if(star > 7) {
      toggleLamp();
      toggleStar();
      star = 0;
    }
  }
}
void toggleStar(){
  if(digitalRead(stars) == HIGH)
    digitalWrite(stars, LOW); 
  else digitalWrite(stars, HIGH);
}

void toggleLamp(){
  if(digitalRead(ledLamp) == HIGH)
    digitalWrite(ledLamp, LOW); 
  else digitalWrite(ledLamp, HIGH);
}

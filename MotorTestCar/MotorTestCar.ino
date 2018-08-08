// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(4);
AF_DCMotor motorR(2);
//............................................................................

int right = 0;
int left = 1;
int r = 0;
int l = 0;
int sR = 0;
int sL = 0;
boolean highR = false;
boolean lowR = false;
boolean highL = false;
boolean lowL = false;
//.............................................................................



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  pinMode(right, INPUT);
  pinMode(left, INPUT);

  // turn on motor............................................................
  motor.setSpeed(200);
  motorR.setSpeed(200);
  motor.run(RELEASE);
  motorR.run(RELEASE);
  //..........................................................................

}

void car(){}

void loop() {
  uint8_t i;
  
  motor.run(FORWARD);
  motorR.run(FORWARD);

  motor.setSpeed(255-sR);
  motorR.setSpeed(255-sL); 
 
   

  //................................................................................
  sR++;
  //................................................................................
  if(r == 20){
    double z = sR;
   Serial.print("Right "); Serial.println(z);
   r = 0;
   sR = 0;
  }
  if(analogRead(right) > 700 && lowR == false && highR == false){
    highR = true;
  }
  if(highR == true && lowR == false && analogRead(right) < 400){
    lowR = true;
  }
  if(lowR == true && highR == true){
    r++;
    highR = false;
    lowR = false;
  }
  //..................................................................................
  sL++;
  //..................................................................................
  if(l == 20){
    double p = sL;
    Serial.print("Left "); Serial.println(p);
   l = 0;
   sL = 0;
  }
  if(analogRead(left) > 700 && lowL == false && highL == false){
    highL = true;
  }
  if(highL == true && lowL == false && analogRead(left) < 400){
    lowL = true;
  }
  if(lowL == true && highL == true){
    l++;
    highL = false;
    lowL = false;
  }
  
  // put your main code here, to run repeatedly: 
  
  delay(1);
  
}

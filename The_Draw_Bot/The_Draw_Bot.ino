#include <Servo.h>
#include "Draw_Bot.h"

Servo myservo_bottom;     // create servo object to control a servo 
Servo myservo_top;        // create servo object to control a servo
Servo myservo_pen;        // create servo object to control a servo

void setup() 
{ 
  setup_servo();
  
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sweep_bottom();
  delay(20);
} 
void sweep_bottom(){
  int i;
  for(i = 0;i<50;i++){
    myservo_bottom.write(pos_bottom+i);
    delay(20);
  }
  //myservo_pen.write(pos_pen-30);
  //delay(200);
  for(;i>0;i--){
    myservo_bottom.write(pos_bottom+i);
    delay(20);
  }
  //myservo_pen.write(pos_pen);
  //delay(200);
}
void setup_servo(){
  myservo_bottom.attach(9);        // attaches the bottom servo on pin 9 to the servo object 
  myservo_top.attach(10);          // attaches the top servo on pin 10 to the servo object 
  myservo_pen.attach(11);          // attaches the pen servo on pin 11 to the servo object
  
  myservo_pen.write(pos_pen); 
  myservo_top.write(pos_top); 
  myservo_bottom.write(pos_bottom);
}


#include <Servo.h>

unsigned long echo = 0;
int ultraSoundTrig = 9; // Ultrasound signal pin
int ultraSoundEcho = 8; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;

//pin 10 is the servo

Servo myservo;


void setup()
{
  Serial.begin(9600);
  pinMode(ultraSoundTrig,INPUT);
  pinMode(ultraSoundEcho,OUTPUT);
  myservo.attach(10);
}

unsigned long ping()
{ 
  //pinMode(ultraSoundTrig, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundEcho, LOW); // Send low pulse 
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundEcho, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundEcho, LOW); // Holdoff
  //pinMode(ultraSoundTrig, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundTrig, HIGH); // Turn on pullup resistor
  // please note that pulseIn has a 1sec timeout, which may
  // not be desirable. Depending on your sensor specs, you
  // can likely bound the time like this -- marcmerlin
  //echo = pulseIn(ultraSoundTrig, HIGH, 28000);
  echo = pulseIn(ultraSoundTrig, HIGH); //Listen for echo
  ultrasoundValue = (echo / 58.138) * .39; //convert to CM then to inches
  return ultrasoundValue;
}

void loop()
{
  int x = 0;
  x = ping();
  Serial.println(x);
//  if(x > 1 && x < 60 && x != 31 & x != 32 & x != 33){
//    for(int i = 130; i > 70 ;i--){
//      myservo.write(i);
//      delay(15);
//    }
//    Serial.println("High");
//    delay(5000);
//    
//  }else if(x < 2000){
//    Serial.println("LOW");
//    for(int i = 70; i < 130;i++){
//      myservo.write(i);
//      delay(20);
//    }
//  }
  delay(100);

//  for(int i = 70; i < 130;i++){
//    myservo.write(i);
//    delay(10);
//  }
//  delay(1000); //delay 1/4 seconds.
//  for(int i = 130; i > 70 ;i--){
//    myservo.write(i);
//    delay(10);
//  }
//  delay(1000); //delay 1/4 seconds.
}

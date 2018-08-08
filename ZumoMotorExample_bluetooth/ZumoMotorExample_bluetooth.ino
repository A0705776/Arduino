#include <ZumoMotors.h>

/*
 * This example uses the ZumoMotors library to drive each motor on the Zumo
 * forward, then backward. The yellow user LED is on when a motor should be
 * running forward and off when a motor should be running backward. If a
 * motor on your Zumo has been flipped, you can correct its direction by
 * uncommenting the call to flipLeftMotor() or flipRightMotor() in the setup()
 * function.
 */

#define LED_PIN 13

ZumoMotors motors;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
}

void loop()
{
  // run left motor forward
  
  digitalWrite(LED_PIN, HIGH);
  
  if (Serial.available() > 0) {
    
    int y = Serial.read();
    Serial.write(y);
      if (y == 'f'){
        motors.setLeftSpeed(200);
        motors.setRightSpeed(200);
        Serial.write("Forward");
        delay(2000);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        y=0;
      }
      if (y == 'r'){
        motors.setLeftSpeed(200);
        motors.setRightSpeed(-200);
        Serial.write("Right");
        delay(500);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        y=0;
      }
      if (y == 'l'){
        motors.setLeftSpeed(-200);
        motors.setRightSpeed(200);
        Serial.write("Left");
        delay(500);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        y=0;
      }
      if (y == 'b'){
        motors.setLeftSpeed(-200);
        motors.setRightSpeed(-200);
        Serial.write("Back");
        delay(2000);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        y=0;
      }
            
  }
    
}

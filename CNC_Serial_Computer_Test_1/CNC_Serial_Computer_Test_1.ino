/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //Serial.setTimeout(50);
  // make the pushbutton's pin an input:
  pinMode(pushButton, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available()){
    String temp = Serial.readStringUntil('\r');
    if(temp == "Hello"){
      Serial.println("Whats Up");
      Serial.flush();
    }else{
      Serial.println("What");
      Serial.flush();
    }
    Serial.read();
//    if(Serial.read() == '1'){
//      digitalWrite(13,HIGH);
//      //delay(100);
//      Serial.println('h');
//      Serial.flush();
//    }
//    else {
//      digitalWrite(13,LOW);
//      //delay(100);
//      Serial.println('l');
//      Serial.flush();
//    }
  }
}




int s = 0;
int ledPin = 9;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(ledPin, OUTPUT);  
  
}

// the loop routine runs over and over again forever:
void loop() {
   int val = analogRead(s);
   
   val = constrain(val, 10, 180);
   int ledLevel = map(val, 10, 180, 255, 0);
   
   analogWrite(ledPin, ledLevel);  
}

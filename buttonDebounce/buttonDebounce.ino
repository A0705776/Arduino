int buttonPin = 8;
int ledPin = 13;

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

boolean debounce(boolean last)
{
 boolean current = digitalRead(buttonPin);
 if (last != current)
{
  delay (5);
  current = digitalRead(buttonPin);
} 
return current;
}

void loop() {
  
  currentButton = debounce(lastButton);
  // put your main code here, to run repeatedly: 
  if (lastButton == LOW && currentButton == HIGH)
  {
    ledOn = !ledOn;
  }
  lastButton = currentButton;
  digitalWrite(ledPin, ledOn);
}


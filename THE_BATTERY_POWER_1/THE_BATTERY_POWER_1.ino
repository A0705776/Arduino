/*
  
 */
float sensorValue = 0;
float OFF_Value = 47;
float ON_Value = 23;
float upperValue = 21.0/16.0;
float lowerValue = 20.0/16.0;

int counter = 0;

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
    
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (3.3 / 1023.0);
    counter++;
    if(counter >= 100){
      Serial.println(voltage);
      Serial.println(OFF_Value);
      Serial.println(ON_Value);
      counter = 0;
    }
    
    if(voltage < lowerValue){
      if(OFF_Value > 47){OFF_Value -= 10;}else{
        OFF_Value = 48;
      }
      if(ON_Value < 23){ON_Value += 1;}else{
        ON_Value = 23;
      }
    
    }else if(voltage > upperValue){
      if(OFF_Value < 200000){OFF_Value += 10;}else{
        OFF_Value = 199999;
      }
      if(ON_Value > 1){ON_Value -= 1;}else{
        ON_Value = 1;
      }
      
    }
      digitalWrite(3,HIGH);
      delayMicroseconds(ON_Value);
      digitalWrite(3,LOW);
      delayMicroseconds(OFF_Value);

}

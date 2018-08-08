/*
  
 */
float sensorValue = 0;
float op = 0;
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
      Serial.println(op);
      counter = 0;
    }
    
    if(voltage < lowerValue){
      if(op < 210){op += 0.01;}else{
        op = 209.99;
      }
    
    }else if(voltage > upperValue){
      if(op > 0){op -= 0.01;}else{
        op = 0.01;
      }
      
    }
      analogWrite(3,op);

}


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
//..............................................................................

boolean x = false;
int motorLeft = 3;
int motorRight = 5;
int motorForwardRight = 8;
int motorForwardLeft = 10;
int motorBackwardRight = 9;
int motorBackwardLeft = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  Serial.begin(9600);
  //............................................................................... 
  
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorForwardRight, OUTPUT);
  pinMode(motorForwardLeft, OUTPUT);
  pinMode(motorBackwardRight, OUTPUT);
  pinMode(motorBackwardLeft, OUTPUT);
  
  
}

void carForward(){
  
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorForwardLeft, HIGH);
  
    
  analogWrite(motorRight, 100-sL); 
  analogWrite(motorLeft,  100-sR);
    

    
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
  delay(1);
  
}

void carForward2(){
  
  digitalWrite(motorForwardRight, HIGH);
  digitalWrite(motorForwardLeft, HIGH);
  
    
  
 
    

    
  //................................................................................
  sR++;
  //................................................................................
  if(r == 5){
   if(l < r){
     analogWrite(motorRight, 30); 
     analogWrite(motorLeft,  100);
   }
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
  if(l == 5){
   if(r < l){
     analogWrite(motorRight, 100); 
     analogWrite(motorLeft,  20);
   }
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
  
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  carForward2();

}

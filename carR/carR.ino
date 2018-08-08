
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

void setup() {
  // put your setup code here, to run once:
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  Serial.begin(9600);
}

void loop() {
  sR++;
  //................................................................................
  if(r == 20){
    double z = sR/1000;
   Serial.print("Right "); Serial.println(z);
   r = 0;
   sR = 0;
  }
  if(analogRead(right) > 900 && lowR == false && highR == false){
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
    double z = sL/1000;
    Serial.print("Left "); Serial.println(z);
   l = 0;
   sL = 0;
  }
  if(analogRead(left) > 900 && lowL == false && highL == false){
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

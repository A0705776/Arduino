/*
  Author: Alamin Ahmed
*/
#define X_busy 2                    //goes high when CNC_X is busy
#define master_ready_X 9            //goes high when Master for X is ready to send info
#define Y_busy 5                    //goes high when CNC_Y is busy
#define master_ready_Y 4            //goes high when Master for Y is ready to send info
#define Z_busy 10                    //goes high when CNC_Z is busy
#define master_ready_Z 7            //goes high when Master is ready to send info

const int Y_DISTANCE_STEP = 16350;  //.. inch
const int X_DISTANCE_STEP = 16250;  //12.8 inch
const unsigned int Z_DISTANCE_STEP = 43500;  //.. inch
static int X_cordinate = 0;         //0 to 16250 (will change depending on the X position)
static int Y_cordinate = 0;         //0 to 16350 (will change depending on the Y position)
static float Z_cordinate = 0;         //0 to 43500 (will change depending on the Z position)
unsigned int Speed_X = 0;
unsigned int Speed_Y = 0;
unsigned int Speed_Z = 0;
unsigned int X;
unsigned int Y;
float Z;
unsigned int Speed;

void setup() {
  Serial.println("SETUP");
  initialize();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.println("END_SETUP");
  delay(1000);
  Serial.println("CAL");
  calibrate_sequence();
  Serial.println("END_CAL");

  drawLine_y(750, 100);
//  drawLine_z(41600, 100);
//  delay(300);
//  drawLine(8000,10000,100);
//  delay(300);
//  drawLine(5000,1000,100);
//  delay(300);
//  drawLine(0,750,100);
  //  drawLine_y(10000,100);
  //  drawLine_x(8000,100);
  //  drawLine_y(750,100);
  //  drawLine_x(0,100);
}

void loop() {
    if(Serial.available()){
      String temp = Serial.readStringUntil('\r');
      Serial.read();
      if(temp == "RAW"){
        //while(!Serial.available());
        while(true){
          //while(!Serial.available());
//          if(Serial.peek()== 'E'){
//            Serial.read();
//            Serial.println("BREAK");
//            break;
//          }
          Serial.readStringUntil('\r');
          Serial.read();
          while(!Serial.available());
          
          X = Serial.parseInt();
          Serial.println("E1");

          Y = Serial.parseInt();
          Serial.println("E2");
          

          Z = Serial.parseFloat();
          Serial.println("E3");
          
          Speed = Serial.parseInt();

          
          draw(X,Y,Z,Speed);
          Serial.println("END");
          Serial.flush();
        }
      }else{
        Serial.println("HMM");
        Serial.flush();
      }
    }
}
void draw(unsigned int x, unsigned int y, float z, unsigned int Speed){
  X_cordinate = x;
  Y_cordinate = y;
  Z_cordinate = z;
  while (digitalRead(Y_busy) == HIGH || digitalRead(X_busy) == HIGH || digitalRead(Z_busy) == HIGH) {
    /*infinite loop*/
  }
  Serial1.println(x);
  Serial1.println(Speed);
  Serial2.println(y);
  Serial2.println(Speed);
  Serial3.println(z);
  Serial3.println(Speed);
  digitalWrite(master_ready_X, HIGH);
  digitalWrite(master_ready_Y, HIGH);
  digitalWrite(master_ready_Z, HIGH);
  while (digitalRead(Z_busy) == LOW || digitalRead(Y_busy) == LOW || digitalRead(X_busy) == LOW) {
    /*infinite loop*/
  }
  digitalWrite(master_ready_X, LOW);
  digitalWrite(master_ready_Y, LOW);
  digitalWrite(master_ready_Z, LOW);

}
void calibrate_sequence() {
  delay(10);
  while (digitalRead(Z_busy) == HIGH) {
    /*infinite loop*/Serial.println("Z_HIGH");
  }
  digitalWrite(master_ready_X, HIGH);
  digitalWrite(master_ready_Y, HIGH);
  while (digitalRead(Y_busy) == LOW || digitalRead(X_busy) == LOW) {
    /*infinite loop*/Serial.println("XY_LOW");
  }
  digitalWrite(master_ready_X, LOW);
  digitalWrite(master_ready_Y, LOW);
}
void initialize() {
  pinMode(X_busy, INPUT);
  digitalWrite(master_ready_X, LOW);
  pinMode(master_ready_X, OUTPUT);
  pinMode(Y_busy, INPUT);
  digitalWrite(master_ready_Y, LOW);
  pinMode(master_ready_Y, OUTPUT);
  pinMode(Z_busy, INPUT);
  digitalWrite(master_ready_Z, LOW);
  pinMode(master_ready_Z, OUTPUT);
}

void drawLine(int x, int y, unsigned int Speed) {
  int temp_x = x - X_cordinate, temp_y = y - Y_cordinate;
  X_cordinate = x; Y_cordinate = y;

  unsigned int Speed_real = Speed;
  double Speed_delay = 0;
  if (temp_x == 0 || temp_y == 0) {
    Speed_delay = 1;
  } else {
    Speed_delay = double(max(abs(temp_x), abs(temp_y))) / min(abs(temp_x), abs(temp_y));
    while((Speed_real*Speed_delay - int(Speed_real*Speed_delay)) != 0.0){
      Speed_real++;
      //Serial.println(Speed_real);
    }
  }
  
  unsigned int Speed_diff = 100;
  if ((Speed_real * Speed_delay) >= (int(Speed_real * Speed_delay) + 0.5)) {
    Speed_diff = int(Speed_real * Speed_delay) + 1;
  } else {
    Speed_diff = int(Speed_real * Speed_delay);
  }

  if (abs(temp_x) > abs(temp_y)) {
    Speed_X = Speed_real;
    Speed_Y = Speed_diff;
  } else {
    Speed_X = Speed_diff;
    Speed_Y = Speed_real;
  }
  
  while (digitalRead(Y_busy) == HIGH || digitalRead(X_busy) == HIGH) {
    /*infinite loop*/
  }
  Serial1.println(x);
  Serial1.println(Speed_X);
  Serial2.println(y);
  Serial2.println(Speed_Y);
  digitalWrite(master_ready_X, HIGH);
  digitalWrite(master_ready_Y, HIGH);
  while (digitalRead(Y_busy) == LOW || digitalRead(X_busy) == LOW) {
    /*infinite loop*/
  }
  digitalWrite(master_ready_X, LOW);
  digitalWrite(master_ready_Y, LOW);
}
void drawLine_z(unsigned int z, unsigned int Speed) {
  Z_cordinate = z;
  while (digitalRead(Z_busy) == HIGH) {
    /*infinite loop*/
  }
  Serial3.println(z);
  Serial3.println(Speed);
  digitalWrite(master_ready_Z, HIGH);
  while (digitalRead(Z_busy) == LOW) {
    /*infinite loop*/
  }
  digitalWrite(master_ready_Z, LOW);
  while (digitalRead(Z_busy) == HIGH) {
    /*infinite loop*/
  }
}
void drawLine_y(int y, unsigned int Speed) {
  Y_cordinate = y;
  while (digitalRead(Y_busy) == HIGH) {
    /*infinite loop*/
  }
  Serial2.println(y);
  Serial2.println(Speed);
  digitalWrite(master_ready_Y, HIGH);
  while (digitalRead(Y_busy) == LOW) {
    /*infinite loop*/
  }
  digitalWrite(master_ready_Y, LOW);
//  while (digitalRead(Y_busy) == HIGH) {
//    /*infinite loop*/
//  }
}
void drawLine_x(int x, unsigned int Speed) {
  X_cordinate = x;
  while (digitalRead(X_busy) == HIGH) {
    /*infinite loop*/
  }
  Serial1.println(x);
  Serial1.println(Speed);
  digitalWrite(master_ready_X, HIGH);
  while (digitalRead(X_busy) == LOW) {
    /*infinite loop*/
  }
  digitalWrite(master_ready_X, LOW);
//  while (digitalRead(X_busy) == HIGH) {
//    /*infinite loop*/
//  }
}

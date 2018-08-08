/*
Author: Alamin Ahmed
*/
#define up_X_step_pin 3             //up stepper motor for X axis
#define down_X_step_pin 4           //down stepper motor for X axis
#define X_direction_pin 5           //HIGH = left (X axis direction)
#define left HIGH                   //x direction left
#define right LOW                   //x direction right
#define up_right_X_sensor_pin 6     //up right sensor for X axis
#define down_right_X_sensor_pin 7   //down right sensor for X axis
#define left_X_sensor_pin 8         //left sensor for X axis
#define X_busy 2                    //goes high when CNC_X is busy
#define master_ready 9              //goes high when Master is ready to send info

const int X_DISTANCE_STEP = 16250;  //12.8 inch 
static int X_cordinate = 0;         //0 to 16250 (will change depending on the X position)
unsigned int wait = 100;            //In microsecond (fastest time the stepper motor can funtion properly is 70)
int X = 0;                          //temp placeholder for X_cordinate




void setup() {
  Serial.begin(9600);               //serial communication with the master and the slave
  initialize();                     //set all the pins
  delay(1000);
  calibrate();                      //calibrate and set the 0th position
}

void loop() {
  if(digitalRead(master_ready) == HIGH){
      digitalWrite(X_busy, HIGH);
      X = Serial.parseInt();
      wait = Serial.parseInt();
      moveto_x(X,wait);
  }
}

void moveto_x(int x,unsigned int wait){
    int temp = x - X_cordinate;
    X_cordinate = x;
    if(temp > 0){
      X_direction(left);
      for(int i = 0;i < temp; i++){
        oneStep_x(wait);
      }
      digitalWrite(X_busy, LOW); 
    }else if(temp < 0){
      X_direction(right);
      for(int i = 0;i > temp; i--){
        oneStep_x(wait);
      }
      digitalWrite(X_busy, LOW); 
    }else{
      digitalWrite(X_busy, LOW); 
    }
}

void initialize(){
  pinMode(up_X_step_pin, OUTPUT);
  pinMode(down_X_step_pin, OUTPUT);
  pinMode(X_direction_pin, OUTPUT);
  pinMode(up_right_X_sensor_pin, INPUT);
  pinMode(down_right_X_sensor_pin, INPUT);
  pinMode(left_X_sensor_pin, INPUT);
  digitalWrite(X_busy, LOW);
  pinMode(X_busy, OUTPUT);
  pinMode(master_ready, INPUT);
}

void calibrate(){
  digitalWrite(X_busy, LOW);
  while(digitalRead(master_ready) == LOW){/*infinite loop*/}
  digitalWrite(X_busy, HIGH);
  X_direction(right);
  delay(10);
  while(digitalRead(up_right_X_sensor_pin) == LOW || digitalRead(down_right_X_sensor_pin) == LOW ){
    if(digitalRead(up_right_X_sensor_pin) == HIGH || digitalRead(down_right_X_sensor_pin) == HIGH){
      while(digitalRead(up_right_X_sensor_pin) == LOW){
        oneStepUp_x(wait);
      }
      while(digitalRead(down_right_X_sensor_pin) == LOW){
        oneStepDown_x(wait);
      }
    }else{
      oneStep_x(100);
    }
  }
  delay(500);
  digitalWrite(X_busy, LOW);
}

void X_direction(boolean dir){
  digitalWrite(X_direction_pin, dir);
}


void oneStep_x(unsigned int wait){
  digitalWrite(up_X_step_pin, HIGH);   
  digitalWrite(down_X_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(up_X_step_pin, LOW);   
  digitalWrite(down_X_step_pin, LOW);    
  delayMicroseconds(wait);
}
void oneStepUp_x(unsigned int wait){
  digitalWrite(up_X_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(up_X_step_pin, LOW);   
  delayMicroseconds(wait);
}
void oneStepDown_x(unsigned int wait){
  digitalWrite(down_X_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(down_X_step_pin, LOW);   
  delayMicroseconds(wait);
}

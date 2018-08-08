#include <Scheduler.h>

#define up_X_step_pin 3             //up stepper motor for X axis
#define down_X_step_pin 4           //down stepper motor for X axis
#define X_direction_pin 5           //HIGH = left (X axis direction)
#define left HIGH                   //x direction left
#define right LOW                   //x direction right
#define down HIGH                   //y direction down
#define up LOW                      //y direction up
#define up_right_X_sensor_pin 6     //up right sensor for X axis
#define down_right_X_sensor_pin 7   //down right sensor for X axis
#define left_X_sensor_pin 8         //left sensor for X axis
#define Y_step_pin 9                //stepper motor for Y axis
#define Y_direction_pin 10          //Y axis direction ()
#define up_Y_sensor_pin 11          //up sensor for Y axis
#define down_Y_sensor_pin 12        //down seneor for Y axis

const int X_DISTANCE_STEP = 16250;  //12.8 inch 
const int Y_DISTANCE_STEP = 16350;  //.. inch 

int X_cordinate = 0;                //0 to 16250 (will change depending on the X position)
int Y_cordinate = 0;                //0 to 16350 (will change depending on the Y position)
unsigned int wait = 100;             //In microsecond (fastest time the stepper motor can funtion properly is 70)
unsigned int wait_X = 100;
unsigned int wait_Y = 100;
int X = 0;
int Y = 0;
boolean done = true;
boolean done_X = true;
boolean done_Y = true;



void setup() {
  initialize();
  calibrate();
  
  Scheduler.startLoop(loop2);
  Scheduler.startLoop(loop3);
  
  
}

void loop() {
  //drawLine(2000,4000,70);
  //moveto_x(5000,wait_X);
  //moveto_y(5000,wait_Y);
  //yield();
}
void loop2() {
    moveto_x(X,wait_X);
    yield();
}
void loop3() {
    moveto_y(Y,wait_Y);
    yield();
}
void drawLine(int x, int y, unsigned int wait){
  if(done_X == true && done_Y == true){
    int temp_x, temp_y;
    temp_x = x - X_cordinate;
    temp_y = y - Y_cordinate;
    boolean maxX = (abs(temp_x) > abs(temp_y)?true:false);
    double pause = double(max(abs(temp_x),abs(temp_y)))/min(abs(temp_x),abs(temp_y));
    if(maxX){
      wait_X = wait;
      wait_Y = int(wait*pause);
      X = x;
      Y = y;
      delayMicroseconds(wait*2);
    }else{
      wait_X = int(wait*pause);
      wait_Y = wait;
      X = x;
      Y = y;
      delayMicroseconds(wait*2);
    }
  }
}



void moveto_y(int y,unsigned int wait){
  int temp = 0;
  if(y <= Y_DISTANCE_STEP && y >= 0){
    temp = y - Y_cordinate;
    Y_cordinate = y;
    if(temp > 0){
      done_Y = false;
      Y_direction(down);
      for(int i = 0;i < temp; i++){
        oneStep_y(wait);
      }
      done_Y = true;
    }else if(temp < 0){
      done_Y = false;
      Y_direction(up);
      for(int i = 0;i > temp; i--){
        oneStep_y(wait);
      }
      done_Y = true;
    }else{
      done_Y = true;
    }
  }
}

void moveto_x(int x,unsigned int wait){
  int temp = 0;
  if(x <= X_DISTANCE_STEP && x >= 0){
    temp = x - X_cordinate;
    X_cordinate = x;
    if(temp > 0){
      done_X = false;
      X_direction(left);
      for(int i = 0;i < temp; i++){
        oneStep_x(wait);
      }
      done_X = true;
    }else if(temp < 0){
      done_X = false;
      X_direction(right);
      for(int i = 0;i > temp; i--){
        oneStep_x(wait);
      }
      done_X = true;
    }else{
      done_X = true;
    }
  }
}

void test_x(){
  X_direction(left);
  delay(100);
  for(int i =0; i < X_DISTANCE_STEP; i++){
    oneStep_x(70);
  }
}

void test_y(){
  Y_direction(down);
  delay(10);
  for(int i =0; i < 16350; i++){
    oneStep_y(70);
  }
}

void test_x_run(){
  X_direction(right);
  delay(40);
  for(int i =0; i < 5000; i++){
    oneStep_x(60);
  }
  X_direction(left);
  delay(40);
  for(int i =0; i < 5000; i++){
    oneStep_x(60);
  }
}

void test_y_run(){
  Y_direction(down);
  delay(40);
  for(int i =0; i < 5000; i++){
    oneStep_y(60);
  }
  Y_direction(up);
  delay(40);
  for(int i =0; i < 5000; i++){
    oneStep_y(60);
  }
}

void initialize(){
  pinMode(up_X_step_pin, OUTPUT);
  pinMode(down_X_step_pin, OUTPUT);
  pinMode(X_direction_pin, OUTPUT);
  pinMode(up_right_X_sensor_pin, INPUT);
  pinMode(down_right_X_sensor_pin, INPUT);
  pinMode(left_X_sensor_pin, INPUT);
  pinMode(Y_step_pin, OUTPUT);
  pinMode(Y_direction_pin, OUTPUT);
  pinMode(up_Y_sensor_pin, INPUT);
  pinMode(down_Y_sensor_pin, INPUT);
}

void calibrate(){
  X_direction(right);
  Y_direction(up);
  delay(10);
  while(digitalRead(up_right_X_sensor_pin) == LOW || digitalRead(down_right_X_sensor_pin) == LOW || digitalRead(up_Y_sensor_pin) == LOW){
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
    if(digitalRead(up_Y_sensor_pin) == LOW){
      oneStep_y(wait);
    }
  }
  delay(1000);
}

void Y_direction(boolean dir){
  digitalWrite(Y_direction_pin, dir);
}

void X_direction(boolean dir){
  digitalWrite(X_direction_pin, dir);
}

void oneStep_y(unsigned int wait){
  digitalWrite(Y_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(Y_step_pin, LOW);   
  delayMicroseconds(wait);
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

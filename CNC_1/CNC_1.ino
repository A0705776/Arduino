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
int count_X = 0;
int count_Y = 0;
boolean state_X = true;
boolean state_Y = true;


void setup() {
  initialize();
  calibrate();
  
}

void loop() {
  drawLine(2000,12000,70);
  
  
}

void flip_x(){
  if(state_X){
    digitalWrite(up_X_step_pin, HIGH);   
    digitalWrite(down_X_step_pin, HIGH);
    state_X = false;
  }else{
    digitalWrite(up_X_step_pin, LOW);   
    digitalWrite(down_X_step_pin, LOW);
    state_X = true;
    count_X++;
  }
}
void flip_y(){
  if(state_Y){
    digitalWrite(Y_step_pin, HIGH);   
    state_Y = false;
  }else{
    digitalWrite(Y_step_pin, LOW);   
    state_Y = true;
    count_Y++;
  }
}

void drawLine(int x, int y, unsigned int wait){
  int temp_x,temp_y;
  if(y <= Y_DISTANCE_STEP && y >= 0 && x <= X_DISTANCE_STEP && x >= 0){
    temp_x = x - X_cordinate;
    temp_y = y - Y_cordinate;
    
    boolean maxX = (abs(temp_x) > abs(temp_y)?true:false);
    double pause = double(max(abs(temp_x),abs(temp_y)))/min(abs(temp_x),abs(temp_y));
    unsigned long cX = 0, cY = 0;
    
    if(temp_x > 0 && temp_y > 0){
      X_direction(left);
      Y_direction(down);
      
      while(true){
        delayMicroseconds(1);
        cX++;
        cY++;
        if(maxX){
          if(cX == wait){
            flip_x();
            cX = 0;
          }
          if(cY == int(wait*pause)){
            flip_y();
            cY = 0;
          }
          if(count_X == temp_x){
            X_cordinate += count_X;
            Y_cordinate += count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }
        }else{
          if(cX == int(wait*pause)){
            flip_x();
            cX = 0;
          }
          if(cY == wait){
            flip_y();
            cY = 0;
          }
          if(count_Y == temp_y){
            X_cordinate += count_X;
            Y_cordinate += count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }//end if
        }//end if 
      }//end while...............................................
    }else if(temp_x < 0 && temp_y < 0){
      X_direction(right);
      Y_direction(up);
      
      while(true){
        delayMicroseconds(1);
        cX++;
        cY++;
        if(maxX){
          if(cX == wait){
            flip_x();
            cX = 0;
          }
          if(cY == int(wait*pause)){
            flip_y();
            cY = 0;
          }
          if(count_X == abs(temp_x)){
            X_cordinate -= count_X;
            Y_cordinate -= count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }
        }else{
          if(cX == int(wait*pause)){
            flip_x();
            cX = 0;
          }
          if(cY == wait){
            flip_y();
            cY = 0;
          }
          if(count_Y == abs(temp_y)){
            X_cordinate -= count_X;
            Y_cordinate -= count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }//end if
        }//end if 
      }//end while..............................................
    }else if(temp_x > 0 && temp_y < 0){
      X_direction(left);
      Y_direction(up);
      
      while(true){
        delayMicroseconds(1);
        cX++;
        cY++;
        if(maxX){
          if(cX == wait){
            flip_x();
            cX = 0;
          }
          if(cY == int(wait*pause)){
            flip_y();
            cY = 0;
          }
          if(count_X == abs(temp_x)){
            X_cordinate += count_X;
            Y_cordinate -= count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }
        }else{
          if(cX == int(wait*pause)){
            flip_x();
            cX = 0;
          }
          if(cY == wait){
            flip_y();
            cY = 0;
          }
          if(count_Y == abs(temp_y)){
            X_cordinate += count_X;
            Y_cordinate -= count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }//end if
        }//end if 
      }//end while..............................................
    }else if(temp_x < 0 && temp_y > 0){
      X_direction(right);
      Y_direction(down);
      
      while(true){
        delayMicroseconds(1);
        cX++;
        cY++;
        if(maxX){
          if(cX == wait){
            flip_x();
            cX = 0;
          }
          if(cY == int(wait*pause)){
            flip_y();
            cY = 0;
          }
          if(count_X == abs(temp_x)){
            X_cordinate -= count_X;
            Y_cordinate += count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }
        }else{
          if(cX == int(wait*pause)){
            flip_x();
            cX = 0;
          }
          if(cY == wait){
            flip_y();
            cY = 0;
          }
          if(count_Y == abs(temp_y)){
            X_cordinate -= count_X;
            Y_cordinate += count_Y;
            count_X = 0;
            count_Y = 0;
            if(X_cordinate != x || Y_cordinate != y){
              drawLine(x,y,wait);
            }
            
            break;
          }//end if
        }//end if 
      }//end while..............................................
    }else if(temp_x == 0 && temp_y != 0){
      moveto_y(y,(wait/3*70));
      if(X_cordinate != x || Y_cordinate != y){
         drawLine(x,y,wait);
      }
    }else if(temp_x != 0 && temp_y == 0){
      moveto_x(x,(wait/3*70));
      if(X_cordinate != x || Y_cordinate != y){
         drawLine(x,y,wait);
      }
    }
    //................................
  }
}


void moveto_y(int y,unsigned int wait){
  int temp = 0;
  if(y <= Y_DISTANCE_STEP && y >= 0){
    temp = y - Y_cordinate;
    Y_cordinate = y;
    if(temp >= 0){
      Y_direction(down);
      for(int i = 0;i < temp; i++){
        oneStep_y(wait);
      }
    }else{
      Y_direction(up);
      for(int i = 0;i > temp; i--){
        oneStep_y(wait);
      }
    }
  }else if(y < 0){
    y = 0;
    temp = y - Y_cordinate;
    Y_cordinate = y;
    if(temp >= 0){
      Y_direction(down);
      for(int i = 0;i < temp; i++){
        oneStep_y(wait);
      }
    }else{
      Y_direction(up);
      for(int i = 0;i > temp; i--){
        oneStep_y(wait);
      }
    }
  }else if(y > Y_DISTANCE_STEP){
    y = 16350;
    temp = y - Y_cordinate;
    Y_cordinate = y;
    Y_direction(down);
    for(int i = 0;i < temp; i++){
      oneStep_y(wait);
    }
  }
}

void moveto_x(int x,unsigned int wait){
  int temp = 0;
  if(x <= X_DISTANCE_STEP && x >= 0){
    temp = x - X_cordinate;
    X_cordinate = x;
    if(temp >= 0){
      X_direction(left);
      for(int i = 0;i < temp; i++){
        oneStep_x(wait);
      }
    }else{
      X_direction(right);
      for(int i = 0;i > temp; i--){
        oneStep_x(wait);
      }
    }
  }else if(x < 0){
    x = 0;
    temp = x - X_cordinate;
    X_cordinate = x;
    if(temp >= 0){
      X_direction(left);
      for(int i = 0;i < temp; i++){
        oneStep_x(wait);
      }
    }else{
      X_direction(right);
      for(int i = 0;i > temp; i--){
        oneStep_x(wait);
      }
    }
  }else if(x > X_DISTANCE_STEP){
    x = 16250;
    temp = x-X_cordinate;
    X_cordinate = x;
    X_direction(left);
    for(int i = 0;i < temp; i++){
      oneStep_x(wait);
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

#define down HIGH                   //y direction down
#define up LOW                      //y direction up
#define Y_step_pin 9                //stepper motor for Y axis
#define Y_direction_pin 8           //Y axis direction ()
#define up_Y_sensor_pin 7           //up sensor for Y axis
#define down_Y_sensor_pin 6         //down seneor for Y axis
#define Y_busy 5                    //goes high when CNC_Y is busy
#define master_ready 4              //goes high when Master is ready to send info

const int Y_DISTANCE_STEP = 16350;  //.. inch 
static int Y_cordinate = 0;         //0 to 16350 (will change depending on the Y position)
unsigned int wait = 100;            //In microsecond (fastest time the stepper motor can funtion properly is 70)
int Y = 0;                          //temp placeholder for Y_cordinate


void setup() {
  Serial.begin(9600);
  initialize();
  calibrate();
}

void loop() {
  if(digitalRead(master_ready) == HIGH){
      digitalWrite(Y_busy, HIGH);
      Y = Serial.parseInt();
      wait = Serial.parseInt();
      moveto_y(Y,wait);
  }
}
void moveto_y(int y,unsigned int wait){
    int temp = y - Y_cordinate;
    Y_cordinate = y;
    if(temp > 0){
      Y_direction(down);
      for(int i = 0;i < temp; i++){
        oneStep_y(wait);
      }
      digitalWrite(Y_busy, LOW);
    }else if(temp < 0){
      Y_direction(up);
      for(int i = 0;i > temp; i--){
        oneStep_y(wait);
      }
      digitalWrite(Y_busy, LOW);
    }else{
      digitalWrite(Y_busy, LOW);
    }
}
void initialize(){
  pinMode(Y_step_pin, OUTPUT);
  pinMode(Y_direction_pin, OUTPUT);
  pinMode(up_Y_sensor_pin, INPUT);
  pinMode(down_Y_sensor_pin, INPUT);
  digitalWrite(Y_busy, HIGH);
  pinMode(Y_busy, OUTPUT);
  pinMode(master_ready, INPUT);
}
void calibrate(){
  digitalWrite(Y_busy, HIGH);
  Y_direction(up);
  delay(10);
  while(digitalRead(up_Y_sensor_pin) == LOW){
      oneStep_y(100);
  }
  delay(500);
  digitalWrite(Y_busy, LOW);
}
void Y_direction(boolean dir){
  digitalWrite(Y_direction_pin, dir);
}
void oneStep_y(unsigned int wait){
  digitalWrite(Y_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(Y_step_pin, LOW);   
  delayMicroseconds(wait);
}

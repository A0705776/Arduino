#define down HIGH                   //Z direction down
#define up LOW                      //Z direction up
#define Z_step_pin 2                //stepper motor for Z axis
#define Z_direction_pin 3           //Z axis direction ()
#define Z_sensor_pin 9              //up sensor for Z axis
#define Z_busy 8                    //goes high when CNC_Z is busy
#define master_ready 7              //goes high when Master is ready to send info

const unsigned int Z_DISTANCE_STEP = 43500;  //.. inch 
static float Z_cordinate = 0;         //0 to 16350 (will change depending on the Y position)
unsigned int wait = 120;            //In microsecond (fastest time the stepper motor can funtion properly is 70)
float Z = 0;                          //temp placeholder for Y_cordinate


void setup() {
  Serial.begin(9600);
  initialize();
  calibrate();
}

void loop() {
  
}
void moveto_z(float z,unsigned int wait){
    float temp = z - Z_cordinate;
    Z_cordinate = z;
    if(temp > 0){
      Z_direction(down);
      for(float i = 0;i < temp; i++){
        oneStep_z(wait);
      }
      digitalWrite(Z_busy, LOW);
    }else if(temp < 0){
      Z_direction(up);
      for(float i = 0;i > temp; i--){
        oneStep_z(wait);
      }
      digitalWrite(Z_busy, LOW);
    }else{
      digitalWrite(Z_busy, LOW);
    }
}
void initialize(){
  pinMode(Z_step_pin, OUTPUT);
  pinMode(Z_direction_pin, OUTPUT);
  pinMode(Z_sensor_pin, INPUT);
  digitalWrite(Z_busy, HIGH);
  pinMode(Z_busy, OUTPUT);
  pinMode(master_ready, INPUT);
}
void calibrate(){
  Z_direction(up);
  delay(10);
  while(digitalRead(Z_sensor_pin) == LOW){
      oneStep_z(wait);
  }
}
void Z_direction(boolean dir){
  digitalWrite(Z_direction_pin, dir);
}
void oneStep_z(unsigned int wait){
  digitalWrite(Z_step_pin, HIGH);   
  delayMicroseconds(wait);
  digitalWrite(Z_step_pin, LOW);   
  delayMicroseconds(wait);
}

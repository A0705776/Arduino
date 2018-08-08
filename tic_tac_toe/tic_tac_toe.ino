/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
//#include "font.h"


//#define clk 8
//#define input 11
//#define rst 9
//#define in 10

#define clk 1
#define input 2
#define rst 0
#define in 4

int matrix[3][3] = {{0,0,0},
                    {0,0,0},
                    {0,0,0}};
int matrix2[3][3] = {{0,0,0},
                    {0,0,0},
                    {0,0,0}};

bool finish = false;
int row = 0;
int col = 0;
bool red = true;

int r = B110;
int g = B111;
int c = B001;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(clk, OUTPUT);
  pinMode(input, OUTPUT);
  pinMode(rst, OUTPUT);
  pinMode(in, INPUT);
  digitalWrite(rst, HIGH);

//  Serial.begin(9600);
  
  
}


// the loop function runs over and over again forever
void loop() {

//      shift_3_bit(g);
//      shift_3_bit(r);
//      shift_3_bit(c);
//      shift_3_bit(B000);
//      shift_3_bit(B111);

  if(digitalRead(in) == HIGH){
   
    //delay(1);
    for(int i = 1, ii = 0; i <= 4; i = i * 2){
      for(int j = 1, jj = 0; j <= 4; j = j * 2){
        shift_3_bit(~j);
        shift_3_bit(i);
        if(digitalRead(in) == HIGH){
            
//          c = bitinv(i);
//          r = ~bitinv(j);
//          g = ~bitinv(j);
//          if(matrix[2-ii][jj] == 1){
//            matrix[2-ii][jj] = 2;
//          }else if(matrix[2-ii][jj] == 2){
//            matrix[2-ii][jj] = 0;
//          }else {
//            matrix[2-ii][jj] = 1;
//          }

          
            if(matrix[2-ii][jj] == 0 && !finish){
                if(red){ 
                  matrix[2-ii][jj] = 1;
                  matrix2[2-ii][jj] = 1;
                  red = false;
                }else{
                  matrix[2-ii][jj] = 2;
                  matrix2[2-ii][jj] = 2;
                  red = true;
                }
                check();
            }else if(finish){
                gameWon();
            }
            
          
          
//          Serial.println(ii);
//          Serial.println(jj);
          
        }
        reset();
        jj++;
      }
      ii++;
    }
    //delay(200);
    
  }
  game();
//  delay(20);
//  reset();
}

void gameWon(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 10; j++){
      game2();
    }
    for(int j = 0; j < 10; j++){
      game();
    }
  }
}

void check(){
  if(matrix[0][0] == 1 && matrix[0][1] == 1 && matrix[0][2] == 1 || matrix[0][0] == 2 && matrix[0][1] == 2 && matrix[0][2] == 2){
    row = 0;
    
    matrix2[0][0] = 0;
    matrix2[0][1] = 0;
    matrix2[0][2] = 0;
    finish = true;
    gameWon();
  }else if(matrix[0][0] == 1 && matrix[1][0] == 1 && matrix[2][0] == 1 || matrix[0][0] == 2 && matrix[1][0] == 2 && matrix[2][0] == 2){
    finish = true;
    matrix2[0][0] = 0;
    matrix2[1][0] = 0;
    matrix2[2][0] = 0;
    col = 0;
    gameWon();
  }else if(matrix[0][1] == 1 && matrix[1][1] == 1 && matrix[2][1] == 1 || matrix[0][1] == 2 && matrix[1][1] == 2 && matrix[2][1] == 2){
    finish = true;
    matrix2[0][1] = 0;
    matrix2[1][1] = 0;
    matrix2[2][1] = 0;
    col = 1;
    gameWon();
  }else if(matrix[1][0] == 1 && matrix[1][1] == 1 && matrix[1][2] == 1 || matrix[1][0] == 2 && matrix[1][1] == 2 && matrix[1][2] == 2){
    row = 1;
    matrix2[1][0] = 0;
    matrix2[1][1] = 0;
    matrix2[1][2] = 0;
    finish = true;
    gameWon();
  }else if(matrix[2][0] == 1 && matrix[2][1] == 1 && matrix[2][2] == 1 || matrix[2][0] == 2 && matrix[2][1] == 2 && matrix[2][2] == 2){
    row = 2;
    matrix2[2][0] = 0;
    matrix2[2][1] = 0;
    matrix2[2][2] = 0;
    finish = true;
    gameWon();
  }else if(matrix[0][2] == 1 && matrix[1][2] == 1 && matrix[2][2] == 1 || matrix[0][2] == 2 && matrix[1][2] == 2 && matrix[2][2] == 2){
    finish = true;
    matrix2[0][2] = 0;
    matrix2[1][2] = 0;
    matrix2[2][2] = 0;
    col = 2;
    gameWon();
  }else if(matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 1 || matrix[0][0] == 2 && matrix[1][1] == 2 && matrix[2][2] == 2){
    finish = true;
    matrix2[0][0] = 0;
    matrix2[1][1] = 0;
    matrix2[2][2] = 0;
    row = 3;
    gameWon();
  }else if(matrix[0][2] == 1 && matrix[1][1] == 1 && matrix[2][0] == 1 || matrix[0][2] == 2 && matrix[1][1] == 2 && matrix[2][0] == 2){
    finish = true;
    matrix2[0][2] = 0;
    matrix2[1][1] = 0;
    matrix2[2][0] = 0;
    col = 3;
    gameWon();
  }
}

void game2(){
    int temp = 1;
    r = B0;
    g = B0;
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(matrix2[i][j] == 1){
            r =  r + 1;         
        }else if(matrix2[i][j] == 2){
            g = g + 1;
        }else{
          
        }
        if(j < 2){
          r = r << 1;
          g = g << 1;
        }
      }
      shift_3_bit(~g);
      shift_3_bit(~r);
      shift_3_bit(temp);
      shift_3_bit(B000);
      shift_3_bit(B111);
      temp = temp << 1;
      delay(6);
      //delayMicroseconds(2000);
      reset();
    }
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B111);
}

void m(int i, int j, int value){
  matrix[i][j] = value;  
}

void game(){
    int temp = 1;
    r = B0;
    g = B0;
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(matrix[i][j] == 1){
            r =  r + 1;         
        }else if(matrix[i][j] == 2){
            g = g + 1;
        }else{
          
        }
        if(j < 2){
          r = r << 1;
          g = g << 1;
        }
      }
      shift_3_bit(~g);
      shift_3_bit(~r);
      shift_3_bit(temp);
      shift_3_bit(B000);
      shift_3_bit(B111);
      temp = temp << 1;
      delay(6);
      //delayMicroseconds(2000);
      reset();
    }
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B000);
    shift_3_bit(B111);
}

void reset(){
  digitalWrite(rst, LOW);
  delayMicroseconds(1);
  digitalWrite(rst, HIGH);
  r = B0;
  g = B0;
}
void shift_3_bit(int value){
  digitalWrite(input, (value & 4));
  clk_pulse();
  digitalWrite(input, (value & 2));
  clk_pulse();
  digitalWrite(input, (value & 1));
  clk_pulse();
}

int bitinv(int b){
  return ((b & 4) >> 2) | ((b & 1) << 2) | (b&2);
}


void shift_1_bit(bool state){
  digitalWrite(input, state);
  clk_pulse();
}
void clk_pulse(){
  digitalWrite(clk, HIGH);
  delayMicroseconds(1);
  digitalWrite(clk, LOW); 
  //delayMicroseconds(1);
}


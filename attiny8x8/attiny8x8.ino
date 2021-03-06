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
#include "font.h"


#define clk 1
#define input 2
#define rst 0
#define in 4

#define a " ALAMIN "


char smily[8] = { 0x00, 0x66, 0x66, 0x00, 0x81, 0xC3, 0x7E, 0x18};
//char smily[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char fullheart[8] = {0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
char heart[6][8] = {
    {0x66, 0xFF, 0xDB, 0xC3, 0xC3, 0x66, 0x3C, 0x18},
    {0x66, 0xFF, 0xDB, 0xC3, 0x66, 0x3C, 0x18, 0x00},
    {0x00, 0x66, 0x7E, 0x66, 0x3C, 0x18, 0x00, 0x00},
    {0x00, 0x66, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00},
    {0x00, 0x00, 0x24, 0x3C, 0x18, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00}
  };
char ball[12][8] = {
    {0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00},

    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
  };

int state = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(clk, OUTPUT);
  pinMode(input, OUTPUT);
  pinMode(rst, OUTPUT);
  pinMode(in, INPUT);
  digitalWrite(rst, HIGH);
   
}


// the loop function runs over and over again forever
void loop() {
//  shift_8_bit(32);
//  shift_8_bit(254);
//  delay(1000);
  if(digitalRead(in) == HIGH){
    LEDreset();
    delay(300);
    state++;
  }
  if(state >= 6) state = 0;

  switch(state){
    case 0:
      writeWord("/HELLO/WORLD/",13,10);
      break;
    case 1:
      writeChar('A',50);
      writeChar('L',50);
      writeChar('A',50);
      writeChar('M',50);
      writeChar('I',50);
      writeChar('N',50);
      writeChar('/',50);
      break;
    case 2:
      printScreen(smily,100);
      break;
    case 3:
      for(int i = 0; i < 6; i++){
        printScreen(heart[i],5);
      }
      for(int i = 0; i < 6; i++){
        printScreen(heart[5-i],5);
      }
      break;
    case 4:
      for(int i = 0; i < 6; i++){
        printScreenInv(heart[i],5);
      }
      for(int i = 0; i < 6; i++){
        printScreenInv(heart[5-i],5);
      }
      break;
    case 5:
      for(int i = 0; i < 10; i++){
        writeChar(48+i,50);
      }
      break;
    case 6:
      //printSnake();
      break;
  }  
}

void printSnake(){
  for(int j = 0; j< 8; j++){
    int temp = 1;
    for(int i = 1; i < 256; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit(~i);
      //}
      
      delay(10);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
    temp = temp << 1;
    //temp++;
  }  
}

void printScreenInv(char* pic,int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1;
    for(int i = 0; i < 8; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(pic[i]);
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }  
}


void printScreen(char* pic,int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1;
    for(int i = 0; i < 8; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~pic[i]);
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }  
}

void write2(char data, char data2, int len, int velocity){
  for(int i = 0; i < len-1; i++){
    for(int j = 0; j < 7; j++){
        //writeCharLeftShift(data[i],7-j,velocity);
        //writeCharsLeftShift(data[i],data[i+1],7-j,velocity);
      writeCharsRightShift(data,data2,j,velocity);
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }
}
void writeWord(char* data, int len, int velocity){
  for(int i = 0; i < len-1; i++){
    for(int j = 0; j < 7; j++){
        //writeCharLeftShift(data[i],7-j,velocity);
        //writeCharsLeftShift(data[i],data[i+1],7-j,velocity);
      writeCharsRightShift(data[i],data[i+1],j,velocity);
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }
}

void writeCharsRightShift(char text, char text2, int shift, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~((font8x8_basic[text-47][i] >> shift)|(font8x8_basic[text2-47][i] << (7 - shift))));
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }  
}
void writeCharRightShift(char text,int shift, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1, temp2 = 0;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~(font8x8_basic[text-47][i] >> shift));
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
    }
  }  
}
void writeCharsLeftShift(char text, char text2, int shift, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1, temp2 = 0;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~(((font8x8_basic[text-47][i] << shift))|((font8x8_basic[text2-47][i] >> (7 - shift)))));
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
    }
  }  
}
void writeCharLeftShift(char text,int shift, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1, temp2 = 0;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~(font8x8_basic[text-47][i] << shift));
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
    }
  }  
}

void writeCharSlow(char text, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1, temp2 = 0;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~font8x8_basic[text-47][i]);
      //}
      temp = temp << 1;
      delay(20);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }  
}

void writeChar(char text, int counter){
  for(int j = 0; j< counter; j++){
    int temp = 1, temp2 = 0;
    for(int i = 0; i < 7; i++){
      //for(int j = 0; j < 8; j++){
        shift_8_bit(temp);
        shift_8_bit_reverse(~font8x8_basic[text-47][i]);
      //}
      temp = temp << 1;
      delayMicroseconds(2000);
      LEDreset();
      if(digitalRead(in) == HIGH){
          return;
      }
    }
  }  
}

void LEDreset(){
  digitalWrite(rst, LOW);
  delayMicroseconds(1);
  digitalWrite(rst, HIGH);
}
void shift_8_bit(int value){
  digitalWrite(input, (value & 128));
  clk_pulse();
  digitalWrite(input, (value & 64));
  clk_pulse();
  digitalWrite(input, (value & 32));
  clk_pulse();
  digitalWrite(input, (value & 16));
  clk_pulse();
  digitalWrite(input, (value & 8));
  clk_pulse();
  digitalWrite(input, (value & 4));
  clk_pulse();
  digitalWrite(input, (value & 2));
  clk_pulse();
  digitalWrite(input, (value & 1));
  clk_pulse();
}

void shift_8_bit_reverse(int value){
  digitalWrite(input, (value & 1));
  clk_pulse();
  digitalWrite(input, (value & 2));
  clk_pulse();
  digitalWrite(input, (value & 4));
  clk_pulse();
  digitalWrite(input, (value & 8));
  clk_pulse();
  digitalWrite(input, (value & 16));
  clk_pulse();
  digitalWrite(input, (value & 32));
  clk_pulse();
  digitalWrite(input, (value & 64));
  clk_pulse();
  digitalWrite(input, (value & 128));
  clk_pulse();
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

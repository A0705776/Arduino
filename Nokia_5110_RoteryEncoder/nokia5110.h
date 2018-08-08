#include <Arduino.h>
//#include <Arduino.Servo.h>

#define RST 12
#define CE  11
#define DC  10
#define DIN  9
#define CLK  8

void LcdWriteCmd(byte cmd){
  digitalWrite(DC, LOW); //DC low for comand
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}
void LcdXY(int x, int y){
  LcdWriteCmd(0x80 | x); //Colum.
  LcdWriteCmd(0x40 | y); //row.
}

void LcdWriteData(byte dat){
  digitalWrite(DC, HIGH); //DC low for comand
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
  digitalWrite(CE, HIGH);
}
void LcdWriteChracter(char chracter){
  for(int i=0; i<5; i++) LcdWriteData(ASCII[chracter - 0x20][i]);
  LcdWriteData(0x00);
}

void LcdWrite(String chracters){
  for (int i = 0; i <chracters.length(); i++) LcdWriteChracter(chracters.charAt(i));
}
void LcdWrite(int x){
  String chracters = String(x);
  for (int i = 0; i <chracters.length(); i++) LcdWriteChracter(chracters.charAt(i));
}
void LcdWrite(char chracter){
  LcdWriteChracter(chracter);
}

void LcdClear(){for(int i=0; i<504; i++) LcdWriteData(0x00);}

void nokia5110start(){
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  
  LcdWriteCmd(0x21); // LCD extended command
  LcdWriteCmd(0xBB); // set LCD Vop (contrast)
  LcdWriteCmd(0x04); // Set temp coefficent
  LcdWriteCmd(0x14); // LCD bias mode 1:40
  LcdWriteCmd(0x20); // LCD basic commands
  //LcdWriteCmd(0x09); // LCD all dots
  LcdWriteCmd(0x0C); // LCD normal
  //LcdWriteCmd(0x0D); // LCD inverted
  
  LcdClear();
//  LcdWrite("I Love Chicken");
//  LcdXY(30,5);
//  LcdWrite("ILC");
}


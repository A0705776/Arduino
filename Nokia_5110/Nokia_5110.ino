#include "font.h"
#include "nokia5110.h"
#include "large_numbers.h"


int x = 0;

void setup() {
  nokia5110start();
}
int i = 0;
void loop() {
  //LcdWriteData(0x55); 
  //LcdWriteData(0xAA);
  //LcdWriteData(0xFE);
  //LcdWriteChracter('a');
  //LcdClear();
//  LcdXY(10, 2);
//  
//  LcdWrite("x = ");
//  LcdWrite(x);
//  number1();
//  number1(21);
//  number1(45);
//  number1(65);

    i++;
    LcdXY(10, 2);
    LcdWrite("A");
    LcdWrite(i);
  


  //delay(1000);
}

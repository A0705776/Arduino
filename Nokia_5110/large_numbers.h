 #include <Arduino.h>
 
  void number1(int z = 0){
    for(int x = 0; x < 5; x++){
      for(int i = 7; i < 14; i++){
        LcdXY(i + z, x);
        LcdWriteData(0xFF);
      }
    }
    for(int x = 0; x < 1; x++){
      for(int i = 1; i < 7; i++){
        LcdXY(i + z, x);
        LcdWriteData(0xF0);
      }
    }
    for(int x = 4; x < 5; x++){
      for(int i = 1; i < 7; i++){
        LcdXY(i + z, x);
        LcdWriteData(0xE0);
      }
    }
    for(int x = 4; x < 5; x++){
      for(int i = 14; i < 19; i++){
        LcdXY(i + z, x);
        LcdWriteData(0xE0);
      }
    }
  }

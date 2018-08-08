#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int day = 6;
int am = 1;
int hour = 1;
int minute = 16;
int sec = 0;
boolean twelve = true;
boolean normal = false;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(":");
  lcd.setCursor(5,0);
  lcd.print(":");
  
  if(hour == 12){}else{twelve = false;}
}
void loop(){
  
  for(day; day <= 7;day++){
    switch(day){
      case 1: lcd.setCursor(0,1); lcd.print("Mon"); break;
      case 2: lcd.setCursor(0,1); lcd.print("Tue"); break;
      case 3: lcd.setCursor(0,1); lcd.print("Wed"); break;
      case 4: lcd.setCursor(0,1); lcd.print("Thu"); break;
      case 5: lcd.setCursor(0,1); lcd.print("Fri"); break;
      case 6: lcd.setCursor(0,1); lcd.print("Sat"); break;
      case 7: lcd.setCursor(0,1); lcd.print("Sun"); break;
    }
    
    for(am; am <= 2; am++){
      switch(am){
        case 1: lcd.setCursor(14,0); lcd.print("AM"); break;
        case 2: lcd.setCursor(14,0); lcd.print("PM"); break;
      }
      if(!normal){
      if(twelve){
        for(hour = 12; hour <= 12; hour++){
          if(hour < 10){lcd.setCursor(0,0); lcd.print("0"); lcd.setCursor(1,0);}else{lcd.setCursor(0,0);}
          lcd.print(hour);
          for(minute; minute < 60;  minute++){  
            if(minute < 10){lcd.setCursor(3,0); lcd.print("0"); lcd.setCursor(4,0);}else{lcd.setCursor(3,0);}
            lcd.print(minute);
            for(sec; sec <60; sec++){
              if(sec < 10){lcd.setCursor(6,0); lcd.print("0"); lcd.setCursor(7,0);}else{lcd.setCursor(6,0);}
              lcd.print(sec);
              millis(1000);
            }
          }
        } hour = 1; minute = 0; sec = 0;
      }else{}
      for(hour; hour <= 11; hour++){
        if(hour < 10){lcd.setCursor(0,0); lcd.print("0"); lcd.setCursor(1,0);}else{lcd.setCursor(0,0);}
        lcd.print(hour);
        for(minute; minute < 60;  minute++){  
          if(minute < 10){lcd.setCursor(3,0); lcd.print("0"); lcd.setCursor(4,0);}else{lcd.setCursor(3,0);}
          lcd.print(minute);
          for(sec; sec <60; sec++){
            if(sec < 10){lcd.setCursor(6,0); lcd.print("0"); lcd.setCursor(7,0);}else{lcd.setCursor(6,0);}
            lcd.print(sec);
            millis(1000);
          }sec = 0;
        }minute = 0;
      }normal = true;
      }else{
        
        for(hour = 12; hour <= 12; hour++){
          if(hour < 10){lcd.setCursor(0,0); lcd.print("0"); lcd.setCursor(1,0);}else{lcd.setCursor(0,0);}
          lcd.print(hour);
          for(minute = 0; minute < 60;  minute++){  
            if(minute < 10){lcd.setCursor(3,0); lcd.print("0"); lcd.setCursor(4,0);}else{lcd.setCursor(3,0);}
            lcd.print(minute);
            for(sec = 0; sec <60; sec++){
              if(sec < 10){lcd.setCursor(6,0); lcd.print("0"); lcd.setCursor(7,0);}else{lcd.setCursor(6,0);}
              lcd.print(sec);
              millis(1000);
            }
          }
        }
        
        for(hour = 1; hour <= 11; hour++){
          if(hour < 10){lcd.setCursor(0,0); lcd.print("0"); lcd.setCursor(1,0);}else{lcd.setCursor(0,0);}
          lcd.print(hour);
          for(minute = 0; minute < 60;  minute++){  
            if(minute < 10){lcd.setCursor(3,0); lcd.print("0"); lcd.setCursor(4,0);}else{lcd.setCursor(3,0);}
            lcd.print(minute);
            for(sec = 0; sec <60; sec++){
              if(sec < 10){lcd.setCursor(6,0); lcd.print("0"); lcd.setCursor(7,0);}else{lcd.setCursor(6,0);}
              lcd.print(sec);
              millis(1000);
            }
          }
        }
      } 
    }am = 1; 
  }day = 1;
}

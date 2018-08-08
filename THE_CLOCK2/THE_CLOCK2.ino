#include<Wire.h>

#include "RTClib.h"
RTC_DS1307 RTC; // a4 green, a5 yello

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // v0 is the pot 
                                       //rs and e are 12 and 11
                                       // d4 - d7 are 5 - 2

boolean am = false;//..........................,,am/pm.........................................
boolean reset = false;//.........................reset.........................................

int resetButton = 8;
int speker = 10;

byte alarmLogo[8] =
{
  B11011,
  B11111,
  B01010,
  B10101,
  B10001,
  B01110,
  B00000,
};

void HOUR(DateTime now);//....................declaration......................................
void MINUTE(DateTime now);//..................declaration......................................
void SECOND(DateTime now);//..................declaration......................................
void AmOrPm();//..............................declaration......................................
void DayOfWeek(DateTime now);//...............declaration......................................
void DATE(DateTime now);//....................declaration......................................

void setup() {
  Serial.begin(57600);
  Wire.begin();
  RTC.begin();
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__)); // this is important...........................
  }
  
  pinMode(resetButton, INPUT);
  pinMode(speker, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(":");
  lcd.setCursor(5,0);
  lcd.print(":");
  
  lcd.createChar(1, alarmLogo);
}

//________________________________________________________________________________________________
void HOUR(DateTime now){
  if(now.hour()< 10){
      am = true;
      lcd.setCursor(0,0); 
      if(now.hour()==0){
        lcd.setCursor(0,0);
        lcd.print("12");
      }else{
        lcd.print("0");
        lcd.print(now.hour());
      }
    }else if(now.hour()<12){
      lcd.setCursor(0,0); lcd.print(now.hour());
      am = true;
    }else{
      am = false;
      if(now.hour()<22){
        lcd.setCursor(0,0); lcd.print("0"); lcd.print(now.hour()-12);
      }else{
        lcd.setCursor(0,0);
        lcd.print(now.hour()-12);
      }
    }
}
//________________________________________________________________________________________________
//________________________________________________________________________________________________
void MINUTE(DateTime now){
    if(now.minute()< 10){
      lcd.setCursor(3,0); lcd.print("0");lcd.print(now.minute());
    }else{
      lcd.setCursor(3,0); lcd.print(now.minute());
    }
}
//________________________________________________________________________________________________
//________________________________________________________________________________________________
void SECOND(DateTime now){
    if(now.second()< 10){
      lcd.setCursor(6,0); lcd.print("0");lcd.print(now.second());
    }else{
      lcd.setCursor(6,0); lcd.print(now.second());
    }
}
//________________________________________________________________________________________________
//________________________________________________________________________________________________
void AmOrPm(){
    if(am == true){
      lcd.setCursor(10,0); lcd.print("AM");
    }else{
      lcd.setCursor(10,0); lcd.print("PM");
    }
}
//________________________________________________________________________________________________
//________________________________________________________________________________________________
void DayOfWeek(DateTime now){
    lcd.setCursor(0,1);
    switch(now.dayOfWeek()){
    case 1: lcd.print("MON"); break;
    case 2: lcd.print("TUE"); break;
    case 3: lcd.print("WED"); break;
    case 4: lcd.print("THU"); break;
    case 5: lcd.print("FRI"); break;
    case 6: lcd.print("SAT"); break;
    case 0: lcd.print("SUN"); break;
    default: break;
    }
}
//________________________________________________________________________________________________
//________________________________________________________________________________________________
void DATE(DateTime now){
      lcd.setCursor(4,1); 
      if(now.month()<10){
        lcd.print("0");
        lcd.print(now.month());
      }else{
        lcd.print(now.month());
      }
      lcd.print("/");
      if(now.day()<10){
        lcd.print("0");
        lcd.print(now.day());
      }else{
        lcd.print(now.day());
      }
      lcd.print("/");
      lcd.print(now.year()-2000);
}
//________________________________________________________________________________________________

void loop() { 
   DateTime now = RTC.now();
    
    if(!reset){
      HOUR(now);
      MINUTE(now);
      SECOND(now);
      AmOrPm();
      DayOfWeek(now);
      DATE(now);
    }else{
      analogWrite(speker, 100);
    delay(200);
    analogWrite(speker, 0);
    delay(100);
    analogWrite(speker, 20);
    delay(100);
    analogWrite(speker, 0);
    delay(200);
  }
    
    

    
    if(reset == false && digitalRead(resetButton) == HIGH){
      reset = true;
      lcd.clear();
      lcd.setCursor(14,0);
      lcd.write(1);
      delay(1000);
    } else if(reset == true && digitalRead(resetButton) == HIGH){
      reset = false;
      lcd.clear();
      delay(500);
    }
    
   
    delay(1);
}

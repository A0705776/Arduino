#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
}
void loop()
{
  lcd.print("Printing Text");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("Text");
  delay(3000);
  lcd.clear();
  
  lcd.print("Blink");
  lcd.blink();
  delay(3000);
  lcd.clear();
  lcd.noBlink();
  
  lcd.print("Underline");
  lcd.cursor();
  delay(3000);
  lcd.clear();
  
  lcd.print("No cursor");
  lcd.noCursor();
  delay(3000);
  lcd.clear();
  
  lcd.print("no display");
  delay(1000);
  lcd.clear();
  lcd.noDisplay();
  lcd.print("display on");
  delay(3000);
  lcd.display();
  delay(3000);
  lcd.clear();

}

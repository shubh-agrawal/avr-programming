#include <LiquidCrystal.h>
LiquidCrystal(12,13,5,4,3,2);
void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  Lcd.print("Threshold");
}
void loop()
{
  int a=analogRead(A0);
  a=map(a,0,1023,0,255);
  int b=analogRead(A1);
  b=map(b,0,1023,0,255);
  lcd.setCursor(0,1);
  lcd.print("X:");
  lcd.setCursor(2,1);
  lcd.print(a);
  lcd.setCursor(10,1);
  lcd.print("Y;");
  lcd.setCursor(12,1);
  lcd.print(b);
  delay(300);
}
  


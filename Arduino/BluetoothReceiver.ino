#include <LiquidCrystal.h>
#include <DFR_Key.h>

DFR_Key keypad;
LiquidCrystal lcd(8,9,4,5,6,7);

void setup()
{
  keypad.setRate(10);
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
}

int getInt()
{
  int val = -1;
  if(Serial.available())
  {
    val = Serial.parseInt();
  }
  return val;
}

void parseCommand(int val, int& player)
{
  if(val > 999 & val < 9999) //3 digits only
  {
    player = val % 10;
  }
  else
  {
    player = -1;
  }
}

void loop()
{
  lcd.setCursor(0,0);
  int val = getInt(); //last Digit should be the player
  int player = 0;
  if(val != -1);
    parseCommand(val,player);
  switch(player)
  {
    lcd.setCursor(0,0);
    case 1:
      lcd.clear();
      lcd.print("Player one!");
      break;
    case 2:
      lcd.clear();
      lcd.print("Player two!");
      break;
    case 3:
      lcd.clear();
      lcd.print("Player three!");
      break;
    case 4:  
      lcd.clear();
      lcd.print("Player four!");
      break;
    default:
      break;
  }
}

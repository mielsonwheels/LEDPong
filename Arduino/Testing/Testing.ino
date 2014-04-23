#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

int MODE = -1;
int X = -1, Y = -1;
const int LED_POSITION_MODE = 1;
const int MULTIPLAYER_MODE = 2;

void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
}

String getStringFromSerial() //returns 5 digit String of digits
{
  int val = -1;
  char charVal[6];
  String stringVal = "-1";
  if(Serial.available())
  {
    val = Serial.parseInt();
    if(val > 9999 && val < 99999) //five digits is acceptable
    {
      itoa(val,charVal,10);
      stringVal = charVal;
      MODE = val / 10000;
      return stringVal;
    }
  }
  return "-1"; //nothing entered
}

void setXYValues(String val)
{
  char* x = new char[2];
  x[0] = val[1];
  x[1] = val[2];
  char* y = new char[2];
  y[0] = val[3];
  y[1] = val[4];
  X = atoi(x);
  Y = atoi(y);
  delete x;
  delete y;
}

void setPlayer(String val)
{
  
}

void loop()
{
  String number = getStringFromSerial();
  if(number != "-1")
  {
    lcd.clear();
    lcd.setCursor(0,0);
    switch(MODE)
    {
      case 1: //LED_POSITION
        setXYValues(number);
        break;
      case 2: //MULTIPLAYER
        
        break;
      default:
        break;
    }
  }
}

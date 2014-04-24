#include <LiquidCrystal.h>
#include <LedControl.h>

LiquidCrystal lcd(8,9,4,5,6,7);
LedControl lc = LedControl(12,11,10,1);

int MODE = -1;
int X = -1, Y = -1;
const int LED_POSITION_MODE = 1;
const int MULTIPLAYER_MODE = 2;

const int CMD_UP = 10;
const int CMD_DOWN = 11;

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

int getPlayer(String val)
{
   
   return atoi(val.c_str())%10;
}

int getCommand(String val)
{
  char* x = new char[2];
  x[0] = val[2];
  x[1] = val[3];
  int value = atoi(x);
  delete x;
  return value;
}



void multiPlayerLoop(String number)
{
  int player = -1;
  int command = -1;
  player = getPlayer(number);
  command = getCommand(number);
  lcd.clear();
  lcd.setCursor(0,0);
  switch(player)
  {
    case 1: //move left paddle
      lcd.print("Player 1");
      break;
    case 2: //move right paddle
      lcd.print("Player 2");
      break;
    case 3: //move top paddle
      lcd.print("Player 3");
      break;
    case 4: //move bottom paddle
      lcd.print("Player 4");
      break;
    default:
      break; 
  }
  lcd.setCursor(0,1);
  switch(command)
  {
    case CMD_UP:
      lcd.print("Up");
      break;
    case CMD_DOWN:
      lcd.print("Down");
      break;
    default:
      lcd.print("Invalid command");
      break;
  }
}

void setLed(int x,int y, boolean on)
{
  int address = -1;
  if(y > 0 && y < 8) //first row
  {
    if(x > 0 && x < 8) // first column
      address = 0;
    else if(x > 7 && x < 16) //second column
      address = 1;
    else if(x > 15 && x < 24) //third column
      address = 2;
  }
  else if (y > 7 && y < 16) //second row
  {
    if(x > 0 && x < 8) // first column
      address = 3;
    else if(x > 7 && x < 16) //second column
      address = 4;
    else if(x > 15 && x < 24) //third column
      address = 5;
  }
  else if (y > 15 && x < 24)
  {
    if(x > 0 && x < 8) // first column
      address = 6;
    else if(x > 7 && x < 16) //second column
      address = 7;
    else if(x > 15 && x < 24) //third column
      address = 8; //new variable with address 0
  }
  
  lc.setLed(address,x%8,y%8,on);
  
}

void loop()
{
  String number = getStringFromSerial(); //also Sets MODE
  int player = -1;
  if(number != "-1")
  {
    lcd.clear();
    lcd.setCursor(0,0);
    switch(MODE)
    {
      case 1: //LED_POSITION
        setXYValues(number);
        lcd.print("X = ");
        lcd.print(X);
        lcd.setCursor(0,1);
        lcd.print("Y = ");
        lcd.print(Y);
        break;
      case 2: //MULTIPLAYER
        multiPlayerLoop(number);
        break;
      default:
        break;
    }
  }
}

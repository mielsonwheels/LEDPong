#include <LiquidCrystal.h>
#include <LedControl.h>
#include "Player.h"

boolean testMatrix = true;

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12,A2 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11,A1 is connected to the CLK-pin of the first MAX7221
 * Pin 10,A0 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */


LiquidCrystal lcd(8,9,4,5,6,7);
//LedControl(int dataPin, int clkPin, int csPin, int numDevices);
const int DEVICES = 8;
const int INTENSITY = 0;

LedControl lc = LedControl(12,11,10,DEVICES); //default is (12,11,10,1)
LedControl lc1 = LedControl(A3,11,A1,1);

boolean MATRIX[24][24] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int MODE = -1;
int X = -1, Y = -1;
const int LED_POSITION_MODE = 1;
const int MULTIPLAYER_MODE = 2;
const int DEMO_MODE = 3;

const int CMD_UP = 10;
const int CMD_DOWN = 11;
/*-----------------------SET UP---------------------*/
void setup()
{
  //Initialize all Devices
  for(int i = 0; i < DEVICES; i++)
  {
    lc.shutdown(i,false);
    lc.setIntensity(i,INTENSITY);
    lc.clearDisplay(i);
  }
  
  lc1.shutdown(0,false);
  lc1.setIntensity(0,INTENSITY);
  lc1.clearDisplay(0);
  
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

void doCommand(int player, int command)
{
  lcd.clear();
  lcd.setCursor(0,0);
  boolean invalid = false;
  switch(player)
  {
     case 1:
       lcd.print("Player 1");
       break;
     case 2:
       lcd.print("Player 2");
       break;
     case 3:
       lcd.print("Player 3");
       break;
     case 4:
       lcd.print("Player 4");
       break;
     default:
       invalid = true;
       break;
  }
  if(!invalid)
  {
    lcd.setCursor(0,1);
    switch(command)
    {
      case CMD_UP:
        lcd.print("UP");
        break;
      case CMD_DOWN:
        lcd.print("DOWN");
        break;
    }
  }
}

void multiPlayerLoop(String number)
{
  int player = -1;
  int command = -1;
  doCommand(getPlayer(number),getCommand(number));
}

void setRow(int y, boolean on)
{
  byte turnedOn = 0;
  if(on) turnedOn = 255;
  if(y >= 0 && y < 8) //first column
  {
    lc1.setRow(0,y,on);
    lc.setRow(3,y,on);
    lc.setRow(2,y,on);
  }
  else if(y > 7 && y < 16)
  {
    lc.setRow(6,y,on);
    lc.setRow(5,y,on);
    lc.setRow(1,y,on);
  }
  else if (y > 15 && y < 24)
  {
    lc.setRow(7,y,on);
    lc.setRow(4,y,on);
    lc.setRow(0,y,on);
  }
}

void setLed(int y,int x, boolean on)
{
  int address = -1;
  
  if(y >= 0 && y < 8) //first row
  {
    if(x >= 0 && x <= 7) // first column
    {
      y = y%8;
      y-= 7;
      if(y<0) y *= -1;
      lc1.setLed(0,x%8,y,on);
      return;
    }
    else if(x > 7 && x <= 15) //second column
      address = 3;
    else if(x > 15 && x < 24) //third column
      address = 2;
  }
  else if (y > 7 && y < 16) //second row
  {
    if(x >= 0 && x < 8) // first column
      address = 6;
    else if(x > 7 && x < 16) //second column
      address = 5;
    else if(x > 15 && x < 24) //third column
      address = 1;
  }
  else if (y > 15 && x < 24)
  {
    if(x >= 0 && x < 8) // first column
      address = 7;
    else if(x > 7 && x < 16) //second column
      address = 4;
    else if(x > 15 && x < 24) //third column
      address = 0;
  }
  if(address != -1)
  {
    MATRIX[x][y] = on;
    y = y %8;
    y -= 7;
    if(y < 0) y *= -1;
    lc.setLed(address,x%8,y,on);
  }
}


void resetMatrix()
{
  for(int i = 0; i < 24; i++)
  {
    for(int j = 0; j < 24; j++)
    {
      MATRIX[i][j] = false;
    }
  }
}

void printMatrix()
{
  for(int i = 0; i < 24; i++)
  {
    for(int j = 0; j < 24; j++)
    {
      setLed(i,j,MATRIX[i][j]);
    }
  }
}

void printRow(int row, boolean val[24])
{
  for(int i = 0; i < 24; i++)
  {
    if(val[i])
      setLed(row,i,true);
  }
}

void ballTest() {
  int Max = 23;
  int xPos = 5;
  int yPos = 0;
  int vx = 3;
  int vy = 2;
  while (true) {
    setLed(xPos, yPos, false);
    setLed(Max - xPos, Max - yPos, false);
    setLed(yPos, xPos, false);
    setLed(Max - yPos, Max - xPos, false);
    xPos += vx;
    yPos += vy;
    if (xPos > Max || xPos < 0) {
      xPos -= vx;
      vx *= -1; 
    }
    if (yPos > Max || yPos < 0) {
      yPos -= vy;
      vy *= -1; 
    }
    setLed(xPos, yPos, true);
    setLed(Max - xPos, Max - yPos, true);
    setLed(yPos, xPos, true);
    setLed(Max - yPos, Max - xPos, true);
    delay(90);
  } 
}

void demoTest()
{
   for(int i = 0; i < 24; i++)
   {
     for(int j = 0; j < 24; j++)
     {
       setLed(i,j,true);
     }
   }
   for(int i = 0; i < 24; i++)
   {
     for(int j = 0; j < 24; j++)
     {
       setLed(j,i,false);
     }
   }
   for(int i = 23; i >= 0; i--)
   {
     for(int j = 23; j >= 0; j--)
       setLed(i,j,true);
   }
   for(int i = 23; i >= 0; i--)
   {
     for(int j = 23; j >= 0; j--)
       setLed(j,i,false);
   }
}

void clearDisplay()
{
  lc1.clearDisplay(0);
  for(int i = 0; i < 8; i++)
  {
    lc.clearDisplay(i);
    resetMatrix();
  }
}

void pongTest()
{
  Player one(1);
  Player two(2);
  Player three(3);
  Player four(4);
  while(true)
  {
  for(int i = 0; i < 19; i++)
  {
    delay(100);
    two.moveUpOrLeft();
    one.moveDownOrRight();
    three.moveDownOrRight();
    four.moveUpOrLeft();
  }
  for(int i = 0; i < 19; i++)
  {
    delay(100);
    two.moveDownOrRight();
    one.moveUpOrLeft();
    three.moveUpOrLeft();
    four.moveDownOrRight();
  }
  }
  delay(10000);
}

void loop()
{
  while(true) pongTest();
  //while(true) setLed(2,1,true);
  String number = getStringFromSerial(); //also Sets MODE //uncomment this line
  int player = -1;
  if(number != "-1")
  {
    lcd.clear();
    lcd.setCursor(0,0);
    switch(MODE)
    {
      case 1: //LED_POSITION
        setXYValues(number);
        setLed(X,Y,true);
        MATRIX[X][Y] = true;
        break;
      case 2: //MULTIPLAYER
        multiPlayerLoop(number);
        break;
      case 3:
        demoTest();
        break;
      default:
        break;
    }
  }
}

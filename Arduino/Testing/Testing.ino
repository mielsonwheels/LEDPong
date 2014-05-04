//#include <LiquidCrystal.h>
#include <LedControl.h>
#include <avr/wdt.h>
#include "Player.h"
#include "Mball.h"
#include "Environment.h"
// inital values used for setting up the ics
int MODE = -1;
boolean balloff= false;
long int X = -1, Y = -1;
const int LED_TURNON_MODE = 1;
const int LED_TURNOFF_MODE = 9;
const int MULTIPLAYER_MODE = 2;
const int SET_MODE = 3;
const int SET_PLAYERS_MODE = 4;
int gamedelay;
const int CMD_UP = 10;
const int CMD_DOWN = 11;

const int DEVICES = 8;
const int INTENSITY = 12;

LedControl lc = LedControl(12,11,10,DEVICES); //default is (12,11,10,1)
LedControl lc1 = LedControl(A3,11,A1,1);
long int StartTime;
Player *POne;
Player *PTwo;
Player *PThree;
Player *PFour;
Environment *envi;
Environment *envi1;
MBall *balltest;
MBall *balltest1;


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


/*-----------------------SET UP---------------------*/
void setup()
{
  //Initialize all Devices

  for(int i = 0; i < DEVICES; i++)
  {
    lc.shutdown(i,false);
    lc.setIntensity(i,INTENSITY);
    lc.clearDisplay(i);
    delay(100);
    
  }
  lc1.shutdown(0,false);
  lc1.setIntensity(0,INTENSITY);
  lc1.clearDisplay(0);
  delay(100);
  StartTime=0;
  gamedelay=250;
  POne = new Player(1);
  PTwo = new Player(2);
  PThree = new Player(3);
  PFour = new Player(4);
  envi= new Environment();
  balltest= new MBall();
  balltest->update();
  envi->paddle_count=0;
  envi->x_max=23;
  envi->y_max=23;
  envi->register_paddle(POne);
  envi->register_paddle(PTwo);
  envi->register_paddle(PFour);
  envi->register_paddle(PThree);
  envi->register_ball(balltest);
  //-----------second ball-------
  envi1= new Environment();
  balltest1= new MBall();
  balltest1->update();
  envi1->paddle_count=0;
  envi1->x_max=23;
  envi1->y_max=23;
  envi1->register_paddle(POne);
  envi1->register_paddle(PTwo);
  envi1->register_paddle(PFour);
  envi1->register_paddle(PThree);
  envi1->register_ball(balltest1);
  Serial.begin(9600);
  delay(100);
}

String getStringFromSerial() //returns 5 digit String of digits
{
  char charVal[6];
  String stringVal = "-1";
  long int val = -1;
  if(Serial.available())
  {
    //val = Serial.parseInt();
    stringVal = Serial.readStringUntil('a');
    
    val = atol(stringVal.c_str());
    if(val > 9999 && val < 999999) //five / six digits is acceptable
    {
      //itoa(val,charVal,10);
      //stringVal = charVal;
      MODE = val / 10000;
      return stringVal;
    }
  }
  return "-1"; //nothing entered
}

void setXYValues(String val)
{
  char* x = new char[3];
  x[0] = val[1];
  x[1] = val[2];
  x[2] = '\0';
  char* y = new char[3];
  y[0] = val[3];
  y[1] = val[4];
  y[2]= '\0';
  X = atol(x);
  Y = atol(y);
  delete[] x;
  delete[] y;
}

long int getPlayer(String val)
{
   return atol(val.c_str())%10;
}

long int getCommand(String val)
{
  char* x = new char[3];
  x[0] = val[2];
  x[1] = val[3];
  x[3] = '\0';
  long int value = atol(x);
  delete[] x;
  return value;
}

void doCommand(int player, int command)
{
  boolean invalid = false;
  Player *p;
  switch(player)
  {
     case 1:
       p = POne;
       break;
     case 2:
       p = PTwo;
       break;
     case 3:
       p = PThree;
       break;
     case 4:
       p = PFour;
       break;
     default:
       invalid = true;
       break;
  }
  if(!invalid)
  switch(command)
  {
    case CMD_UP:
      p->moveUpOrLeft();
      break;
    case CMD_DOWN:
      p->moveDownOrRight();
      break;
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

void setLed(long int y,long int x, boolean on)
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


void demoTest()
{
  for(int k = 0; k < 2; k++)
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
}

void clearDisplay()
{
  lc1.clearDisplay(0);
  for(int i = 0; i < 8; i++)
  {
    lc.clearDisplay(i);
  }
  resetMatrix();
}

void setPlayers(String number)
{
  switch(getPlayer(number))
  {
    case 1:
      PTwo->lose();
      PThree->lose();
      PFour->lose();
      break;
    case 2:
      PThree->lose();
      PFour->lose();
      break;
    case 3:
      PFour->lose();
      break;
    case 4:
      break;
  }
}

void playerLost(String number)
{
  switch(getPlayer(number))
  {
    case 1:
      POne->lose();
      break;
    case 2:
      PTwo->lose();
      break;
    case 3:
      PThree->lose();
      break;
    case 4:
      PFour->lose();
      break;
    default:
      break;
  }
}

void clear_ball(Environment* envi)
{
  long int x=envi->ball->x;
  long int y=envi->ball->y;
  if ( x==0 || x==23 || y==0 || y==23)
  {
    // dont do anything cause im a paddle
  }
  else
  {
    setLed(x,y,false);
  }
  
}
void software_reboot()
{
  wdt_enable(WDTO_15MS);
  while(1)
  {
  }
}
void update_screen(Environment* envi)
{
  long int x=(envi->ball)->x;
  long int y=(envi->ball)->y;
  setLed(x,y,true);
}

void loop()
{
  String number = getStringFromSerial(); //also Sets MODE //uncomment this line
  //game code
  if ( envi->paddles[0]->lost== true && envi->paddles[1]->lost== true && envi->paddles[2]->lost== true && envi->paddles[3]->lost== true)
  {
    software_reboot();
  }
  // game loop for running 4 player pong ball speeds up as the game proceeds 
  if(abs(millis() - StartTime) > gamedelay && balloff==false)
  {
    clear_ball(envi);
    envi->tick();
    update_screen(envi);
    clear_ball(envi1);
    envi1->tick();
    update_screen(envi1);
    StartTime = millis();
    if( gamedelay > 40)
    {
      gamedelay=gamedelay-1;
    }
  }
  
  int player = -1;
  if(number != "-1")
  {
    switch(MODE)
    {
      case 1: //LED_POSITION
        if(!balloff)
        {
          balloff= true;
          clear_ball(envi);
          clear_ball(envi1);
        }
        setXYValues(number);
        setLed(X,Y,true);
        break;
      case 2: //MULTIPLAYER
        multiPlayerLoop(number);
        break;
      case 3: //DEMO
        if(!balloff)
        {
          balloff= true;
          clear_ball(envi);
          clear_ball(envi1);
        }
        demoTest();
        break;
      case 4: //SET PLAYERS
        setPlayers(number);
        break;
      case 5: //LOSE PLAYER
        playerLost(number);
        break;
      case 6:// TURN OFF BALLS
        if(!balloff)
        {
          balloff= true;
          clear_ball(envi);
          clear_ball(envi1);
        }
        break;// TURN ON BALLS 
      case 7:
        balloff= false;
        break;
      case 8: // RESET THE GAME 
        software_reboot();
        break;
      case 9: //TURNOFFLED
        setXYValues(number);
        setLed(X,Y,false);
        break;
      case 10:
        if(!balloff)
        {
          balloff= true;
          clear_ball(envi);
          clear_ball(envi1);
        }
        clearDisplay();
        break;
      default:
        break;
    }
  }
}


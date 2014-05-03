#ifndef Player_h
#define Player_h

const int PADDLE_SIZE = 3;
void setLed(long int x,long int y, boolean on); //declaration

class Player
{
public:
  Player(int pNum) : playerNum(pNum) 
  { 
   // memset(this, 0, sizeof(this));
    lost = false;
    memset(xCoords,0,sizeof(int)*PADDLE_SIZE);
    memset(yCoords,0,sizeof(int)*PADDLE_SIZE);
    switch(playerNum)
    {
      case 1:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = j;
          yCoords[i] = 23;
        }
        break;
      case 2:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = j;
          yCoords[i] = 0;
        }
        break;
      case 3:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = 23;
          yCoords[i] = j;
        }
        break;
      case 4:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = 0;
          yCoords[i] = j;
        }
        break;
      default:
        break;
    }
    for(int i = 0; i < PADDLE_SIZE; i++)
    {
      setLed(xCoords[i],yCoords[i],true);
    }
  }
  
  const int playerNum;
  int xCoords[PADDLE_SIZE];
  int yCoords[PADDLE_SIZE];
  boolean lost;
  void moveUpOrLeft() //orUp
  {
    if(!lost)
    switch(playerNum)
    {
      case 1: //move left
      case 2:
        if(xCoords[0] > 0)
        {
          setLed(xCoords[PADDLE_SIZE-1],yCoords[0],false);
          setLed(xCoords[0]-1,yCoords[0],true);
          for(int i = 0; i < PADDLE_SIZE; i++)
            xCoords[i]--;
        }
        break;
      case 3: //move Up
      case 4:
        if(yCoords[0] > 0)
        {
          setLed(xCoords[0],yCoords[PADDLE_SIZE-1],false);
          setLed(xCoords[0],yCoords[0]-1,true);
          for(int i = 0; i < PADDLE_SIZE; i++)
            yCoords[i]--;
        }
        break;
    }
  }
  void moveDownOrRight()
  {
    if(!lost)
    switch(playerNum)
    {
      case 1: //move Right
      case 2:
        if(xCoords[PADDLE_SIZE-1] < 23)
        {
          setLed(xCoords[0],yCoords[0],false);
          setLed(xCoords[PADDLE_SIZE-1]+1,yCoords[0],true);
          for(int i = 0; i < PADDLE_SIZE; i++)
            xCoords[i]++;
        }
        break;
      case 3: //move Down
      case 4:
        if(yCoords[PADDLE_SIZE-1] < 23)
        {
          setLed(xCoords[0],yCoords[0],false);
          setLed(xCoords[0],yCoords[PADDLE_SIZE-1]+1,true);
          for(int i = 0; i < PADDLE_SIZE; i++)
            yCoords[i]++;
        }
        break;
    }
  }
  void lose()
  {
    lost = true;
    switch(playerNum)
    {
      case 1:
        for(int i = 0; i < 24; i++)
        {
          setLed(i,23,true);
        }
        break;
      case 2:
        for(int i = 0; i < 24; i++)
        {
          setLed(i,0,true);
        }
        break;
      case 3:
        for(int i = 0; i < 24; i++)
        {
          setLed(23,i,true);
        }
        break;
      case 4:
        for(int i = 0; i < 24; i++)
        {
          setLed(0,i,true);
        }
        break;
      default:
        break;
    }
  }
  
  static void playersReady(int numPlayers)
  {
    switch(numPlayers)
    {
      case 1:
        for(int i = 0; i < 23; i++)
        {
          setLed(0,i,true); //left line
          setLed(23,i,true); //right line
          setLed(i,0,true); //top line
        }
        break;
      case 2:
        for(int i = 1; i < 23; i++)
        {
          setLed(0,i,true); //left
          setLed(23,i,true); //right
        }
        break;
      case 3:
        for(int i = 1; i < 23; i++)
        {
          setLed(0,i,true);//left
        }
        break;
      case 4:
        break;
      default:
        break;
    }
  }
};

#endif

#ifndef Player_h
#define Player_h

const int PADDLE_SIZE = 5;
void setLed(int x,int y, boolean on); //declaration

class Player
{
public:
  Player(int pNum) : playerNum(pNum)
  { 
    //playerNum = PLAYERNUMBER++;
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
  void moveUpOrLeft() //orUp
  {
    switch(playerNum)
    {
      case 1: //move left
      case 2:
        if(xCoords[0] > 0)
        {
          setLed(xCoords[4],yCoords[0],false);
          setLed(xCoords[0]-1,yCoords[0],true);
          for(int i = 0; i < 5; i++)
            xCoords[i]--;
        }
        break;
      case 3: //move Up
      case 4:
        if(yCoords[0] > 0)
        {
          setLed(xCoords[0],yCoords[4],false);
          setLed(xCoords[0],yCoords[0]-1,true);
          for(int i = 0; i < 5; i++)
            yCoords[i]--;
        }
        break;
    }
  }
  void moveDownOrRight()
  {
    switch(playerNum)
    {
      case 1: //move Right
      case 2:
        if(xCoords[4] < 23)
        {
          setLed(xCoords[0],yCoords[0],false);
          setLed(xCoords[4]+1,yCoords[0],true);
          for(int i = 0; i < 5; i++)
            xCoords[i]++;
        }
        break;
      case 3: //move Down
      case 4:
        if(yCoords[4] < 23)
        {
          setLed(xCoords[0],yCoords[0],false);
          setLed(xCoords[0],yCoords[4]+1,true);
          for(int i = 0; i < PADDLE_SIZE; i++)
            yCoords[i]++;
        }
        break;
    }
  }
  static void PlayersReady(int numPlayers, int** Matrix)
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
        for(int i = 0; i < 23; i++)
        {
          setLed(0,i,true); //left
          setLed(23,i,true); //right
        }
        break;
      case 3:
        for(int i = 0; i < 23; i++)
        {
          setLed(0,i,true);//left
        }
        break;
      case 4:
        break;
    }
  }
};

#endif

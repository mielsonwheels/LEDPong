#ifndef Player_h
#define Player_h

const int PADDLE_SIZE = 5;

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
          xCoords[i] = 23;
          yCoords[i] = j;
        }
        break;
      case 2:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = 0;
          yCoords[i] = j;
        }
        break;
      case 3:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = j;
          yCoords[i] = 23;
        }
        break;
      case 4:
        for(int i = 0, j = 9; i < PADDLE_SIZE; i++, j++)
        {
          xCoords[i] = j;
          yCoords[i] = 0;
        }
        break;
      default:
        break;
    }
  }
  const int playerNum;
  int xCoords[5];
  int yCoords[5];
  void moveUpOrLeft() //orUp
  {
    switch(playerNum)
    {
      case 1: //move left
      case 2:
        if(yCoords[0] > 0)
          yCoords[4] = yCoords[0] - 1;
        break;
      case 3: //move Up
      case 4:
        if(xCoords[0] > 0)
          xCoords[4] = xCoords[0] -1;
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
          xCoords[0] = xCoords[4] + 1;
        break;
      case 3: //move Down
      case 4:
        if(yCoords[4] < 23)
          yCoords[0] = yCoords[4] + 1;
        break;
    }
  }
};

#endif

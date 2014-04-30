#ifndef Ball_h
#define Ball_h
void setLed(long int x, long int y, boolean on); //declaration
class Ball
{
public:
  int xPos;
  int yPos;
  long int DELAY;
  long int previousTime;
  int angle;
  Ball(long int d) {xPos = 12; yPos = 12; DELAY = d; previousTime = 0; angle = 90;}
  
  void move(int Angle)
  {
    int x = xPos;
    int y = yPos;
    switch(Angle)
    {
      case 90: //UP
        y--;
        break;
      case 270: //DOWN
        y++;
        break;
      case 180: //LEFT
        x--;
        break;
      case 0: //RIGHT
        x++;
        break;
      case 45: //UP RIGHT
        y--; x++;
        break;
      case 315: //DOWN RIGHT
        x++; y++;
        break;
      case 135: //UP LEFT
        x--; y--;
        break;
      case 225: //DOWN LEFT
        x++; y--;
        break;
      default:
        break;
    }
    if((millis() - previousTime) > DELAY)
    {
      setLed(xPos,yPos,false);
      setLed(x,y,true);
      xPos = x;
      yPos = y;
      previousTime = millis();
    }
  }
};

#endif

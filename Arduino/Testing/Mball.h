#ifndef _MBALL_H
#define _MBALL_H

#include "Player.h"

class MBall {
public:
    boolean go_x();
    boolean go_y();
    
    void flip_x();
    void flip_y();
    MBall();
   void update();
   boolean can_move_x();
   boolean can_move_y();
   int angle;
   long int x_dir, y_dir;
   long int x, y;
};

MBall::MBall() {
  randomSeed(analogRead(0));
  x=random(4,20);
  y=random(4,20);
  angle=(random(0,8)*45);
}

boolean MBall::go_x() {
    x += x_dir;
    return true;
}

boolean MBall::go_y() {
    y += y_dir;
    return true;
}

boolean MBall::can_move_x() {
    if (x_dir + x > 23 || x_dir + x < 0) {
      return false;
    }
}

boolean MBall::can_move_y() {
    if (y_dir + y > 23 || y_dir + y < 0) {
      return false;
    }
}

void MBall::update()
{
      switch(angle)
    {
      case 90: //UP
        y_dir=-1; x_dir=0;
        break;
      case 270: //DOWN
        y_dir=1; x_dir=0;
        break;
      case 180: //LEFT
        x_dir=-1; y_dir=0;
        break;
      case 0: //RIGHT
        x_dir=1; y_dir=0;
        break;
      case 360: //RIGHT
        x_dir=1; y_dir=0;
        break;
      case 45: //UP RIGHT
        y_dir=-1; x_dir=1;
        break;
      case 315: //DOWN RIGHT
        x_dir=1; y_dir=1;
        break;
      case 135: //UP LEFT
        x_dir=-1; y_dir=-1;
        break;
      case 225: //DOWN LEFT
        x_dir=-1; y_dir=1;
        break;
      default:
        break;
    }
}

#endif


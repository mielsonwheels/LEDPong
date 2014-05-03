#ifndef _ENV_H
#define _ENV_H

#include "Player.h"
#include "Mball.h"
class Environment {
  public:
    Environment();
    
    boolean register_ball(MBall* _ball);
    boolean register_paddle(Player* _player);
    
    boolean tick();
    int paddle_count;
    int x_max ;
    int y_max;
    Player* paddles[4]; 
    MBall* ball;
};
Environment::Environment() {
      memset(this, 0, sizeof(this));
      x_max = 23;
      y_max = 23;
      paddle_count = 0;
      //paddles = 0;
      ball = 0;
}
boolean Environment::register_paddle(Player* _player) {
    
    paddles[paddle_count] = _player;
    
    paddle_count++;
    return true;
}

boolean Environment::register_ball(MBall* _ball) {
   if (ball) {
      return false;
   }
   
   ball = _ball;
   return true;
}

boolean Environment::tick() {
   // Check paddle collisions
   // check for losers
   //----------------------------------------player one----------------------------------------------------------py
    if(ball->x != 23 && ball->y >= 22 ) 
    {
       if ( ball->x == paddles[0]->xCoords[0]  )// left paddle hit
       {
         switch (ball->angle)
         {
           case 270:
           ball->angle=135;
           ball->update();
           break;
           case 315:
           ball->angle=90;
           ball->update();
           break;
           case 225:
           ball->angle=135;
           ball->update();
           break;
         }
       }
       else if ( ball->x == paddles[0]->xCoords[1] || paddles[0]->lost==true )// middle paddle hit
       {
         switch (ball->angle)
         {
           case 270:
           ball->angle=90;
           ball->update();
           break;
           case 315:
           ball->angle=45;
           ball->update();
           break;
           case 225:
           ball->angle=135;
           ball->update();
           break;
         }
       }
        else if ( ball->x == paddles[0]->xCoords[2] )// left paddle hit
       {
         switch (ball->angle)
         {
           case 270:
           ball->angle=45;
           ball->update();
           break;
           case 315:
           ball->angle=45;
           ball->update();
           break;
           case 225:
           ball->angle=90;
           ball->update();
           break;
         }
       }
       else 
       {
         switch (ball->angle)
         {
           case 270:
           ball->angle=90;
           ball->update();
           paddles[0]->lose();
           break;
           case 315:
           ball->angle=45;
           ball->update();
           paddles[0]->lose();
           break;
           case 225:
           ball->angle=135;
           ball->update();
           paddles[0]->lose();
           break;
         }
       }
       
    }
     //----------------------------------------player two----------------------------------------------------------py
    if(ball->x != 0 && ball->y <= 1 ) 
    {
       if ( ball->x == paddles[1]->xCoords[0])// left paddle hit
       {
         switch (ball->angle)
         {
           case 90:
           ball->angle=225;
           ball->update();
           break;
           case 45:
           ball->angle=270;
           ball->update();
           break;
           case 135:
           ball->angle=225;
           ball->update();
           break;
         }
       }
       else if ( ball->x == paddles[1]->xCoords[1] || paddles[1]->lost==true )// middle paddle hit
       {
         switch (ball->angle)
         {
           case 90:
           ball->angle=270;
           ball->update();
           break;
           case 45:
           ball->angle=315;
           ball->update();
           break;
           case 135:
           ball->angle=225;
           ball->update();
           break;
         }
       }
        else if ( ball->x == paddles[1]->xCoords[2] )// left paddle hit
       {
         switch (ball->angle)
         {
           case 90:
           ball->angle=315;
           ball->update();
           break;
           case 45:
           ball->angle=315;
           ball->update();
           break;
           case 135:
           ball->angle=270;
           ball->update();
           break;
         }
       }
       else 
       {
         switch (ball->angle)
         {
           case 90:
           ball->angle=270;
           ball->update();
           paddles[1]->lose();
           break;
           case 45:
           ball->angle=315;
           ball->update();
           paddles[1]->lose();
           break;
           case 135:
           ball->angle=225;
           ball->update();
           paddles[1]->lose();
           break;
         }
       }
       
    }
     //----------------------------------------player three----------------------------------------------------------py
    if(ball->y != 23 && ball->x <= 1 ) 
    {
       if ( ball->y == paddles[2]->yCoords[0] )// left paddle hit
       {
         switch (ball->angle)
         {
           case 135:
           ball->angle=45;
           ball->update();
           break;
           case 180:
           ball->angle=45;
           ball->update();
           break;
           case 225:
           ball->angle=0;
           ball->update();
           break;
         }
       }
       else if ( ball->y == paddles[2]->yCoords[1] || paddles[2]->lost==true )// middle paddle hit
       {
         switch (ball->angle)
         {
           case 135:
           ball->angle=45;
           ball->update();
           break;
           case 180:
           ball->angle=0;
           ball->update();
           break;
           case 225:
           ball->angle=315;
           ball->update();
           break;
         }
       }
        else if ( ball->y == paddles[2]->yCoords[2] )// left paddle hit
       {
         switch (ball->angle)
         {
           case 135:
           ball->angle=0;
           ball->update();
           break;
           case 180:
           ball->angle=315;
           ball->update();
           break;
           case 225:
           ball->angle=315;
           ball->update();
           break;
         }
       }
       else 
       {
         switch (ball->angle)
         {
           case 135:
           ball->angle=45;
           ball->update();
           paddles[2]->lose();
           break;
           case 180:
           ball->angle=315;
           ball->update();
           paddles[2]->lose();
           break;
           case 225:
           ball->angle=315;
           ball->update();
           paddles[2]->lose();
           break;
         }
       }
       
    }
         //----------------------------------------player four----------------------------------------------------------py
    if(ball->y != 0 && ball->x >= 22 ) 
    {
       if ( ball->y == paddles[3]->yCoords[0])// left paddle hit
       {
         switch (ball->angle)
         {
           case 45:
           ball->angle=135;
           ball->update();
           break;
           case 0:
           ball->angle=135;
           ball->update();
           break;
           case 315:
           ball->angle=180;
           ball->update();
           break;
         }
       }
       else if ( ball->y == paddles[3]->yCoords[1] || paddles[3]->lost==true )// middle paddle hit
       {
         switch (ball->angle)
         {
           case 45:
           ball->angle=135;
           ball->update();
           break;
           case 0:
           ball->angle=180;
           ball->update();
           break;
           case 315:
           ball->angle=225;
           ball->update();
           break;
         }
       }
        else if ( ball->y == paddles[3]->yCoords[2] )// left paddle hit
       {
         switch (ball->angle)
         {
           case 45:
           ball->angle=180;
           ball->update();
           break;
           case 0:
           ball->angle=225;
           ball->update();
           break;
           case 315:
           ball->angle=225;
           ball->update();
           break;
         }
       }
       else 
       {
         switch (ball->angle)
         {
           case 45:
           ball->angle=135;
           ball->update();
           paddles[3]->lose();
           break;
           case 0:
           ball->angle=225;
           ball->update();
           paddles[3]->lose();
           break;
           case 315:
           ball->angle=225;
           ball->update();
           paddles[3]->lose();
           break;
         }
       }
       
    }
   // Move ball 
   ball->go_y();
   ball->go_x();
   

   return false;
}

#endif

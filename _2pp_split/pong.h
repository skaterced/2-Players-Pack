#ifndef pong_h
#define pong_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

#define downWall 64
#define upWall 0
#define scoreTimerInit 60

class Balle {
  public :
    int x,y, vx,vy;
    void affiche (void);
    void stop (void);
    void init (void);
    Balle (void);
    Balle (int X, int Y, int vx, int vy);
};
Balle::Balle(int X, int Y, int vx, int vy)
{
  this->x=X;
  this->y=Y;
  this->vx=vx;
  this->vy=vy;  
}
Balle::Balle(void)  //not working
{
  this->init(); 
}
void Balle::init(void){  //to do: add random
  this->x=64;
  this->y=30;
  //srand(p1.y);
  int temp=-2+rand()%5;
  if (0==temp){ 
    if (rand()%2>=1){
      temp++;
    }
    else {
      temp--;
    }
  }
  this->vx=temp;
  temp=-2
  +rand() %5;
  this->vy=temp;
}
void Balle::affiche (void)
{
  arduboy.fillCircle(this->x,this->y,2);
}
void Balle::stop(void){
  this->vx=0;
  this->vy=0;
}

//class Balle balle();
class Balle balle(12,20,1,-2);

void playPong(){    
  arduboy.drawRect(0,0,128,64,1);
  arduboy.fillRect(p1.x,p1.y,2,p1.length,1);
  arduboy.fillRect(p2.x,p2.y,2,p2.length,1);
  
 if (arduboy.pressed(P1_LEFT))
  {
    if (p1.y>upWall+1){
      p1.y--;
    }
  }
 if (arduboy.pressed(P1_RIGHT))
  {
    if (p1.y+p1.length<downWall-1){
      p1.y++;
    }
  }
  
 if (arduboy.pressed(P2_RIGHT))
  {
    if (p2.y>upWall+1){
      p2.y--;
    }
  }
 if (arduboy.pressed(P2_LEFT))
  {
    if (p2.y+p2.length<downWall-1){
      p2.y++;
    }
  }
  
  if (scoreTimer>0){ // *********** someone scored ****
    if (0<=scoreTimer--){
      balle.init();
    }
    arduboy.setCursor(50,45);
    arduboy.print(p1.score);
    arduboy.print(" - ");
    arduboy.print(p2.score);
  }
  // *************  calculate Ball position
  else {
    balle.x+=balle.vx;
    balle.y+=balle.vy;
    
    if (balle.y<upWall){ // upper wall
      balle.y*=-1;
      balle.vy*=-1;
    }
    if (balle.y>downWall){ // down wall
      balle.y=balle.y-2*(balle.y-downWall);
      balle.vy*=-1;
    }
    
    if (0>=balle.x)
    {
      balle.stop();
      p2.score++;
      scoreTimer=scoreTimerInit;
    }
    if (128<=balle.x)
    {
      balle.stop();
      p1.score++;
      scoreTimer=scoreTimerInit;
    }      
    if (balle.x<p1.x+2){
      if ((balle.y>p1.y)&&(balle.y<p1.y+p1.length)){ //  left player
        balle.x=balle.x+2*(p1.x+2-balle.x);
        balle.vx*=-1;
      }
      else if (balle.y==p1.y) {
        balle.vy=balle.vy==0 ? -1 : abs(balle.vy)*(-1);
        balle.vx*=-1;
      }
      else if (balle.y==p1.y+p1.length) {
        balle.vy=balle.vy==0 ? 1 : abs(balle.vy);
        balle.vx*=-1;
      }
    }
    if (balle.x>p2.x){
      if ((balle.y>p2.y)&&(balle.y<p2.y+p2.length)){ //  right player
        balle.x=balle.x+2*(p2.x+2-balle.x);
        balle.vx*=-1;
      }
      else if (balle.y==p2.y) {
        balle.vy=balle.vy==0 ? -1 : abs(balle.vy)*(-1);
        balle.vx*=-1;
      }
      else if (balle.y==p2.y+p2.length) {
        balle.vy=balle.vy==0 ? 1 : abs(balle.vy);
        balle.vx*=-1;
      }
    }
  }
  balle.affiche();
}

#endif

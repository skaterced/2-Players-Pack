#ifndef trace_h
#define trace_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

#define TRACE_WAIT_ROUND 2000
//#define TRACE_FPS 10

#if (THIS_IS_REAL_HARDWARE == 1) //don't think it works...
#define TRACE_FPS 5
#else
#define TRACE_FPS 10
#endif


void newTraceGame(void){
  arduboy.clear();
  arduboy.setCursor(40,30);
  arduboy.print(p1.score);
  arduboy.print(F(" : "));
  arduboy.print(p2.score);
  arduboy.display();
  delay(TRACE_WAIT_ROUND);
  arduboy.clear();
  p1.x=10;
  p1.y=30;
  p1.dir=1;
  p2.x=118;
  p2.y=30;
  p2.dir=3;
  arduboy.drawRect(0,0,128,64,1);
}

void playTrace(){
  if (arduboy.justPressed(P1_LEFT)){
    if (0==p1.dir){
      p1.dir=3;
    }
    else {
      p1.dir--;
    }
  }
  if (arduboy.justPressed(P1_RIGHT)){
    p1.dir++;
    if (p1.dir>3){
      p1.dir=0;
    }
  }
  if (arduboy.justPressed(P2_LEFT)){
    if (0==p2.dir){
      p2.dir=3;
    }
    else {
      p2.dir--;
    }
  }
  if (arduboy.justPressed(P2_RIGHT)){
    p2.dir++;
    if (p2.dir>3){
      p2.dir=0;
    }
  }    
    switch(p1.dir){   //player 1 moves
      case 0:
        p1.y--;
      break;
      case 1:
        p1.x++;
      break;
      case 2:
        p1.y++;
      break;
      case 3:
        p1.x--;
      break;
    }
    switch(p2.dir){   //player 2 moves
      case 0:
        p2.y--;
      break;
      case 1:
        p2.x++;
      break;
      case 2:
        p2.y++;
      break;
      case 3:
        p2.x--;
      break;
    }
    
    if((p1.x==p2.x)&&(p1.y==p2.y)){ //draw
      p1.score++;
      p2.score++;
      newTraceGame();
    }
    
    if(arduboy.getPixel(p1.x,p1.y)){
      //arduboy.print("BLAM!");  //for now...
      p2.score++;
      newTraceGame();
    }
    if(arduboy.getPixel(p2.x,p2.y)){
      //arduboy.print("BIM!");  //for now...
      p1.score++;
      newTraceGame();
    }
    arduboy.drawPixel(p1.x,p1.y,1);
    arduboy.drawPixel(p2.x,p2.y,1);  
}

#endif

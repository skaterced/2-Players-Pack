#ifndef go_h
#define go_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

void drawGo(void){
  arduboy.fillRect(38,0,73,65,1);
  for (int i=0; i<casesCol; i++){
    arduboy.drawLine(leftBorder+i*casesLength,0,leftBorder+i*casesLength,65,0); //vert
    arduboy.drawLine(leftBorder,upBorder+i*casesHeight,105,upBorder+i*casesHeight,0); //hz
  }
}

playGo(){
/*if (arduboy.justPressed(UP_BUTTON)){
      if (p1.y>8){
        p1.y-=8;
      }
    }
    if (arduboy.justPressed(DOWN_BUTTON)){
      if (p1.y<56){ 
        p1.y+=8;
      }
    }
    if (arduboy.justPressed(RIGHT_BUTTON)){
      if (p1.x<98){
        p1.x+=8;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON)){
      if (p1.x>50){
        p1.x-=8;
      }
    }*/
    SelectorManagment();
    if (arduboy.justPressed(B_BUTTON)){
      int temp=getIndice(p1.x,p1.y);
      switch (symbolArray[temp]){        
        case WHITE_STONE :
          symbolArray[temp]= 0;
          p2.score--;
        break;
        case BLACK_STONE :
          symbolArray[temp]= WHITE_STONE;
          p1.score--;
          p2.score++;
        break; 
        default :
          symbolArray[temp]= WHITE_STONE;          
          p2.score++;
        break;       
      }
    }
    if (arduboy.justPressed(A_BUTTON)){
      int temp=getIndice(p1.x,p1.y);
      switch (symbolArray[temp]){
        case BLACK_STONE :
          symbolArray[temp]= 0;
          p1.score--;
        break;
        case WHITE_STONE :
          symbolArray[temp]= BLACK_STONE;
          p2.score--;
          p1.score++;
        break;
        default :
          symbolArray[temp]= BLACK_STONE;          
          p1.score++;
        break;
      }
    }
    drawGo();
    turnUpdate();
    drawStones();
 
    if (blinkTimer++>10){
      blinkTimer=0;
      blink=!blink;
    }
    drawSelector(getIndice(p1.x,p1.y));
    
  }

#endif


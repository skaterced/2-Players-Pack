#ifndef reflx_h
#define reflx_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

#define PRESSED_DOWN true
#define PRESSED_UP false

bool arrowInverted=false;
bool boldArrowInverted=false;
bool pointDown=false;

void newReflXGame(void){
  arduboy.clear();
  arduboy.setCursor(0,0);
  arduboy.print(F("Next Round :"));
  arduboy.drawChar(1,11,24,1,0,1);
  arduboy.drawChar(8,11,25,1,0,1);
  arduboy.setCursor(16,11);
  if (random(100)>=50){
    arduboy.print(F(" are normal"));
    arrowInverted=false;
  }
  else{
    arduboy.print(F(" are inverted"));
    arrowInverted=true;
  }
  arduboy.fillRect(0,21,15,8,1);
  arduboy.drawChar(1,21,24,0,1,1);
  arduboy.drawChar(8,21,25,0,1,1);
  arduboy.setCursor(16,20);
  if (random(100)>=50){
    arduboy.print(F(" are normal"));
    boldArrowInverted=false;
  }
  else{
    arduboy.print(F(" are inverted"));
    boldArrowInverted=true;
  }
  arduboy.setCursor(0,45);
  arduboy.print(F("Press both 'down'"));
  arduboy.setCursor(0,55);
  arduboy.print(F("buttons when ready"));
  arduboy.display();
  while (!(arduboy.pressed(P1_RIGHT)&&arduboy.pressed(P2_LEFT))){
    delay(10);
  }
  arduboy.clear();
  timer=10+random(600);
}

bool checkPressed(bool down){
  if (selected){ //bold arrow
    if (!boldArrowInverted){
      if (down==pointDown){
        return true;
      }
      else return false;
    }
    else { //bold arrow is inverted
      if (down!=pointDown){
        return true;
      }
      else return false;
    }
  }
  else { //normal arrow
    if (!arrowInverted){
      if (down==pointDown){
        return true;
      }
      else return false;
    }
    else { //bold arrow is inverted
      if (down!=pointDown){
        return true;
      }
      else return false;
    }
  }
}

void playReflx(){
uint8_t scoreChange=0; // ( 0 no change, 1 correct, 2 false ) for p1 <<2 for p2
  if (!((arduboy.pressed(DOWN_BUTTON))||(arduboy.pressed(UP_BUTTON))||(arduboy.pressed(A_BUTTON))||(arduboy.pressed(B_BUTTON)))){
    timer--;
  }
  if (0==timer){
    if (random(100)>50){
      selected=false; // normal arrow
      if (random(100)>50){
        pointDown=false;
        arduboy.drawChar(55,22,24,1,0,3);
      }
      else {
        pointDown=true;
        arduboy.drawChar(55,22,25,1,0,3);
      }
    }
    else {
      selected=true;
      if (random(100)>50){
        pointDown=false;
        arduboy.drawChar(52,22,0,0,1,3);  
        arduboy.drawChar(55,22,24,0,1,3);
      }
      else {
        pointDown=true;
        arduboy.drawChar(52,22,0,0,1,3);
        arduboy.drawChar(55,22,25,0,1,3);
      }
    }
  }
  if ((timer<0)&&(0==scoreChange)){
    if ((arduboy.justPressed(DOWN_BUTTON)||arduboy.justPressed(UP_BUTTON))||(arduboy.justPressed(B_BUTTON)||arduboy.justPressed(A_BUTTON))) { 
      if (arduboy.justPressed(P1_RIGHT)||arduboy.justPressed(P1_LEFT)) { //only p1 has pressed
         if (arduboy.justPressed(P1_RIGHT)){
           if (checkPressed(PRESSED_DOWN)){
             scoreChange+=1;
           }
           else {
             scoreChange+=2;
           }
         }
         else if (arduboy.justPressed(P1_LEFT)){
           if (checkPressed(PRESSED_UP)){
             scoreChange+=1;
           }
           else {
             scoreChange+=2;
           }
         }
      }
      if (arduboy.justPressed(P2_RIGHT)||arduboy.justPressed(P2_LEFT)) { //only p1 has pressed
        if (arduboy.justPressed(P2_LEFT)){
          if (checkPressed(PRESSED_DOWN)){
          scoreChange+=4;
          }
          else {
          scoreChange+=8;
          }
        }
        else if (arduboy.justPressed(P2_RIGHT)) {
          if (checkPressed(PRESSED_UP)){
           scoreChange+=4;
          }
          else {
           scoreChange+=8;
          }
        }
      }
    }
    if (scoreChange!=0){
      if ((scoreChange&2)==2){
        p1.score--;
        arduboy.drawChar(2,45,'x',1,0,1);
      }
      if ((scoreChange&1)==1){
        p1.score++;
        //arduboy.drawChar(2,45,'v',1,0,1);
        arduboy.drawLine(3,47,5,49,1);
        arduboy.drawLine(5,49,9,40,1);
      }
      if ((scoreChange&4)==4){
        p2.score++;
        //arduboy.drawChar(115,45,'v',1,0,1);
        arduboy.drawLine(117,47,119,49,1);
        arduboy.drawLine(119,49,123,40,1);
      }
      if ((scoreChange&8)==8){
        p2.score--;
        arduboy.drawChar(115,45,'x',1,0,1);
      }
      arduboy.setCursor(49,10);
      arduboy.print(p1.score);
      arduboy.print(" : ");
      arduboy.print(p2.score);
      //arduboy.print(scoreChange);
        
      arduboy.display();
      delay(3000);
      newReflXGame();
    }
  }
}

#endif

#ifndef mill_h
#define mill_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

#define EMPTY 0


void drawMill(void){
  arduboy.fillRect(50,0,65,65,1);
  arduboy.drawRect(58,8,49,49,0);
  arduboy.drawRect(66,16,33,33,0);
  arduboy.drawRect(74,24,17,17,0);
  arduboy.drawLine(82,8,82,56,0);
  arduboy.drawLine(58,32,105,32,0);
  arduboy.fillRect(75,25,15,15,1);  
}

bool checkMill(int ind, int color){ //check if same line (or col) as ind, has two other same colored stones
  uint8_t xR=0,xC=0;  //There you were you filthy bug!
  //int temp=0;
  for (int i=0; i<49; i++){ // check col.
    if (ind%7==i%7){
      if (i%7==3) {
        if ((24-i)*(24-ind)>0){ // check if the 3 stones are on the same side 
          if (stoneArray[i]==color)
            xC++;
        }
      }
      else {
        if (stoneArray[i]==color)
          xC++;
      }
    }
    if (ind/7==i/7) { // check rows
      if (i/7==3){
        if ((24-i)*(24-ind)>0){ // check if the 3 stones are on the same side 
          if (stoneArray[i]==color)
            xR++;
        }
      }   
      else {
        if (stoneArray[i]==color)
          xR++;
      }
    }
  }
  return ((xR==3)||(xC==3));
}

bool checkLegalMove(int i1, int i2, bool canJump){
  if (stoneArray[i2]!=EMPTY){
    return false;
  }
  if (canJump){
    return true; 
  }
  int temp=i1/7;
  if (i2/7==temp){ //same row
    if ((temp==0)||(temp==6)){
      if (abs(i1-i2)==3){
        return true;
      }
    }
    else if ((temp==1)||(temp==5)){
      if (abs(i1-i2)==2){
        return true;
      }
    }
    else if ((temp==2)||(temp==4)){
      if ((i2%7>1)&&(i2%7<5)&&(abs(i1-i2)==1)){
        return true;
      }
    }
    else if (temp==3){ // temp==3 stoneArray[22]=4
      if (abs(i1-i2)==1){
        return true;
      }
    }
  }
  temp=i1%7;
  if (i2%7==temp){ // same col.
    if ((temp==0)||(temp==6)){
      if (abs(i1/7-i2/7)==3){
        return true;
      }
    }
    else if ((temp==1)||(temp==5)){
      if (abs(i1/7-i2/7)==2){
        return true;
      }
    }
    else if ((temp==2)||(temp==4)){
      if ((i2/7>1)&&(i2/7<5)&&(abs(i1/7-i2/7)==1)){
        return true;
      }
    }
    else if (temp==3){ // temp==3 stoneArray[22]=4
      if (abs(i1/7-i2/7)==1){
        return true;
      }
    }
  }
  return false;
}

bool checkLose(int color){
  int temp=0;
  for (int i=0;i<49;i++){
    if (stoneArray[i]==color){
      temp++;
      for (int j=0;j<49;j++){
        if (checkLegalMove(i,j,false)) { 
          return false;
        }
      }
    }
  }
  if (temp==3){ //because you can't get stuck if you can jump
    return false;
  }
  return true;
}
bool checkRemoving (int color) { // check if one or more stone(s) is removable (not in a mill)
  for (int i=0;i<49;i++){
    if (stoneArray[i]==color){
      if (!checkMill(i,color)){
        return true;
      }
    }
  }
  return false;
}

void millSetup(){
    p1.score=p1.length=9; //Score is the nb of stone to put down. length is the total number of stones per player
    p2.score=p2.length=9;
    p1.x=58;
    p1.y=8;
    casesCol=7;
    casesRow=7;
    casesHeight=8;
    leftBorder=58;
    upBorder=8;
    for (int i=0; i<49; i++){ //block the invalid places for Mill
      if ((((0==i%7)||(6==i%7))&&((i/7==0)||(i/7==6)))||
         (((1==i%7)||(5==i%7))&&((i/7==1)||(i/7==5)))||
         (((2==i%7)||(4==i%7))&&((i/7==2)||(i/7==4)))||
         (i/7==3)||(i%7==3)  )    {
        stoneArray[i]=EMPTY;
      }
      else {
        stoneArray[i]=4;
      }
    }
    stoneArray[24]=4;  
}

void playMill(){
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
      selected=false;
      selectedI=-1;
    }
    if (arduboy.justPressed(A_BUTTON)){
      int temp=getIndice(p1.x,p1.y);
      if (removing){
        if ((!checkMill(temp,p1Playing? WHITE_STONE : BLACK_STONE))&&(stoneArray[temp]==(p1Playing? WHITE_STONE : BLACK_STONE))){
          removing=false;
          stoneArray[temp]=EMPTY;
          if (p1Playing){
            p2.length--;
            if (p2.length<3){
              arduboy.setCursor(20,30);
              arduboy.print(F("P1 Wins"));
              arduboy.display();
              while("Never gonna give you up");
            }
          }
          else {
            p1.length--;
            if (p1.length<3){
              arduboy.setCursor(20,30);
              arduboy.print(F("P2 Wins"));
              arduboy.display();
              while("Never gonna let you down");
            }
          }      
          p1Playing=!p1Playing;
        }
      }
      else if (p1.score+p2.score>0){
        if (checkLegalMove(0,temp,true)){
          if (p1Playing){
            stoneArray[temp]= BLACK_STONE ;
            p1.score--;
            if (checkMill(temp,BLACK_STONE)){
              if (checkRemoving(WHITE_STONE)){
                removing=true;
              }
              else{
                arduboy.print(F("Can't remove Stone"));
                arduboy.display();
                delay(2000);
                p1Playing=false;
              }
            }
            else {
              p1Playing=false;
            }
          }
          else {
            stoneArray[temp]= WHITE_STONE ;
            p2.score--;
            if (checkMill(temp,WHITE_STONE)){
              if (checkRemoving(BLACK_STONE)){
                removing=true;
              }
              else{
                arduboy.print(F("Can't remove Stone"));
                arduboy.display();
                delay(2000);
                p1Playing=false;
              }
            }
            else {
              p1Playing=true;
            }
          }
        }
      }
      else  {
        if (!selected){
          if (((p1Playing)&&stoneArray[temp]==BLACK_STONE)||((!p1Playing)&&stoneArray[temp]==WHITE_STONE)){
            selectedI=temp;
            selected=true;
          }
        }
        else {
          if (checkLegalMove(selectedI,temp,p1Playing? p1.length==3:p2.length==3)){
            stoneArray[temp]=stoneArray[selectedI];
            stoneArray[selectedI]=EMPTY;
            selectedI=-1;
            selected=false;
            if (checkMill(temp,p1Playing? BLACK_STONE : WHITE_STONE )){
              if (checkRemoving(p1Playing? WHITE_STONE : BLACK_STONE)){
                removing=true;
              }
              else{
                arduboy.print(F("no stone available"));
                arduboy.display();
                delay(2000);                
              }
            }
            if (checkLose(p1Playing? WHITE_STONE : BLACK_STONE)){
              drawMill();
              drawStones();
              arduboy.print("Player");
              arduboy.println(p1Playing? 2:1);
              arduboy.println(F("can't move\n"));
              //arduboy.println("");
              arduboy.print("Player");
              arduboy.println(p1Playing? 1:2);
              arduboy.println("won !");
              arduboy.display();
              while(true); //inite loop: see infinite loop
            }
            if (!removing) {
              p1Playing=!p1Playing;
            }
          }
        }
      }
    }
    drawMill();
    turnUpdate();
    drawStones();
 /*
    if (blinkTimer++>10){
      blinkTimer=0;
      blink=!blink;
    }*/
    drawSelector(getIndice(p1.x,p1.y));    
/*    if (temp>48)
      temp=0;  // whqt was the use again? */  
}

#endif

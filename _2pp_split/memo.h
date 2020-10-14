#ifndef memo_h
#define memo_h

//#include <Arduino.h>

#include "globals.h"
#include "function.h"

#define MEMO_WAIT 3000

//initialy used in Memo (array of 88) but then used in Mill and then in Go and then in Chess... That's why it can now contain 96 char
char symbolArray []={(char)228,(char)228 ,(char)15,(char)15,(char)10,(char)10,(char)14,(char)14,(char)232,(char)168,(char)197,
                      (char)225,(char)225,(char)240,(char)240,(char)175,(char)175,(char)206,(char)206,(char)232,(char)168,(char)197,
                      (char)64,(char)64,(char)35,(char)35,(char)236,(char)236,(char)25,(char)3,(char)3,(char)25,(char)12,
                      (char)247,(char)247,(char)12,/*->medium*/(char)234,(char)18,(char)18,(char)2,(char)2,(char)20,(char)20,(char)234,
                      (char)38,(char)38,(char)5,(char)5,(char)24,(char)24,/*->hard*/(char)36,(char)36,(char)37,(char)37,(char)237,
                      (char)156,(char)156,(char)174,(char)174,(char)4,(char)4,(char)155,(char)155,(char)157,(char)157,(char)237};

void drawCurs(int x, int y, bool print){
  uint8_t temp=0;
  if (difficulty>1){
    temp=1;
  }
  arduboy.drawRect(p1.x,p1.y,casesLength+temp,casesHeight+temp,print? 1:0);
}

void drawCard(int i, uint8_t face){ //2: symbol, 1: back, other: empty
  uint8_t temp=1;
    if (1==difficulty){
    temp=2;
  }
  
  if (1==face){
    arduboy.drawRect(leftBorder+1+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+1,casesLength-temp,casesHeight-temp,0);
    arduboy.drawChar(leftBorder+2+(i%casesCol)*casesLength,i/casesCol*casesHeight+2+upBorder,symbolArray[i],1,0,temp); 
  }
  else if (2==face){
    arduboy.drawChar(leftBorder+2+(i%casesCol)*casesLength,i/casesCol*casesHeight+upBorder+2,(char)178,1,0,temp); 
    arduboy.drawRect(leftBorder+1+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+1,casesLength-temp,casesHeight-temp,1);
  }
  else {
    arduboy.fillRect(leftBorder+2+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+2,casesLength-temp,casesHeight-temp,0);
  }  
}

void shuffle (int size){
  char c=0;
  int r1,r2=0;
  for (int i=0; i<200; i++){
    r1=random(size);
    r2=random(size);
    c=symbolArray[r1];
    symbolArray[r1]=symbolArray[r2];
    symbolArray[r2]=c;
  }
}

void memoSetup(){
    arduboy.clear();
    casesCol=7+difficulty;
    casesRow=2+difficulty;
    
    if (1==difficulty){
      leftBorder-=12;
      upBorder=1;
      casesHeight=20;
      casesLength=14;
    }
    p1.x=leftBorder;
    p1.y=upBorder;    
    int temp=casesCol*casesRow;
    for (int i=temp; i<66; i++){
      symbolArray[i]=0;
    }
    shuffle(temp);
    for (int i=0; i<temp; i++){
      drawCard(i,2);
    }
    turnUpdate();  
}
void playMemo(){
      if (arduboy.justPressed(UP_BUTTON)){
      if (p1.y>upBorder){
        drawCurs(p1.x,p1.y,false);
        p1.y-=casesHeight;
      }
    }
    if (arduboy.justPressed(DOWN_BUTTON)){
      if (p1.y<50){ //?
        drawCurs(p1.x,p1.y,false);
        p1.y+=casesHeight;
      }
    }
    if (arduboy.justPressed(RIGHT_BUTTON)){
      if (p1.x<105){
        drawCurs(p1.x,p1.y,false);
        p1.x+=casesLength;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON)){
      if (p1.x>leftBorder){
        drawCurs(p1.x,p1.y,false);
        p1.x-=casesLength;
      }      
    }
    if (arduboy.justPressed(A_BUTTON)){
      int temp=0;
      if (!selected){
        
        if(selectedI!=getIndice(p1.x,p1.y)){
          selectedI=getIndice(p1.x,p1.y);
          if (symbolArray[selectedI]!=0){
            drawCard(selectedI,1);
            selected=true;
          }
        }
      }
      else { //if (selected){
        temp=getIndice(p1.x,p1.y);
        if ((temp!=selectedI)&&(symbolArray[temp]!=0)){
          drawCard(temp,1);
          arduboy.display();
          delay(MEMO_WAIT);
          if (symbolArray[temp]==symbolArray[selectedI]){ // win a point
            symbolArray[temp]=symbolArray[selectedI]=0;
           drawCard(temp,0);
            drawCard(selectedI,0);
            arduboy.display();
            selected=false;
            if (p1Playing){
              p1.score++;
            }
            else {
              p2.score++;
            }
            if (p1.score+p2.score==casesCol*casesRow/2){
              arduboy.clear();
              arduboy.setCursor(24,30);
              if (p1.score==p2.score){
                arduboy.print(F("   Draw !"));
              }
              else {
                arduboy.print(F("Player "));
                arduboy.print(p1.score>p2.score ? "1":"2");
                arduboy.print(F(" wins"));
              }
              arduboy.display();
              while("why write a symbolArrayInit when you can infite loop and reset"); 
            }
          }
          else {  //2nd card is different
            drawCard(temp,2);
            drawCard(selectedI,2);
            p1Playing=!p1Playing;
            //nselectedI=0;
            selected=false;            
          }
        }
        turnUpdate();
      }
    }
    drawCurs(p1.x,p1.y,blink ? true:false);
    //arduboy.drawRect(p1.x,p1.y,casesLength+1,casesHeight+1,blink ? 1:0);
    if (blinkTimer++>10) { // Blink speed ?
      blink=!blink;
      blinkTimer=0;
    }
}

#endif

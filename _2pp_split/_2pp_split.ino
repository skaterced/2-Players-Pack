
/*  Welcome to my first Arduboy Game.

    About the Games :
    
      Menu:
        left and right to change game, A to select, B for the settings menu where
        You can change global DIFFICULTY. It will affect Trace and Pong speed, and MEMO ammount of cards (from 3X8 to 6x11)
        
      CONTROLS : As it was developped (and will surely be played often) with the Emulator, the controls are optimized for Emulator OR Arduboy
                You can change defaut Controls settings by commenting or decommenting some lines -> look for "bool forEmulator"
          Emulator (PC) :
            Pong, Trace and ReflX are played with A and B for player 1 and UP and DOWN for player 2
          Arduboy :
            Pong, Trace and ReflX are played with UP and DOWN for player 1 and A and B for player 2
            
          MEMO : Arrows for moving the cursor, A to select a card
          MILL : Arrows for moving the cursor, A to select a Stone, B to cancel selection
          GO   : Arrows for moving the cursor, A to add/remove a Black Stone, B to add/remove a White Stone 

      RULES:
        
        Pong:   Do I Really have to explain ?
        Trace:  Survive longer than your opponent
        ReflX:  Before each round there is a new rule (normal or inverted) for the 2 kind of arrows (White on Black BackGround or Black on White Bg)
                after both players are ready and have pressed "down" (cf CONTROLS) they wait a random time and then the arrow appears.
                +1 point if you press the correct direction depending on the rule, and -1 if you press the wrong one.
                Both players can press at the same time and get the point (or lose it).
        MEMO:   select a card and flip it with button A. Flip a second card and if they math you get the point. When there is no more card,
                the player with more pointsw wins. Note: the cards are bigger if you select the minimal difficulty (3x8)
        MILL:   Th first 9 Stones can be placed anywhere. After that you must select a stone with A and place it in a free adjacent space.
                Align 3 stones on the same line to form a "mill". If you do so you can remove an oppenent stone, except if it's part of a mill.
                If you only have 3 stones left, you can move not only by following the lines but where you want.
                You win if your opponent has only 2 stones left OR if he is "stuck" with nowhere to move any of his stones.
                Look up for "Nine Men's Morris" for more information
    GO/CHESS:   There are no rules check. Look up Wikipedia to lurn the rules
          
          
      Hope you'll enjoy !


    Special thanks to my brother Jean-Philippe who taught me how to code and wrote the "original" Trace inspired by the movie TRON
    and thanks to Pharap who spends a lot of time helping coding people
   
*/

#include "pong.h"
#include "trace.h"
#include "reflx.h"
#include "memo.h"
#include "mill.h"
#include "chess.h"
#include "go.h"

#include "globals.h"
#include "function.h" 

#define NBGAMES 7
 
const unsigned char PROGMEM picture[] =
{
// width, height,
//128, 48,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x0f, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x83, 0xe3, 0xe3, 0x63, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x83, 0xf3, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x3f, 0x3f, 0x3f, 0xbf, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf1, 0xf1, 0xf0, 0xf0, 0xf0, 0xf8, 0xfc, 0x3c, 0x1f, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x1e, 0x0f, 0x0f, 0x05, 0x04, 0x44, 0x46, 0x46, 0x02, 0x02, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x81, 0xc0, 0xe0, 0xf0, 0xfc, 0x0e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x24, 0x24, 0x26, 0x26, 0x20, 0xa0, 0xe0, 0xe0, 0x70, 0x1f, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfc, 0x3c, 0x3e, 0x3f, 0x30, 0x20, 0x00, 0x00, 0x00, 0x04, 0x04, 0x9c, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x3f, 0x7e, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x06, 0x07, 0x0f, 0x0f, 0x07, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0x3e, 0x3e, 0x3c, 0x3c, 0xbc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1e, 0x1e, 0x0e, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0x7f, 0x4f, 0x47, 0x67, 0x63, 0x23, 0x23, 0x03, 0x03, 0x03, 0x03, 0x07, 0xc7, 0xff, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x83, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xff, 0x3f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x10, 0x18, 0x0f, 0x07, 0x03, 0xc3, 0xc3, 0xe3, 0xf3, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc1, 0xc0, 0xc0, 0xc0, 0xc4, 0xc4, 0xc4, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0xff, 0xff, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xc7, 0xc7, 0xe3, 0xf3, 0xff, 0xc7, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0xf0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xeb, 0xe3, 0xff, 0xb3, 0xaf, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x9d, 0xbe, 0xbe, 0xbe, 0xc7, 0xab, 0xab, 0xa5, 0xbd, 0xcf, 0xb7, 0x97, 0xc1, 0xbf, 0x83, 0xf7, 0xfb, 0xff, 0x85, 0xff, 0xcf, 0xb7, 0xb7, 0xff, 0xff, 0xff, 0x80, 0xf9, 0xf3, 0xf9, 0x80, 0xff, 0xdf, 0xab, 0xab, 0xc7, 0xbf, 0x83, 0xf7, 0xfb, 0xff, 0xfb, 0xc1, 0xbb, 0xff, 0x85, 0xff, 0x83, 0xf7, 0xfb, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 
};
//char c=0;

void setup() { // SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS  Setup SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  arduboy.clear();
  if (0==game){
    arduboy.begin();
    arduboy.setFrameRate(60);
  }

  #ifdef pong_h
    else if (PONG==game){
      arduboy.setFrameRate(30+difficulty*5);
      p1.x=4;
      p1.y=20;
      p2.x=122;
      p2.y=20;
    }
  #endif
  
  #ifdef trace_h
    else if (TRACE==game){
      arduboy.setFrameRate(TRACE_FPS+difficulty*5);
      newTraceGame();
    }
  #endif
  
  #ifdef reflx_h
    else if (REFLX==game){
      newReflXGame();
    }
  #endif

  #ifdef memo_h
    else if (MEMO==game){
      memoSetup();
    }
  #endif
  
  #ifdef mill_h
    else if (MILL==game){
      millSetup();
    }
  #endif

  #ifdef go_h
    else if (GO==game){
      goSetup();
    }
  #endif

  #ifdef chess_h
    else if (CHESS==game){
      chessSetup();
    }
  #endif
}
 
void loop() { // -------------------------  Init loop -------------------------------------------------------------------------
  //testP++; //for .h testing (doesn't work )
  //timer++;
  //arduboy.pollButtons();  
 
  if (!(arduboy.nextFrame()))
    return;
    
  arduboy.pollButtons();    
    
  if ((MENU==game)||(MENU2==game)||(PONG==game)||(MILL==game)||(GO==game)){
    arduboy.clear(); //in other words: IF NOT MEMO or pong
  }
  if (MENU==game){  
    timer++;
    arduboy.drawBitmap(0,0,picture,128,48,WHITE);
    //arduboy.drawChar(2,50,17,1,0,1);
    arduboy.setCursor(10,49);
    switch(p1.x){
      case (PONG):
        arduboy.print("      Pong  ->");
      break;
      case (TRACE):
        arduboy.print("  <-  Trace ->");
      break;
      case (REFLX):
        arduboy.print("  <-  ReflX ->");
      break;
      case (MEMO):
        arduboy.print("  <-  Memo  ->");
      break;
      case (MILL):
        arduboy.print("  <-  Mill  ->");
      break;
      case (GO):
        arduboy.print("  <-   Go   ->");
      break;   
      case (CHESS):
        arduboy.print("  <-  Chess");
      break;      
    }
    //arduboy.print(TRACE_FPS);
    
    //arduboy.drawChar(120,50,16,1,0,1);
    arduboy.setCursor(1,57);
    arduboy.print("A: Select    B: Param");
  
    if (arduboy.justPressed(RIGHT_BUTTON))
    {
      if (p1.x<NBGAMES+1){
        p1.x++;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON))
    {
      if (p1.x>2){
        p1.x--;
      }
    }
    if (arduboy.justPressed(B_BUTTON))
    {
      game=MENU2;
      arduboy.clear();
    }    
    if (arduboy.justPressed(A_BUTTON))
    {
      arduboy.initRandomSeed();
      randomSeed(timer*37);
      game=p1.x;
      setup();
    }  
  }
  else if (MENU2==game){  
    timer++;
    arduboy.setCursor(10,10);
    arduboy.print("Difficulty : ");
    arduboy.print(difficulty);
    arduboy.setCursor(10,20);
    arduboy.print("Controls : " );
    arduboy.print(forEmulator ? "PC":"Arduboy");
    arduboy.setCursor(0,55);
    arduboy.print("WW.Github.com/skaterced");
    arduboy.setCursor(1,40);
    arduboy.print("A: Change    B: Back");
    
    arduboy.drawChar(0,p1.y*10+10,16,1,0,1);
 
  
    if (arduboy.justPressed(DOWN_BUTTON))
    {
      if (p1.y<1){
        p1.y++;
      }
    }
    if (arduboy.justPressed(UP_BUTTON))
    {
      if (p1.y>0){
        p1.y--;
      }
    }
    if (arduboy.justPressed(A_BUTTON))
    {
      switch (p1.y){
        case 0:
        
          if (++difficulty==5)
            difficulty=1;
        break;
        case 1:
          forEmulator = !forEmulator;
          if (forEmulator) {
            P2_RIGHT=UP_BUTTON;
            P1_LEFT=A_BUTTON;
            P1_RIGHT=B_BUTTON;
            P2_LEFT=DOWN_BUTTON;
          }
          else {
            P1_LEFT=UP_BUTTON;
            P1_RIGHT=DOWN_BUTTON;
            P2_RIGHT=B_BUTTON;
            P2_LEFT=A_BUTTON;
          }
        break;
      }
      
    }
    if (arduboy.justPressed(B_BUTTON))
    {
      game=MENU;
      arduboy.clear();
    }     
  }

  #ifdef trace_h  
    else if (PONG==game){     //  ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||    Pong   |||||||||||||||||||||||||||||||||||||||||
      playPong();
    }
  #endif
  #ifdef trace_h
    else if (game==TRACE) // ---------------------------------------------------------------- Trace  -----------------------------
    {
      playTrace();
    }
  #endif

  #ifdef reflx_h
    else if (REFLX==game){ // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ReflX xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
      playReflx();
    }
  #endif
  
  #ifdef memo_h
  else if (MEMO==game){  // ############################################  MEMO #################################
    playMemo();
  }
  #endif
  
  #ifdef mill_h
  else if (MILL==game){  // -----------------++--+--++-+-------+-----+-+----++ MILL ++--+-++--++--++--+---++-++
    playMill();
  }
  #endif
  
  #ifdef go_h
    else if (GO==game){  // -----------------++--+--++-+-------+-----+-+----++ GO ++--+-++--++--++--+---++-++
      arduboy.clear();
      playGo();
    }
  #endif
  #ifdef chess_h
    else if (CHESS==game){  // ######################################################### Chess ###############################
      arduboy.clear();
      playChess();
    }
  #endif
  else {
    arduboy.setCursor(0,0);
    arduboy.println("please recompile with");
    arduboy.println("this game included");
    arduboy.println("(#include xxx_h)");
  }
  arduboy.display();
}

#ifndef globals_h
#define globals_h

#include <Arduboy2.h>
//#include <stdlib.h>

Arduboy2 arduboy;

#define MENU 0
#define MENU2 1
#define PONG 2
#define TRACE 3
#define REFLX 4
#define MEMO 5
#define MILL 6
#define GO 7
#define CHESS 8

#define BLACK_STONE 1 // (P1)
#define WHITE_STONE 2 // (P2)

uint8_t scoreTimer=0;
int timer=0;
uint8_t difficulty=2;  //must be between 1-4
uint8_t game=MENU;
//int temp=0;
bool p1Playing=true; //false: p2's turn
bool selected=false; //MILL and MEMO - when a player has selected something - ReflX True: bold arrow
int8_t selectedI=-1;
bool removing=false;
bool blink=true;
uint8_t blinkTimer=0;
bool arrowInverted=false;
bool boldArrowInverted=false;
bool pointDown=false;
uint8_t casesLength=8;
uint8_t casesHeight=11;
uint8_t casesCol=7+difficulty;
uint8_t casesRow=2+difficulty;
uint8_t leftBorder=30;
uint8_t upBorder=-1;

//initialy used in Memo (array of 88) but then used in Mill and then in Go and then in Chess... That's why it can now contain 96 char
char symbolArray [88]={(char)228,(char)228 ,(char)15,(char)15,(char)10,(char)10,(char)14,(char)14,(char)232,(char)168,(char)197,
                      (char)225,(char)225,(char)240,(char)240,(char)175,(char)175,(char)206,(char)206,(char)232,(char)168,(char)197,
                      (char)64,(char)64,(char)35,(char)35,(char)236,(char)236,(char)25,(char)3,(char)3,(char)25,(char)12,
                      (char)247,(char)247,(char)12,/*->medium*/(char)234,(char)18,(char)18,(char)2,(char)2,(char)20,(char)20,(char)234,
                      (char)38,(char)38,(char)5,(char)5,(char)24,(char)24,/*->hard*/(char)36,(char)36,(char)37,(char)37,(char)237,
                      (char)156,(char)156,(char)174,(char)174,(char)4,(char)4,(char)155,(char)155,(char)157,(char)157,(char)237};

uint8_t stoneArray [96];


class Player {
  public :
    int x,y;
    int length;
    uint8_t dir;
    int score;
    Player(int X, int Y);
};
Player::Player(int X, int Y)
{
  this->x=X;
  this->y=Y;
  this->length=14;  //becomes "Number of Stones left" in MILL
  this->dir=0;
  this->score=0;
}

class Player p1(4,0);
class Player p2(122,20);

#endif

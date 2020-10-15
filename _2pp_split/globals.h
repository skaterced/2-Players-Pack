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

  //Controls designed for Arduboy
bool forEmulator = false;  // ToDo : remove this and change Menu. No more need for this bool
uint8_t P1_LEFT=UP_BUTTON;
uint8_t  P1_RIGHT=DOWN_BUTTON;
uint8_t  P2_RIGHT=B_BUTTON;
uint8_t  P2_LEFT=A_BUTTON;

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
uint8_t casesLength=8;
uint8_t casesHeight=11;
uint8_t casesCol=7+difficulty;
uint8_t casesRow=2+difficulty;
int leftBorder=30;
int upBorder=-1;

uint8_t stoneArray [81];


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

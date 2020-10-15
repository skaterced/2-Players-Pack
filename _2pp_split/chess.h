#ifndef chess_h
#define chess_h

#include "globals.h"
#include "function.h"

#define NBCHESSPIECES 32
#define CHESS_PION 0  // noir +2, pas sa couleur +1
#define CHESS_CHEVAL 4
#define CHESS_FOU 8
#define CHESS_TOUR 12
#define CHESS_DAME 16
#define CHESS_ROI 20



const unsigned char chessPieces[] PROGMEM = {
// width, height,
8, 8,
//pionB_N
0x00,0x00,0x20,0x38,0x38,0x20,0x00,0x00,
//pionB_B
0xff,0xdf,0xa7,0xbb,0xbb,0xa7,0xdf,0xff,
//pionN_B
0xff,0xff,0xdf,0xc7,0xc7,0xdf,0xff,0xff,
//pionN_N
0x00,0x20,0x58,0x44,0x44,0x58,0x20,0x00,
//chevalB_N
0x00,0x40,0x78,0x7c,0x6c,0x48,0x00,0x00,
//chevalB_B
0xbf,0x47,0x7b,0x7d,0x6d,0x4b,0xb7,0xff,
//chevalN_B
0xff,0xbf,0x87,0x83,0x93,0xb7,0xff,0xff,
//chevalN_N
0x40,0xb8,0x84,0x82,0x92,0xb4,0x48,0x00,
//fou
0x00,0x00,0x40,0x7c,0x7e,0x46,0x00,0x00,
0xff,0xbf,0x43,0x7d,0x7e,0x46,0xb9,0xff,
0xff,0xff,0xbf,0x83,0x81,0xb9,0xff,0xff,
0x00,0x40,0xbc,0x82,0x81,0xb9,0x46,0x00,
//tour
0x00,0x06,0x7c,0x7e,0x7e,0x7c,0x06,0x00,
0xf9,0x86,0x7d,0x7e,0x7e,0x7d,0x86,0xf9,
0xff,0xf9,0x83,0x81,0x81,0x83,0xf9,0xff,
0x06,0x79,0x82,0x81,0x81,0x82,0x79,0x06,
//dame
0x08,0x12,0x34,0x38,0x38,0x34,0x12,0x08,
0xe9,0xd2,0xb5,0xbb,0xbb,0xb5,0xd2,0xe9,
0xef,0xdb,0x97,0x8f,0x8f,0x97,0xdb,0xef,
0x2c,0x5a,0x94,0x88,0x88,0x94,0x5a,0x2c,
//roi
0x00,0x00,0xf8,0xf2,0xff,0xf2,0xf8,0x00,
0xff,0x03,0xfd,0xfa,0xff,0xfa,0xfd,0x03,
0xff,0xff,0x07,0x0d,0x00,0x0d,0x07,0xff,
0x00,0xfc,0x02,0x05,0x00,0x05,0x02,0xfc
};

class ChessPiece {
  public:
    uint8_t i;
    uint8_t type;
    bool black;
    //bool selected;
    ChessPiece(int i_, uint8_t type_, bool black_){
      i=i_;
      type=type_;
      black=black_;
      //selected=false;
    }
    void draw(void){
      int x= leftBorder-4+(i%casesCol)*casesLength;
      int y= i/casesCol*casesHeight+1;//+upBorder+2;
      int temp=0;
      bool caseIsBlack=true;
      if ((i%casesCol>1)&&(i%casesCol<10)&&(0==(i%casesCol+i/casesCol)%2))
        caseIsBlack=false;
      if ((selectedI!=i)||(blink)){
        if (black){
          temp+=2;
          if (caseIsBlack){
            temp++;
          }
        }
        else {
          if (!caseIsBlack){
            temp++;
          }
        }
        Sprites::drawOverwrite(x,y,chessPieces, type+temp);
      }
    }
};

class ChessPiece pieces[NBCHESSPIECES]={ChessPiece(17,CHESS_PION,false),ChessPiece(14,CHESS_PION,false),ChessPiece(15,CHESS_PION,false),ChessPiece(16,CHESS_PION,false),
                                        ChessPiece(18,CHESS_PION,false),ChessPiece(19,CHESS_PION,false),ChessPiece(20,CHESS_PION,false),ChessPiece(21,CHESS_PION,false),                                        
                                        ChessPiece(2,CHESS_TOUR,false),ChessPiece(3,CHESS_CHEVAL,false),ChessPiece(4,CHESS_FOU,false),ChessPiece(5,CHESS_ROI,false),
                                        ChessPiece(9,CHESS_TOUR,false),ChessPiece(8,CHESS_CHEVAL,false),ChessPiece(7,CHESS_FOU,false),ChessPiece(6,CHESS_DAME,false),
                                        ChessPiece(77,CHESS_PION,true),ChessPiece(74,CHESS_PION,true),ChessPiece(75,CHESS_PION,true),ChessPiece(76,CHESS_PION,true),
                                        ChessPiece(78,CHESS_PION,true),ChessPiece(79,CHESS_PION,true),ChessPiece(80,CHESS_PION,true),ChessPiece(81,CHESS_PION,true),
                                        ChessPiece(86,CHESS_TOUR,true),ChessPiece(87,CHESS_CHEVAL,true),ChessPiece(88,CHESS_FOU,true),ChessPiece(89,CHESS_ROI,true),
                                        ChessPiece(93,CHESS_TOUR,true),ChessPiece(92,CHESS_CHEVAL,true),ChessPiece(91,CHESS_FOU,true),ChessPiece(90,CHESS_DAME,true)};

int isOccupied(uint8_t ind){ //return the indice (in the pieces array) of the piece that stays on the given chessBoard indice
  for (int i=0; i<NBCHESSPIECES; i++){
    if (pieces[i].i==ind)
      return i;
  }
  return -1;
}

void eat(uint8_t v){ // V for Victim indice in the pieces array
  int temp=0;
  if (pieces[v].black){ // bring out your deads... whites on the left, blacks on the right
    temp=11;
  }
  for (int j=0; j<16; j++){
    if (isOccupied(temp)!=-1){
      temp+=casesCol;
      if (96==temp){
        temp=1;
      }
      else if (107==temp){
        temp=10;
      }
    }
    else {
      pieces[v].i=temp;
      break;
    }
  }
}

void drawChessBoard(void){
  arduboy.drawRect(33,0,66,64,1);
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      arduboy.fillRect(34+16*i,1+16*j,8,8,1);
      arduboy.fillRect(42+16*i,9+16*j,8,8,1);
    }
  }
}

void chessSetup(){
    p1.x=74;
    p1.y=12;
    casesCol=12;
    casesRow=8;
    casesHeight=8;
    casesLength=8;
    leftBorder=22;
    upBorder=4;  
}

void playChess(){
  /*
  if (arduboy.justPressed(UP_BUTTON)){
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
    if (p1.x<106){
      p1.x+=8;
    }
  }
  if (arduboy.justPressed(LEFT_BUTTON)){
    if (p1.x>18){
      p1.x-=8;
    }
  }*/
  SelectorManagment();
  if (arduboy.justPressed(B_BUTTON)){
    selectedI=-1;
    selected=false;
  }
  if (arduboy.justPressed(A_BUTTON)){
    int selectorI=getIndice(p1.x,p1.y);
    if (!selected){
      for (int i=0; i<NBCHESSPIECES; i++){
        if (pieces[i].i==selectorI){
          selected=true;
          selectedI=selectorI;
          break;  
        }
      }
    }
    else{ // Piece is put down
      if (selectorI!=selectedI){
        int victim=isOccupied(selectorI);
        if (victim!=-1){
          eat(victim);
        }
        pieces[isOccupied(selectedI)].i=selectorI;
        selected=false;
        selectedI=-1;
      }
    }
  }
  //p1.score=p1.x;
  //p2.score=p1.y;
  
  drawChessBoard();    
  for (int i=0; i<NBCHESSPIECES; i++){
    pieces[i].draw();
  }
  
  if (blinkTimer++>10){
    blinkTimer=0;
    blink=!blink;
  }
  drawSelector(getIndice(p1.x,p1.y));
  arduboy.drawLine(33,0,33,64,1);   
}

#endif

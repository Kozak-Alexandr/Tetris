
#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct boardCell
{
    int x;
    int y;
    int colour;
    int onoff;
};

struct boardCell theBoard[20][40];
int gameMode = 1;                                    
int gameInProgress = 0;
int anchorX, anchorY = 1;
int mouseX, mouseY = 1;
int stretchX, stretchY = 1;
int pausedMode = 1;
int currScore = 0;
int pieceColour;
char pieceColourStr[10];
int blue, green, red, yellow, darkgrey, white, black, orange, purple, rainbow, decidePiece;
int border1;
int border2;
int totNumOther;
int totNumOther;
int totNum1, totNum2, totNum3, totNum4;
int paused = 0;
float angle;
int moveX, moveY;
int needNewPiece = 1;

#define STARTX 7
#define STARTY 33
#define xOffSet -1

GLfloat LightAmbient[] = { 0.4, 0.4, 0.4, 1.0};
GLfloat LightDiffuse[] = { 0.7, 0.7, 0.7, 1.0};
GLfloat LightPosition[] = { 0.0, 0.0, 2.0, 1.0};

void resetPit();

void glPrint (GLfloat xp, GLfloat yp, void *font, char *format, ...);

void drawBoard ();

void moveDown (int fillLineNo);

void fillBoard ();

void printRunningScores ();

void drawText ();

void drawNextBlock3D ();

void drawStartStuff ();

void renderStartScreen ();

void renderGameScreen ();

void renderHighScores ();

void render (void);

struct piece
{
    int x;
    int y;
    int onoff;
    int colour;
};

struct piece currActivePiece[16];
struct piece currDecidePiece[16];
struct piece currTempPiece[16];
struct piece nextActivePiece[16];

int shape_L[] =
{ 0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

int shape_S[] =
{ 0, 1, 1, 0,
  1, 1, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 0,
  0, 0, 1, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  1, 1, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 0,
  0, 0, 1, 0,
  0, 0, 0, 0
};

int shape_Z[] =
{ 1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0
};

int shape_O[] =
{ 0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};

int shape_T[] =
{ 0, 0, 1, 0,
  0, 1, 1, 0,
  0, 0, 1, 0,
  0, 0, 0, 0,
  0, 0, 1, 0,
  0, 1, 1, 1,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 1, 0,
  0, 0, 1, 1,
  0, 0, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 1,
  0, 0, 1, 0,
  0, 0, 0, 0
};

int shape_EL[] =
{ 0, 0, 0, 1,
  0, 1, 1, 1,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 1,
  0, 0, 0, 0,
  0, 1, 1, 1,
  0, 1, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 0, 0
};

int shape_LE[] =
{ 0, 1, 1, 1,
  0, 0, 0, 1,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 1,
  0, 0, 0, 1,
  0, 0, 1, 1,
  0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 1,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 1, 1,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 0, 0
};

void drawActivePiece (int xCnt, int yCnt, int makeActive);

int getRotNumbers (int rotPiece);

void loadPiece (int shape[], int pieceRot, int makeActive, int theColour);

void loadNewPiece (int pieceNo, int pieceRot, int makeActive);

void loadDecidePiece (int shape[], int dAng, int xx, int yy);

void loadDecide (int xx, int yy, int dNum, int dAng);

void initNewPiece ();

void drawDroppedPieces ();

int isGameMode = 0;
int isTrailsMode = 1;
int OKnewPiece = 1;
int startCnt;
int ticks = 0, fps;
float z_zoom = -10;
float gRotate = -10;
int newPieceNo, currPieceNo;
int pieceAngle = 0;
int isBlendMode = 1;
int isLineMode = 0;
int isFogMode = 0;
int arbColourR, arbColourG, arbColourB;
int totNumRowsDone;
int noL = 0, noS = 0, noZ = 0, noO = 0, noT = 0, noEL = 0, noLE = 0;
int vIdleCnt, vRenderCnt;
int weightBoard = 10;
int settCnt = 0;

int getLowest (int xVal, int decideNum, int decideAngle);

void checkFullRow ();

void rotatePiece ();

void movePieceX (int mag);

void movePieceY (int mag);

void mouse (int button, int state, int x, int y);

void motion (int x, int y);

void passive (int x, int y);

void idle (void);

void visible (int vis);

void key (unsigned char key, int px, int py);

void keyup (unsigned char key, int x, int y);

void special (int key, int x, int y);

void specialup (int key, int x, int y);

void moveColours ();

void timerFunc (int value);

void initDisplayLists ();

void renderSettingScreen ();

#endif

#include "game.h"

void resetPit ()
{
    for (int i = 4; i < 14; i++)
    {
        for (int j = 4; j < 35; j++)
        {
            theBoard[i][j].colour = 0;
            theBoard[i][j].onoff = 0;
        }
    }
}

void glPrint (GLfloat xp, GLfloat yp, void *font, char *format, ...)
{
    va_list args;
    char buffer[200], *p;
    va_start (args, format);
    vsprintf (buffer, format, args);
    va_end (args);
    glPushMatrix ();
    glRasterPos2f (xp, yp);
    for (p = buffer; *p; p++)
    {
        glutBitmapCharacter (font, *p);
    }
    glPopMatrix ();
}

void drawBoard ()
{
    int i, j;
    int printit = 0;
    glPushMatrix ();
    glLineWidth (0.01);
    glColor4f (1.0, 1.0, 1.0, 1.0);
    glBegin (GL_LINE_STRIP);
    glVertex2f (3.9, 34);
    glVertex2f (3.9, 4);
    glEnd ();
    glBegin (GL_LINE_STRIP);
    glVertex2f (14.1, 4);
    glVertex2f (14.1, 34);
    glEnd ();
    glBegin (GL_LINE_STRIP);
    glVertex2f (4, 3.9);
    glVertex2f (14, 3.9);
    glEnd ();
    glTranslatef (7, 35, 0);
    for (int i = 0; i < 5; i++)
    {
        glColor4f (1.0, 1.0, 1.0, 0.2);
        glBegin (GL_LINE_STRIP);
        glVertex2f (i, 0);
        glVertex2f (i, 4);
        glEnd ();
        glBegin (GL_LINE_STRIP);
        glVertex2f (4, i);
        glVertex2f (0, i);
        glEnd ();
    }
    glPopMatrix ();
}

void moveDown (int fillLineNo)
{
    theBoard[4][fillLineNo].onoff = 0;
    theBoard[4][fillLineNo].colour = 0;
    theBoard[5][fillLineNo].onoff = 0;
    theBoard[5][fillLineNo].colour = 0;
    theBoard[6][fillLineNo].onoff = 0;
    theBoard[6][fillLineNo].colour = 0;
    theBoard[7][fillLineNo].onoff = 0;
    theBoard[7][fillLineNo].colour = 0;
    theBoard[8][fillLineNo].onoff = 0;
    theBoard[8][fillLineNo].colour = 0;
    theBoard[9][fillLineNo].onoff = 0;
    theBoard[9][fillLineNo].colour = 0;
    theBoard[10][fillLineNo].onoff = 0;
    theBoard[10][fillLineNo].colour = 0;
    theBoard[11][fillLineNo].onoff = 0;
    theBoard[11][fillLineNo].colour = 0;
    theBoard[12][fillLineNo].onoff = 0;
    theBoard[12][fillLineNo].colour = 0;
    theBoard[13][fillLineNo].onoff = 0;
    theBoard[13][fillLineNo].colour = 0;
    for (int i = 4; i < 14; i++)
    {
        for (int j = 4; j < 35; j++)
        {
            if (j > fillLineNo)
            {
                if (theBoard[i][j].onoff == 1)
                {
                    theBoard[i][j - 1].colour = theBoard[i][j].colour;
                    theBoard[i][j - 1].onoff = theBoard[i][j].onoff;
                    theBoard[i][j].colour = theBoard[i][j + 1].colour;
                    theBoard[i][j].onoff = theBoard[i][j + 1].onoff;
                }
            }
        }
    }
}

void fillBoard ()
{
    int j = 0;
    for (int i = 0; i < 16; i++)
    {
        if (currActivePiece[i].onoff == 1)
        {
            theBoard[currActivePiece[i].x][currActivePiece[i].y].colour =
            currActivePiece[i].colour;
            theBoard[currActivePiece[i].x][currActivePiece[i].y].onoff = 1;
        }
    }
    for (int j = 0; j < 16; j++)
    {
        currActivePiece[j].onoff = 0;
        currActivePiece[j].colour = 0;
    }
}

void printRunningScores ()
{
    glColor4f (1.0, 0.0, 0.0, 1.0);
    glPrint (200, 800, GLUT_BITMAP_HELVETICA_18, "%i", currScore);
}

void drawText ()
{
    glPushMatrix ();
    glDisable (GL_LIGHTING);
    glOrtho (0, 400, 0, 400, 0, 400);
    glMatrixMode (GL_MODELVIEW);
    glColor4f (0.5, 0.5, 0.5, 1.05);
    switch (gameMode)
    {
        case 1:
        {
            glColor4f (0.5, 0.5, 0.5, 1.05);
            glPrint (1000, 1000, GLUT_BITMAP_HELVETICA_12, "X: %i  Y: %i",
            mouseX, mouseY);
            glPrint (1000, 800, GLUT_BITMAP_HELVETICA_12, "%i",
            glutGet (GLUT_ELAPSED_TIME));
            glPrint (1000, 600, GLUT_BITMAP_HELVETICA_12, "start#: %i",
            startCnt);
            if (startCnt == 0)
            glColor3f (1.0, 1.0, 0.0);
            else
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glPrint (3700, 5400, GLUT_BITMAP_HELVETICA_18, "New Game");
            if (startCnt == -1)
            glColor3f (1.0, 1.0, 0.0);
            else
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glPrint (3700, 5800, GLUT_BITMAP_HELVETICA_18, "Settings");
            if (startCnt == 1)
            glColor3f (1.0, 1.0, 0.0);
            else
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glPrint (3700, 5000, GLUT_BITMAP_HELVETICA_18, "Close");
            if (gameInProgress == 1)
            {
                if (startCnt == 2)
                glColor3f (1.0, 1.0, 0.0);
                else
                glColor4f (0.0, 0.0, 1.0, 1.0);
                glPrint (3700, 4600, GLUT_BITMAP_HELVETICA_18, "Continue");
            }
            break;
        }
        case 2:
        {
            glDisable (GL_LIGHTING);
            glPrint (7000, 200, GLUT_BITMAP_HELVETICA_12, "FPS :%i", fps);
            glPrint (7000, 800, GLUT_BITMAP_HELVETICA_12,
            "pieceNo :%i  pieceAngle :%i", currPieceNo, pieceAngle);
            glPrint (3200, 1000, GLUT_BITMAP_HELVETICA_12, "Level: %i", 1);
            glPrint (3200, 1200, GLUT_BITMAP_HELVETICA_12, "Position: %i", 20);
            glPrint (3200, 1400, GLUT_BITMAP_HELVETICA_12, "Speed: %i", 1);
            glPrint (3200, 1600, GLUT_BITMAP_HELVETICA_12, "Rows: %i",
            totNumRowsDone);
            glPrint (3200, 1800, GLUT_BITMAP_HELVETICA_12, "Score: %i",
            18000000);
            glPrint (3200, 2000, GLUT_BITMAP_HELVETICA_12, "1's: %i", totNum1);
            glPrint (3200, 2200, GLUT_BITMAP_HELVETICA_12, "2's: %i", totNum2);
            glPrint (3200, 2400, GLUT_BITMAP_HELVETICA_12, "3's: %i", totNum3);
            glPrint (3200, 2600, GLUT_BITMAP_HELVETICA_12, "4's: %i", totNum4);
            glPrint (3200, 2800, GLUT_BITMAP_HELVETICA_12,
            "Not supposed to happen: %i", totNumOther);
            glPrint (3200, 3000, GLUT_BITMAP_HELVETICA_12, "start#: %i",
            startCnt);
            printRunningScores ();
            if (pausedMode == 1)
            {
                glColor4f (1.0, 1.0, 1.0, 1.0);
                glPrint (1800, 6000, GLUT_BITMAP_TIMES_ROMAN_24, "PAUSED");
            }
            break;
        case 4:
        {
        	if (settCnt == 0)
            glColor3f (1.0, 1.0, 0.0);
            else
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glPrint (3700, 5400, GLUT_BITMAP_HELVETICA_18, "UP");
            if (settCnt == 1)
            glColor3f (1.0, 1.0, 0.0);
            else
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glPrint (3700, 5000, GLUT_BITMAP_HELVETICA_18, "DOWN");
            glColor3f (0.0, 0.0, 1.0);
            glPrint (3700, 4600, GLUT_BITMAP_HELVETICA_18, "Weight: %i", weightBoard);
            break;	
        }
        }
    }
    glEnable (GL_LIGHTING);
    glPopMatrix ();
}

void drawNextBlock3D ()
{
    drawActivePiece (7, 38, 2);
    glLoadIdentity ();
    glPushMatrix ();
    glTranslatef (15, 34, -10);
    glRotatef (angle, 1.0, 1.0, 1.0);
    glColor4f (0.5, 0.5, 0.5, 0.9);
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            glBegin (GL_LINE_STRIP);
            glVertex3f (i, 0, j);
            glVertex3f (i, 4, j);
            glEnd ();
            glBegin (GL_LINE_STRIP);
            glVertex3f (4, i, j);
            glVertex3f (0, i, j);
            glEnd ();
            glBegin (GL_LINE_STRIP);
            glVertex3f (j, i, 4);
            glVertex3f (j, i, 0);
            glEnd ();
        }
    }
    glPopMatrix ();
}

void drawStartStuff ()
{
    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth (0.01);
    glLoadIdentity ();
    glViewport (0, 0, 1024, 768);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0, 1024, 0, 768);
    glScalef (2, 2, 2);
    glTranslatef (0, -768, 0);

    glBegin (GL_LINE_LOOP);
        glVertex2f (anchorX, anchorY);
        glVertex2f (anchorX, stretchY);
        glVertex2f (stretchX, stretchY);
        glVertex2f (stretchX, anchorY);
    glEnd ();

    glutWireCube (5.0);
    glMatrixMode (GL_PROJECTION);
    gluPerspective (180,                      
                    1024 / 768,              
                    1.0,                     
                    -900.0                  
    ); 

    glLoadIdentity ();
    glOrtho (0, 40, 0, 40, 0, 40);
    glMatrixMode (GL_MODELVIEW);
    gluLookAt (0.0, 0.0, 600.0,              
               0.0, 0.0, 0.0,                
               0.0, 1.0, 0.                  
    ); 
    glLoadIdentity ();


    
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    
    
    loadNewPiece (0, 0, 2); glColor4f (1.0, 1.0, 1.0, 0.01); drawActivePiece (3, 38, 3);
    loadNewPiece (1, 0, 2); glColor4f (1.0, 1.0, 0.0, 0.01); drawActivePiece (7, 38, 3);
    loadNewPiece (2, 0, 2); glColor4f (0.0, 1.0, 0.0, 0.01); drawActivePiece (11, 38, 3);
    loadNewPiece (3, 0, 2); glColor4f (0.0, 0.0, 1.0, 0.01); drawActivePiece (15, 38, 3);
    loadNewPiece (4, 0, 2); glColor4f (0.7, 0.0, 1.0, 0.01); drawActivePiece (19, 38, 3);
    loadNewPiece (5, 0, 2); glColor4f (1.0, 0.9, 0.0, 0.01); drawActivePiece (23, 38, 3);
    loadNewPiece (6, 0, 2); glColor4f (1.0, 1.0, 1.0, 0.01); drawActivePiece (27, 38, 3);
    loadNewPiece (0, 0, 2); glColor4f (0.0, 1.0, 0.0, 0.01); drawActivePiece (31, 38, 3);
    loadNewPiece (1, 0, 2); glColor4f (1.0, 0.0, 0.0, 0.01); drawActivePiece (35, 38, 3);

    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    glColor4f (1.0, 1.0, 1.0, 1.5); loadNewPiece (0, 0, 2); drawActivePiece (3, 38, 3);
    glColor4f (1.0, 1.0, 0.0, 1.5); loadNewPiece (1, 0, 2); drawActivePiece (7, 38, 3);
    glColor4f (0.0, 1.0, 0.0, 1.5); loadNewPiece (2, 0, 2); drawActivePiece (11, 38, 3);
    glColor4f (0.0, 0.0, 1.0, 1.5); loadNewPiece (3, 0, 2); drawActivePiece (15, 38, 3);
    glColor4f (0.7, 0.0, 1.0, 1.5); loadNewPiece (4, 0, 2); drawActivePiece (19, 38, 3);
    glColor4f (1.0, 0.9, 0.0, 1.5); loadNewPiece (5, 0, 2); drawActivePiece (23, 38, 3);
    glColor4f (1.0, 1.0, 1.0, 1.5); loadNewPiece (6, 0, 2); drawActivePiece (27, 38, 3);
    glColor4f (0.0, 1.0, 0.0, 1.5); loadNewPiece (0, 0, 2); drawActivePiece (31, 38, 3);
    glColor4f (1.0, 0.0, 0.0, 0.5); loadNewPiece (1, 0, 2); drawActivePiece (35, 38, 3);

    
    glLoadIdentity ();
}

void renderStartScreen ()
{
    pausedMode = 1;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
    GL_STENCIL_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    drawText ();
    drawStartStuff ();
}

void renderGameScreen ()
{
    int temp, temp2;
    glutSetCursor (GLUT_CURSOR_NONE);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
    GL_STENCIL_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    temp = 1024 * 768 * 3;
    if (pausedMode == 1)
    {
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);
        glEnable (GL_LIGHT1);
    }
    if (isBlendMode)
    {
        glShadeModel (GL_SMOOTH);
    }
    else
    {
        glShadeModel (GL_FLAT);
    }
    if (isLineMode)
    {
        glDisable (GL_DEPTH_TEST);
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth (0.01);
    }
    else
    {
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        glEnable (GL_DEPTH_TEST);
        glLineWidth (1.0);
    }
    if (isFogMode)
    {
    }
    drawText ();
    glPushMatrix();
    glViewport(0, 0, 768* weightBoard / 5, 1024);
    drawBoard ();
    drawActivePiece (moveX, moveY, 1);
    drawDroppedPieces ();
    glPopMatrix();
    checkFullRow ();
    drawNextBlock3D ();
    if (glGetError ())
    printf ("oops! Bad gl command!\n");
}

void renderHighScores ()
{
    pausedMode = 1;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
    GL_STENCIL_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.5, 0.5);
    glLoadIdentity ();
    drawText ();
}

void render (void)
{
    switch (gameMode)
    {
        case 1:
        {
            renderStartScreen ();
            break;
        }
        case 2:
        {
            renderGameScreen ();
            break;
        }
        case 3:
        {
            renderHighScores ();
            break;
        }
        case 4:
        {
        	renderSettingScreen ();
        	break;
        }
    }
    ticks += 1;
    glutSwapBuffers ();
    vRenderCnt += 1;
}

void drawActivePiece (int xCnt, int yCnt, int makeActive)
{
    int i, j;
    int sx, sy;
    int bet1 = 0;
    int bet2 = 0;
    int bet3 = 0;
    glPushMatrix ();
    j = 0;
    for (i = 0; i < 16; i++)
    {
        if ((i >= 0) && (i <= 3))
        {
            sx = xCnt + j;
            sy = yCnt;
        }
        if ((i >= 4) && (i <= 7))
        {
            if (bet1 == 0)
            {
                j = 0;
                bet1 = 1;
            }
            sx = xCnt + j;
            sy = yCnt - 1;
        }
        if ((i >= 8) && (i <= 11))
        {
            if (bet2 == 0)
            {
                j = 0;
                bet2 = 1;
            }
            sx = xCnt + j;
            sy = yCnt - 2;
        }
        if ((i >= 12) && (i <= 15))
        {
            if (bet3 == 0)
            {
                j = 0;
                bet3 = 1;
            }
            sx = xCnt + j;
            sy = yCnt - 3;
        }
        if (makeActive == 1)
        {
            if (currActivePiece[i].onoff == 1)
            {
                glLoadIdentity ();
                glTranslatef (sx + xOffSet, sy, 0);
                glCallList (currActivePiece[i].colour);
            }
        }
        if (makeActive == 2)
        {
            if (nextActivePiece[i].onoff == 1)
            {
                glLoadIdentity ();
                glTranslatef (sx + xOffSet, sy, 0);
                glCallList (nextActivePiece[i].colour);
            }
        }
        if (makeActive == 3)
        {
            if (nextActivePiece[i].onoff == 1)
            {
                glPushMatrix ();
                glLoadIdentity ();
                glTranslatef (sx + xOffSet, sy, -10);
                glRotatef (angle, 1.0, 1.0, 1.0);
                glutSolidCube (1);
                glPopMatrix ();
            }
        }
        if (makeActive == 4)
        {
            if (currDecidePiece[i].onoff == 1)
            {
                glPushMatrix ();
                glLoadIdentity ();
                glTranslatef (sx + xOffSet, sy, -10);
                glCallList (12);
                glPopMatrix ();
            }
        }
        j = j + 1;
    }
    glPopMatrix ();
}

int getRotNumbers (int rotPiece)
{
    int retVal;
    switch (rotPiece)
    {
        case 0:
        {
            retVal = 0;
            break;
        }
        case 1:
        {
            retVal = 16;
            break;
        }
        case 2:
        {
            retVal = 32;
            break;
        }
        case 3:
        {
            retVal = 48;
            break;
        }
        default:
        {
            retVal = 0;
            break;
        }
    }
    return retVal;
}

void loadPiece (int shape[], int pieceRot, int makeActive, int theColour)
{
    int bet1 = 0;
    int bet2 = 0;
    int bet3 = 0;
    int i, j;
    int cntPlus;
    cntPlus = getRotNumbers (pieceRot);
    j = 0;
    for (i = 0; i < 16; i++)
    {
        currTempPiece[i].onoff = shape[i + cntPlus];
        currTempPiece[i].colour = theColour;
        if ((i >= 0) && (i <= 3))
        {
            currTempPiece[i].x = moveX + j;
            currTempPiece[i].y = moveY;
        }
        if ((i >= 4) && (i <= 7))
        {
            if (bet1 == 0)
            {
                j = 0;
                bet1 = 1;
            }
            currTempPiece[i].x = moveX + j;
            currTempPiece[i].y = moveY - 1;
        }
        if ((i >= 8) && (i <= 11))
        {
            if (bet2 == 0)
            {
                j = 0;
                bet2 = 1;
            }
            currTempPiece[i].x = moveX + j;
            currTempPiece[i].y = moveY - 2;
        }
        if ((i >= 12) && (i <= 15))
        {
            if (bet3 == 0)
            {
                j = 0;
                bet3 = 1;
            }
            currTempPiece[i].x = moveX + j;
            currTempPiece[i].y = moveY - 3;
        }
        if (makeActive == 1)
        {
            currActivePiece[i].onoff = currTempPiece[i].onoff;
            currActivePiece[i].x = currTempPiece[i].x;
            currActivePiece[i].y = currTempPiece[i].y;
            currActivePiece[i].colour = theColour;
        }
        if (makeActive == 2)
        {
            nextActivePiece[i].onoff = currTempPiece[i].onoff;
            nextActivePiece[i].x = currTempPiece[i].x;
            nextActivePiece[i].y = currTempPiece[i].y;
            nextActivePiece[i].colour = theColour;
        }
        j = j + 1;
    }
}

void loadNewPiece (int pieceNo, int pieceRot, int makeActive)
{
    switch (pieceNo)
    {
        case 0:
        {
            loadPiece (shape_L, pieceRot, makeActive, yellow);
            pieceColour = yellow;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Yellow");
            noL += 1;
            break;
        }
        case 1:
        {
            loadPiece (shape_S, pieceRot, makeActive, blue);
            pieceColour = blue;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Blue");
            noS += 1;
            break;
        }
        case 2:
        {
            loadPiece (shape_Z, pieceRot, makeActive, white);
            pieceColour = black;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Black");
            noZ += 1;
            break;
        }
        case 3:
        {
            loadPiece (shape_O, pieceRot, makeActive, green);
            pieceColour = green;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Green");
            noO += 1;
            break;
        }
        case 4:
        {
            loadPiece (shape_T, pieceRot, makeActive, red);
            pieceColour = red;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Red");
            noT += 1;
            break;
        }
        case 5:
        {
            loadPiece (shape_EL, pieceRot, makeActive, purple);
            pieceColour = purple;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Purple");
            noEL += 1;
            break;
        }
        case 6:
        {
            loadPiece (shape_LE, pieceRot, makeActive, orange);
            pieceColour = orange;
            if (makeActive == 1)
            strcpy (pieceColourStr, "Orange");
            noLE += 1;
            break;
        }
    }
}

void loadDecidePiece (int shape[], int dAng, int xx, int yy)
{
    int bet1 = 0;
    int bet2 = 0;
    int bet3 = 0;
    int i, j;
    int cntPlus;
    j = 0;
    cntPlus = getRotNumbers (dAng);
    for (i = 0; i < 16; i++)
    {
        currDecidePiece[i].onoff = shape[i + cntPlus];
        if ((i >= 0) && (i <= 3))
        {
            currDecidePiece[i].x = xx + j;
            currDecidePiece[i].y = yy;
        }
        if ((i >= 4) && (i <= 7))
        {
            if (bet1 == 0)
            {
                j = 0;
                bet1 = 1;
            }
            currDecidePiece[i].x = xx + j;
            currDecidePiece[i].y = yy - 1;
        }
        if ((i >= 8) && (i <= 11))
        {
            if (bet2 == 0)
            {
                j = 0;
                bet2 = 1;
            }
            currDecidePiece[i].x = xx + j;
            currDecidePiece[i].y = yy - 2;
        }
        if ((i >= 12) && (i <= 15))
        {
            if (bet3 == 0)
            {
                j = 0;
                bet3 = 1;
            }
            currDecidePiece[i].x = xx + j;
            currDecidePiece[i].y = yy - 3;
        }
    }
    j = j + 1;
}

void loadDecide (int xx, int yy, int dNum, int dAng)
{
    switch (dNum)
    {
        case 0:
        {
            loadDecidePiece (shape_L, dAng, xx, yy);
            break;
        }
        case 1:
        {
            loadDecidePiece (shape_S, dAng, xx, yy);
            break;
        }
        case 2:
        {
            loadDecidePiece (shape_Z, dAng, xx, yy);
            break;
        }
        case 3:
        {
            loadDecidePiece (shape_O, dAng, xx, yy);
            break;
        }
        case 4:
        {
            loadDecidePiece (shape_T, dAng, xx, yy);
            break;
        }
        case 5:
        {
            loadDecidePiece (shape_EL, dAng, xx, yy);
            break;
        }
        case 6:
        {
            loadDecidePiece (shape_LE, dAng, xx, yy);
            break;
        }
    }
}

void initNewPiece ()
{
    needNewPiece = 0;
    moveX = STARTX;
    moveY = STARTY;
    pieceAngle = 0;
    loadNewPiece (newPieceNo, 0, 1);
    currPieceNo = newPieceNo;
    newPieceNo = rand () % 7;
    loadNewPiece (newPieceNo, 0, 2);
    currScore += 50;
}

void drawDroppedPieces ()
{
    glLoadIdentity ();
    glPushMatrix ();
    for (int i = 4; i < 14; i++)
    {
        for (int j = 4; j < 35; j++)
        {
            if (theBoard[i][j].onoff == 1)
            {
                glLoadIdentity ();
                glTranslatef (theBoard[i][j].x + xOffSet, theBoard[i][j].y, 0);
                glCallList (theBoard[i][j].colour);
            }
        }
    }
    glPopMatrix ();
    glutPostRedisplay ();
}

int getLowest (int xVal, int decideNum, int decideAngle)
{
    int canMove = 1;
    int retVal = 35;
    int temp = 0;
    for (int k = 34; k > 4; k--)
    {
        loadDecide (xVal, k, decideNum, decideAngle);
        for (int i = 0; i < 30; i++)
        {
            if (currDecidePiece[i].onoff == 1)
            {
                if (currDecidePiece[i].x <= 3)
                continue;
                if ((theBoard[currDecidePiece[i].x]
                [currDecidePiece[i].y].onoff == 1)
                ||
                (currDecidePiece[i].y <= 4))
                {
                    temp = currDecidePiece[i].y;
                    if (temp < retVal)
                    retVal = temp;
                    canMove = 0;
                    break;
                }
            }
            if (canMove == 0)
            break;
        }
    }
    return retVal;
}

void checkFullRow ()
{
    int isPieceReset = 0;
    OKnewPiece = 0;
    int numRow = 0;
    for (int i = 4; i < 35; i++)
    {
        if ((theBoard[4][i].onoff == 1) && (theBoard[5][i].onoff == 1)
        &&
        (theBoard[6][i].onoff == 1) && (theBoard[7][i].onoff == 1)
        &&
        (theBoard[8][i].onoff == 1) && (theBoard[9][i].onoff == 1)
        &&
        (theBoard[10][i].onoff == 1)
        && (theBoard[11][i].onoff == 1)
        &&
        (theBoard[12][i].onoff == 1) && (theBoard[13][i].onoff == 1))
        {
            moveDown (i);
            totNumRowsDone += 1;
            numRow += 1;
        }
    }
    OKnewPiece = 1;
    switch (numRow)
    {
        case 4:
        {
            totNum4 += 1;
            break;
        }
        case 3:
        {
            totNum3 += 1;
        }
        case 2:
        {
            totNum2 += 1;
            break;
        }
        case 1:
        {
            totNum1 += 1;
            break;
        }
    }
    if (numRow > 4)
    totNumOther += 1;
    numRow = 0;
}

void rotatePiece ()
{
    int canMove = 1;
    int i, j;
    int tempAngle;
    tempAngle = pieceAngle + 1;
    if (tempAngle == 4)
    tempAngle = 0;
    loadNewPiece (currPieceNo, tempAngle, 0);
    for (i = 0; i < 16; i++)
    {
        if (currTempPiece[i].onoff == 1)
        {
            if (currTempPiece[i].x + xOffSet < 3)
            canMove = 0;
            if (currTempPiece[i].x + xOffSet > 12)
            canMove = 0;
            if (theBoard[currTempPiece[i].x][currTempPiece[i].y].onoff == 1)
            canMove = 0;
        }
    }
    if (canMove == 1)
    {
        pieceAngle = pieceAngle + 1;
        if (pieceAngle == 4)
        pieceAngle = 0;
        for (i = 0; i < 16; i++)
        {
            currActivePiece[i].onoff = currTempPiece[i].onoff;
            currActivePiece[i].x = currTempPiece[i].x;
            currActivePiece[i].y = currTempPiece[i].y;
            currActivePiece[i].colour = currTempPiece[i].colour;
        }
        loadNewPiece (currPieceNo, pieceAngle, 1);
    }
}

void movePieceX (int mag)
{
    int canMove = 1;
    int i, j;
    for (i = 0; i < 16; i++)
    {
        if (currActivePiece[i].onoff == 1)
        {
            if (currActivePiece[i].x + xOffSet + mag < 3)
            canMove = 0;
            if (currActivePiece[i].x + xOffSet + mag > 12)
            canMove = 0;
            if (theBoard[currActivePiece[i].x + mag]
            [currActivePiece[i].y].onoff == 1)
            canMove = 0;
        }
    }
    if (canMove == 1)
    {
        moveX = moveX + mag;
        for (i = 0; i < 16; i++)
        {
            currActivePiece[i].x += mag;
        }
    }
}

void movePieceY (int mag)
{
    int canMove = 1;
    for (int i = 0; i < 16; i++)
    {
        if (currActivePiece[i].onoff == 1)
        {
            if (currActivePiece[i].y + mag <= 3)
            canMove = 0;
            if (theBoard[currActivePiece[i].x]
            [currActivePiece[i].y + mag].onoff == 1)
            canMove = 0;
        }
    }
    if (canMove == 0)
    {
        fillBoard ();
        needNewPiece = 1;
    }
    if (canMove == 1)
    {
        moveY += mag;
        for (int i = 0; i < 16; i++)
        {
            currActivePiece[i].y += mag;
        }
    }
}

void mouse (int button, int state, int x, int y)
{
    
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            anchorX = x;
            anchorY = y;
            stretchX = x;
            stretchY = y;
        }
        
        if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446)
        && (mouseY <= 271) && (mouseY >= 251))
        {
            gameMode = 2;
            pausedMode = 0;
            resetPit ();
            gameInProgress = 1;
            initNewPiece ();
        }
        if ((gameMode == 1) && (mouseX <= 490) && (mouseX >= 446)
        && (mouseY <= 385) && (mouseY >= 363))
        {
            exit (0);
        }
    }
}

void motion (int x, int y)
{
    stretchX = x;
    stretchY = y;
}

void passive (int x, int y)
{
    mouseX = x;
    mouseY = y;

    glBegin (GL_LINE_STRIP);
        glVertex2f (mouseX + 20, mouseX - 20);
        glVertex2f (mouseY + 20, mouseY - 20);
    glEnd ();

    
    if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446)
    && (mouseY <= 271) && (mouseY >= 251))
    {
        startCnt = 0;
        glutSetCursor (GLUT_CURSOR_INHERIT);
    }
    if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446)
    && (mouseY <= 311) && (mouseY >= 293))
    {
        startCnt = 1;
        glutSetCursor (GLUT_CURSOR_INHERIT);
    }
    if ((gameMode == 1) && (mouseX <= 516) && (mouseX >= 446)
    && (mouseY <= 343) && (mouseY >= 330))
    {
        startCnt = 2;
        glutSetCursor (GLUT_CURSOR_INHERIT);
    }
    if ((gameMode == 1) && (mouseX <= 490) && (mouseX >= 446)
    && (mouseY <= 385) && (mouseY >= 363))
    {
        startCnt = 3;
        glutSetCursor (GLUT_CURSOR_INHERIT);
    }
    if ((gameMode == 1) && (gameInProgress) &&
    (mouseX <= 524) && (mouseX >= 446) && (mouseY <= 231)
    && (mouseY >= 213))
    {
        startCnt = 4;
        glutSetCursor (GLUT_CURSOR_INHERIT);
    }
}

void idle (void)
{
    angle = angle + 0.4;
    glutPostRedisplay ();
    vIdleCnt += 1;
}

void visible (int vis)
{   
	glutIdleFunc (idle);
}

void key (unsigned char key, int px, int py)
{
    switch (key)
    {
        case 27:
        {
            if (gameMode == 1 && startCnt == 1)
            {
                printf ("dieeee!!!\n");
                exit (0);
            }
            if (gameMode == 2)
            {
                gameMode = 1;
                pausedMode = 0;
                startCnt = 2;
                glutSetCursor (GLUT_CURSOR_FULL_CROSSHAIR);
            }
            if (gameMode == 4)
            {
            	gameMode = 1;
            }
            break;
        }
        case 13:
        {
            if (gameMode == 1 && startCnt == 1)
            {
                printf ("dieeee!!!\n");
                exit (0);
            }
            if ((gameMode == 1) && (startCnt == 0))
            {
                gameMode = 2;
                pausedMode = 0;
                resetPit ();
                gameInProgress = 1;
                initNewPiece ();
            }
            if ((gameMode == 1) && (startCnt == 1))
            {
                exit (0);
            }
            if ((gameMode == 1) && (startCnt == 2))
            {
                gameMode = 2;
                pausedMode = 0;
                gameInProgress = 1;
            }
            if ((gameMode == 1) && (startCnt == -1))
            {
            	gameMode = 4;
            }
            if ((gameMode == 4) && (settCnt == 0))
            {
            	weightBoard++;
            }
            if ((gameMode == 4) && (settCnt == 1))
            {
            	weightBoard--;
            }
            break;
        }
        case 'b':
        {
            isBlendMode = !isBlendMode;
            break;
        }
        case 'l':
        {
            isLineMode = !isLineMode;
            break;
        }
        case 'f':
        {
            isFogMode = !isFogMode;
            break;
        }
        case 't':
        {
            isTrailsMode = !isTrailsMode;
            break;
        }
        case '\t':
        {
            break;
        }
        case 'p':
        {
            if (gameMode == 2)
            {
                startCnt = 2;
                pausedMode = !pausedMode;
                if (pausedMode == 1)
                glutIdleFunc (NULL);
                else
                glutIdleFunc (idle);
            }
            break;
        }
        case 'x':
        {
            glEnable (GL_LIGHT1);
            glEnable (GL_LIGHT0);
            glEnable (GL_LIGHTING);
            break;
        }
    }
}

void keyup (unsigned char key, int x, int y)
{
}

void special (int key, int x, int y)
{
    int i = 0;
    switch (key)
    {
        case GLUT_KEY_RIGHT:
        {
            if (pausedMode == 0)
            movePieceX (1);
            i++;
        }
        break;
        case GLUT_KEY_LEFT:
        {
            if (pausedMode == 0)
            movePieceX (-1);
            i++;
        }
        break;
        case GLUT_KEY_DOWN:
        {
            if ((gameMode == 2) && (pausedMode == 0))
            movePieceY (-1);
            if (gameMode == 1)
            {
                startCnt += 1;
                if (gameInProgress)
                {
                    if (startCnt > 2)
                    startCnt = 2;
                }
                else
                {
                    if (startCnt > 1)
                    startCnt = 1;
                }
            }
            if (gameMode == 4)
            {
            	settCnt +=1;
            	if (settCnt > 1)
            	settCnt = 1;
            }
            i++;
        }
        break;
        case GLUT_KEY_UP:
        {
            if ((gameMode == 2) && (pausedMode == 0))
            {
                rotatePiece ();
                break;
            }
            if (gameMode == 1)
            {
                startCnt -= 1;
                if (startCnt < -1)
                startCnt = -1;
            }
            if (gameMode == 4)
            {
            	settCnt -=1;
            	if(settCnt < 0)
            	settCnt = 0;
            }
            i++;
        }
        break;
        case GLUT_KEY_F1:
        {
            if ((gameMode == 1) && (startCnt == 0))
            {
                gameMode = 2;
                pausedMode = 0;
                resetPit ();
                gameInProgress = 1;
                initNewPiece ();
            }
            if ((gameMode == 1) && (startCnt == 1))
            {
                exit (0);
            }
            if ((gameMode == 1) && (startCnt == 2))
            {
                gameMode = 2;
                pausedMode = 0;
                gameInProgress = 1;
            }
            i++;
        }
        break;
    }
    if (i)
    glutPostRedisplay ();
}

void specialup (int key, int x, int y)
{
}

void moveColours ()
{
    int tempColour;
    for (int i = 4; i < 14; i++)
    {
        for (int j = 4; j < 35; j++)
        {
            if (theBoard[i][j].onoff == 1)
            {
                if (theBoard[i][j + 1].onoff == 1)
                {
                    if (i == 13)
                    theBoard[i][j].colour = theBoard[1][j].colour;
                    else
                    theBoard[i][j].colour = theBoard[i][j + 1].colour;
                }
            }
        }
    }
}

void timerFunc (int value)
{
    switch (value)
    {
        case 1:
        {
            glutTimerFunc (250, timerFunc, 1);
            if ((needNewPiece == 1) && (OKnewPiece == 1))
            {
                initNewPiece ();
            }
            else
            {
                if (pausedMode == 0)
                movePieceY (-1);
            }
            break;
        }
        case 2:
        {
            glutTimerFunc (1000, timerFunc, 2);
            fps = ticks;
            ticks = 0;
            break;
        }
        case 3:
        {
            glutTimerFunc (50, timerFunc, 3);
            break;
        }
    }
}

void initDisplayLists ()
{
    border1 = glGenLists (11);
    glNewList (border1, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (1, 0, 0);
            glVertex3f (2, 0, 0);
            glColor3f (0, 1, 1);
            glVertex3f (2, 1, 0);
            glColor3f (0, 0, 1);
            glVertex3f (1, 1, 0);
            glColor3f (1, 1, 1);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    border2 = border1 + 1;
    glNewList (border2, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (0, 0, 1);
            glVertex3f (2, 0, 0);
            glColor3f (1.0, 1.0, 1.0);
            glVertex3f (2, 1, 0);
            glColor3f (1, 1, 1);
            glVertex3f (1, 1, 0);
            glColor3f (1.0, 1.0, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    blue = border2 + 1;
    glNewList (blue, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor4f (0.0, 0.0, 0.3, 1.0);
            glVertex3f (2, 0, 0);
            glColor4f (0.0, 0.0, 0.3, 1.0);
            glVertex3f (2, 1, 0);
            glColor4f (0.0, 0.0, 1.0, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (0.0, 0.0, 0.3, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    darkgrey = blue + 1;
    glNewList (darkgrey, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (0.7, 0.7, 0.7);
            glVertex3f (2, 0, 0);
            glColor3f (0.7, 0.7, 0.7);
            glVertex3f (2, 1, 0);
            glColor3f (1, 1, 1);
            glVertex3f (1, 1, 0);
            glColor3f (0.7, 0.7, 0.7);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    yellow = darkgrey + 1;
    glNewList (yellow, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor4f (0.7, 0.7, 0.0, 1.0);
            glVertex3f (2, 0, 0);
            glColor4f (0.7, 0.7, 0.0, 1.0);
            glVertex3f (2, 1, 0);
            glColor4f (1.0, 1.0, 0.0, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (0.7, 0.7, 0.0, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    white = yellow + 1;
    glNewList (white, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (1.0, 1.0, 1.0);
            glVertex3f (2, 0, 0);
            glColor3f (1.0, 1.0, 1.0);
            glVertex3f (2, 1, 0);
            glColor3f (0.6, 0.6, 0.6);
            glVertex3f (1, 1, 0);
            glColor3f (1.0, 1.0, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    green = white + 1;
    glNewList (green, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor4f (0.0, 0.2, 0.0, 1.0);
            glVertex3f (2, 0, 0);
            glColor4f (0.0, 0.2, 0.0, 1.0);
            glVertex3f (2, 1, 0);
            glColor4f (0.0, 0.7, 0.0, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (0.0, 0.2, 0.0, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    red = green + 1;
    glNewList (red, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (0.4, 0.0, 0.0);
            glVertex3f (2, 0, 0);
            glColor3f (0.4, 0.0, 0.0);
            glVertex3f (2, 1, 0);
            glColor3f (1.0, 0.0, 0.0);
            glVertex3f (1, 1, 0);
            glColor3f (0.4, 0.0, 0.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();
    black = red + 1;
    glNewList (black, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor3f (0.0, 0.0, 0.0);
            glVertex3f (2, 0, 0);
            glColor3f (0.0, 0.0, 0.0);
            glVertex3f (2, 1, 0);
            glColor3f (0.3, 0.3, 0.3);
            glVertex3f (1, 1, 0);
            glColor3f (0.0, 0.0, 0.0);
            glVertex3f (1, 0, 0);
            glEnd ();
    glEndList();

    orange = black + 1;
    glNewList (orange, GL_COMPILE);
        glBegin (GL_QUADS);
            glColor4f (1.0, 0.45, 0.0, 1.0);
            glVertex3f (2, 0, 0);
            glColor4f (1.0, 0.45, 0.0, 1.0);
            glVertex3f (2, 1, 0);
            glColor4f (1.0, 0.9, 0.0, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (1.0, 0.45, 0.0, 1.0);
            glVertex3f (1, 0, 0);
        glEnd();
    glEndList();

    purple = orange + 1;
        glNewList (purple, GL_COMPILE);
            glBegin (GL_QUADS);
            glColor4f (0.5, 0.0, 1.0, 1.5);
            glVertex3f (2, 0, 0);
            glColor4f (0.5, 0.0, 1.0, 1.5);
            glVertex3f (2, 1, 0);
            glColor4f (0.7, 0.0, 1.0, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (0.5, 0.0, 1.0, 1.5);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();

    decidePiece = purple + 1;
        glNewList (decidePiece, GL_COMPILE);
            glBegin (GL_QUADS);
            glColor4f (0.8, 0.8, 0.8, 1.0);
            glVertex3f (2, 0, 0);
            glColor4f (0.8, 0.8, 0.8, 1.0);
            glVertex3f (2, 1, 0);
            glColor4f (0.8, 0.8, 0.8, 1.0);
            glVertex3f (1, 1, 0);
            glColor4f (0.8, 0.8, 0.8, 1.0);
            glVertex3f (1, 0, 0);
        glEnd ();
    glEndList ();
}

void renderSettingScreen()
{
	pausedMode = 1;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
    GL_STENCIL_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    drawText ();
    drawStartStuff ();	
}



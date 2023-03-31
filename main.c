#include "game.c"


#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void initWindow (void)
{
    glutDisplayFunc (render);
    glutVisibilityFunc (visible);
    glutKeyboardFunc (key);
    glutKeyboardUpFunc (keyup);
    glutSpecialFunc (special);
    glutSpecialUpFunc (specialup);
    glutTimerFunc (1000, timerFunc, 1);
    glutTimerFunc (1000, timerFunc, 2);
    glutTimerFunc (300, timerFunc, 3);
    glPointSize (3.0);
    glEnable (GL_BLEND);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_NORMALIZE);
    glEnable (GL_ALPHA_TEST);
    glEnable (GL_POLYGON_SMOOTH);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_ALWAYS);
    glEnable (GL_CULL_FACE);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glLightfv (GL_LIGHT1, GL_AMBIENT, LightAmbient); 
    glLightfv (GL_LIGHT1, GL_DIFFUSE, LightDiffuse); 
    glLightfv (GL_LIGHT1, GL_POSITION, LightPosition); 
    glEnable (GL_LIGHT1); 
    glEnable (GL_COLOR_MATERIAL);    
    glMatrixMode (GL_PROJECTION);
    gluPerspective (80,              
                    786 / 1024,       
                    1.0,            
                    -900.0           
    ); 
    glLoadIdentity ();
    glOrtho (0, 40, 0, 40, 0, 40);
    glMatrixMode (GL_MODELVIEW);
    gluLookAt (0.0, 0.0, 600.0,     
               0.0, 0.0, 0.0,      
               0.0, 1.0, 0.0        
    ); 
    for (int i = 3; i < 14; i++)
    {
        for (int j = 4; j < 35; j++)
        {
            theBoard[i][j].x = i;
            theBoard[i][j].y = j;
            theBoard[i][j].onoff = 0;
            theBoard[i][j].colour = 0;
        }
    }
    newPieceNo = rand () % 7;
    getRotNumbers (0);
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    if (isGameMode)
    {
        glutGameModeString ("1024x768:32");
        if (glutGameModeGet (GLUT_GAME_MODE_POSSIBLE))
        glutEnterGameMode ();
        else
        isGameMode = 0;
    }
    if (!isGameMode)
    {
        glutInitWindowSize (1024, 768);
        glutCreateWindow ("tetris");
    }
    initWindow ();
    initDisplayLists ();
    glutMainLoop ();
    return 0;
}

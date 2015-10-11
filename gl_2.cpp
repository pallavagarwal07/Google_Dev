#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
GLfloat angle = 0;
int first, second;
void init ( GLvoid )
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
    glTranslatef(0.0f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
    glRotatef(angle, 0, 1, 0);
    glutSolidCube(1);
    glRotatef(-angle, 0, 1, 0);
    //angle += 0.5f;
    glutSwapBuffers ( );
    if(glutGetWindow() == first)
        glutSetWindow(second);
    else
        glutSetWindow(first);
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glPushMatrix();
    gluLookAt(6, 0, 0, 0, 0, -6, 0, 1, 0);
    //glTranslatef(-3.0f,0.0f,0.0f);						// Move Left 1.5 Units And Into The Screen 6.0
    display();
}
void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glPushMatrix();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
    display();
}

void reshape ( int w, int h )   // Create The Reshape Function (the viewport)
{
    glViewport     ( 0, 0, w, h );
    glMatrixMode   ( GL_PROJECTION );  // Select The Projection Matrix
    glLoadIdentity ( );                // Reset The Projection Matrix
    if ( h==0 )  // Calculate The Aspect Ratio Of The Window
        gluPerspective ( 80, ( float ) w, 1.0, 5000.0 );
    else
        gluPerspective ( 80, ( float ) w / ( float ) h, 1.0, 5000.0 );
    glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
    glLoadIdentity ( );    // Reset The Model View Matrix
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
    switch ( key ) {
        case 27:
            exit ( 0 );
            break;
        default:
            break;
    }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
    switch ( a_keys ) {
        case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
            glutFullScreen(); // Go Into Full Screen Mode
            break;
        case GLUT_KEY_LEFT:
            angle += 5;
            break;
        case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
            glutReshapeWindow(500, 500); // Go Into A 500 By 500 Window
            break;
        default:
            break;
    }
}
static void TimeEvent(int te)
{
    //angle+=4;  // increase cube rotation by 1
	if (angle > 360) angle = 0; // if over 360 degress, start back at zero.
 
	glutSetWindow(first);
	glutPostRedisplay();  // Update screen with new rotation data
 
	glutSetWindow(second);
	glutPostRedisplay();  // Update screen with new rotation data
 
	glutTimerFunc( 10, TimeEvent, 1);  // Reset our timmer.
}
 

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
    glEnable ( GL_LIGHTING ) ;
    glutInit(&argc, argv); // Erm Just Write It =)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode
    glutInitWindowSize(500, 500); // If glutFullScreen wasn't called this is the window size
    glutTimerFunc( 10, TimeEvent, 1);

    first = glutCreateWindow("cube"); // Window Title (argv[0] for current directory as title)
    init();
    glutDisplayFunc(display1);  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display1);

    second = glutCreateWindow("side"); // Window Title (argv[0] for current directory as title)
    init();
    glutDisplayFunc(display2);  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display2);

    glutMainLoop();          // Initialize The Main Loop
}


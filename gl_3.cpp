#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include "Leap.h"

using namespace Leap;
using namespace std;

int first, frames_n = 0;
Vector coordinates[10][4];
Vector Tangent = Vector(0,0,0);
Vector Normal = Vector(0,0,0);
void oneFrame(const Controller& controller);
double matrix[16] = {0};

class SampleListener:public Listener {
    public:
        virtual void onConnect(const Controller&);
        virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller){
    cout << "Connected" << endl;
    controller.enableGesture(Gesture::TYPE_SWIPE);
    //oneFrame(controller);
}

void SampleListener::onFrame(const Controller& controller)
{
    oneFrame(controller);
    const Frame frame = controller.frame();
    Leap::GestureList gestures = frame.gestures();
	glutSetWindow(first);
	glutPostRedisplay();  // Update screen with new rotation data
    for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++)
    {
        switch ((*gl).state()) {
            case Leap::Gesture::STATE_START:
                cout << "Start" << endl;//Handle starting gestures
                break;
            case Leap::Gesture::STATE_UPDATE:
                //cout << "continuing";//Handle continuing gestures
                break;
            case Leap::Gesture::STATE_STOP:
                {    cout << "stop" << endl;//Handle ending gestures
                    std::string clockwiseness;
                    Leap::SwipeGesture circleGesture = Leap::SwipeGesture(*gl);
                    /*if ((circleGesture).pointable().direction().angleTo((circleGesture.normal())) <= Leap::PI/2) {
                      clockwiseness = "clockwise";
                      }
                      else
                      {
                      clockwiseness = "counterclockwise";
                      }*/
                    Tangent = circleGesture.direction();
                    double a = Tangent[0],b = Tangent[1], c = Tangent[2];
                    double d = sqrt(2*c*c+(b-a)*(b-a));
                    Normal = Vector(c/d,-c/d,(b-a)/d);
                    cout << Normal << endl;
                    frames_n = 60;
                    break;
                }
            default:
                //Handle unrecognized states
                break;
        }
    }
}
void oneFrame(const Controller& controller){
    const Frame frame = controller.frame();
    HandList hands = frame.hands();
    int i;
    Finger fingers[10];
    for(i=0;i<10;i++)
    {
        fingers[i]=hands[i/5].fingers()[i%5];
        int j;
        for(j=1;j<4;j++)
        {
            Bone::Type boneType = static_cast<Leap::Bone::Type>(j);
            Bone bone = fingers[i].bone(boneType);// << endl;
            if(j==1)
                coordinates[i][0]=bone.prevJoint();
            coordinates[i][j]=bone.nextJoint();
        }
    }
}

void gesture(const Controller& controller)
{
    const Frame frame = controller.frame();
    Leap::GestureList gestures = frame.gestures();
    for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++)
    {
        switch ((*gl).state()) {
            case Leap::Gesture::STATE_START:
                cout << "Start";//Handle starting gestures
                break;
            case Leap::Gesture::STATE_UPDATE:
                cout << "continuing";//Handle continuing gestures
                break;
            case Leap::Gesture::STATE_STOP:
                cout << "stop";//Handle ending gestures
                break;
            default:
                break;
        }
    }
}

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
GLfloat angle = 0;


void joinCyllinder(float x1, float y1, float z1, float x2, float y2, float z2)
{
            glPushMatrix();
            glLoadIdentity();
            float r = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
            glTranslatef(x1, y1, z1);
            glRotatef(180, (x2-x1)/2, (y2-y1)/2, (z2-z1+r)/2);
            glBegin(GL_QUADS);
            glVertex3f(0,0,r);
            glVertex3f(0.03, 0, 0);
            glVertex3f(0,0,-r);
            glVertex3f(-0.03, 0, 0);
            glEnd();
            glPopMatrix();
}

void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glPushMatrix();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
    glTranslatef(0.0f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
    if(frames_n != 0)
    {
        glPushMatrix();
        glLoadMatrixd(matrix);
        glRotatef(2, Normal[0], Normal[1], Normal[2]);
        frames_n--;
        glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
        glutWireCube(1);
        glPopMatrix();
    }
    else
    {
        glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
        glutWireCube(1);
    }
    glRotatef(angle, 0, 1, 0);
    for(int i=0; i<10; i++)
        for(int j=0; j<4; j++)
        {
            float x1 = coordinates[i][j][0]/75, y1 = coordinates[i][j][1]/75 - 1, z1 = -6 + coordinates[i][j][2]/75;
            if(j<3)
            {
                float x2 = coordinates[i][j+1][0]/75, y2 = coordinates[i][j+1][1]/75 - 1, z2 = -6 + coordinates[i][j+1][2]/75;
                joinCyllinder(x1, y1, z1, x2, y2, z2);
            }
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(x1, y1, z1);
            glutWireSphere(.03f, 10, 10);
            glPopMatrix();
        }
    angle += 1;
    glRotatef(-angle, 0, 1, 0);
    glutSwapBuffers();
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
            break;
        case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
            glutReshapeWindow(500, 500); // Go Into A 500 By 500 Window
            break;
        default:
            break;
    }
}

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{

    glEnable ( GL_LIGHTING ) ;
    glutInit(&argc, argv); // Erm Just Write It =)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode
    glutInitWindowSize(500, 500); // If glutFullScreen wasn't called this is the window size

    first = glutCreateWindow("cube"); // Window Title (argv[0] for current directory as title)
    SampleListener listener;
    Controller controller;
    controller.addListener(listener);
    gesture(controller);
    cout << "Press Enter to quit..." << endl;
    init();
    glutDisplayFunc(display1);  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display1);

    glutMainLoop();          // Initialize The Main Loop
    controller.removeListener(listener);
}


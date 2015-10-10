#include <GL/glut.h>
#include <stdlib.h>
using namespace std;
void handleKeypress(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
        exit(0);
    }
}
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}
void handleResize(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0,(double)w/(double)h,1.0,200);
}
void drawScene1()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,-5.0f);
    glVertex3f(0.0f,1.0f,-5.0f);
    glVertex3f(1.0f,1.0f,-5.0f);
    glVertex3f(1.0f,0.0f,-5.0f);
    glEnd();
    glutSwapBuffers();
}

void drawScene2()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,-5.0f);
    glVertex3f(0.0f,1.0f,-5.0f);
    glVertex3f(1.0f,1.0f,-5.0f);
    glVertex3f(1.0f,0.0f,-5.0f);
    glEnd();
    glutSwapBuffers();
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    initRendering();
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("First window :-www.codeincodeblock.blogspot.com");
    glutDisplayFunc(drawScene1);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutCreateWindow("Second Window :www.codeincodeblock.blogspot.com");
    glutPositionWindow(540,40);
    glutReshapeFunc(handleResize);
    glutDisplayFunc(drawScene2);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}

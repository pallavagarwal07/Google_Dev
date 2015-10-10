#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

void setup() {
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluLookAt(0.0f, 0.0f, 0.0f, 0, 0, -1, 0, 1, 0);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glRectf(-0.75f,0.75f, 0.75f, -0.75f);
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Hello World");

    setup();
    glutDisplayFunc(display);

    glutMainLoop();

    getchar();//pause here to see results or lack there of
    return 0;
}

#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>



// Globals.
static unsigned int aCylinder; // List index.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate
bool wiredFrame=true;
const int N = 20; // number of vertices around the circumference
const float R = 5.0f; // radius of the cylinder
const float H = 100.0f; // height of the cylinder

#define CHAIR_X_POS 0
#define CHAIR_Y_POS -20
#define CHAIR_Z_POS -175

// Initialization routine.
void setup(void)
{
    aCylinder = glGenLists(1); // Return a list index.
    // Begin create a display list.
    glNewList(aCylinder, GL_COMPILE);
    //borders
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= N; i++) {
        float x = R * cos(2.0f * M_PI * i / N);
        float y = R * sin(2.0f * M_PI * i / N);
        float z = -H / 2.0f;
        glVertex3f(x, y, z);
        glVertex3f(x, y, z + H);
    }
    glEnd();
    //lower circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -H / 2.0f);
    for (int i = 0; i <= N; i++) {
        float x = R * cos(2.0f * M_PI * i / N);
        float y = R * sin(2.0f * M_PI * i / N);
        glVertex3f(x, y, -H / 2.0f);
    }
    glEnd();
    //upper circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, H / 2.0f);
    for (int i = 0; i <= N; i++) {
        float x = R * cos(2.0f * M_PI * i / N);
        float y = R * sin(2.0f * M_PI * i / N);
        glVertex3f(x, y, H / 2.0f);
    }
    glEnd();
    glEndList();
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void renderLeg1(){
    glPushMatrix();
    glTranslatef(30.0, 0, -20);
    glRotatef(90,1,0,0);
    glRotatef(20,0,1,0);
    glRotatef(20,1,0,1);
    glCallList(aCylinder);
    glPopMatrix();
}void renderLeg2(){
    glPushMatrix();
    glTranslatef(-30.0, 0, -20);
    glRotatef(90,1,0,0);
    glRotatef(-20,0,1,0);
    glRotatef(20,1,0,1);
    glCallList(aCylinder);
    glPopMatrix();

}void renderLeg3(){
    glPushMatrix();
    glTranslatef(0.0, 0.0, 30.0);
    glRotatef(90,1,0,0);
    glRotatef(-20,1,0,1);
    glCallList(aCylinder);
    glPopMatrix();
}
void renderSeat() {
    glPushMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, H/2 , 0);
    glScalef(8, 0.1, 8);
    glRotatef(90, 1, 0, 0);
    glCallList(aCylinder);
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
    if(wiredFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(CHAIR_X_POS, CHAIR_Y_POS, CHAIR_Z_POS);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    renderLeg1();
    renderLeg2();
    renderLeg3();
    renderSeat();
    glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'X':
            Xangle += 1.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'x':
            Xangle -= 1.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;
        case 'Y':
            Yangle += 1.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'y':
            Yangle -= 1.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;
        case 'Z':
            Zangle += 1.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'z':
            Zangle -= 1.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;
        case ' ':
            wiredFrame=!wiredFrame;
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE)z

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("helixList.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
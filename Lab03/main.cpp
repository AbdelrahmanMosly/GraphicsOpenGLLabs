///////////////////////////////////////////////////////////////////////////////////////          
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
//
// Interaction:
// Press P/p to increase/decrease the number of longitudinal slices.
// Press Q/q to increase/decrease the number of latitudinal slices.
// Press x, X, y, Y, z, Z to turn the hemisphere.
//
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////// 

#define _USE_MATH_DEFINES 

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
enum choice {sphere=1, helix=2};
static float R = 5.0; // Radius of hemisphere.
static int p = 6; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static float offset = -10;
static float spinSpeed = 5;
static float prev_time = 0;
int userChoice = 0;
bool wiredFrame=true;
float helixRadius=5.0;
float helixPitch=1.0;
float helixVertices=50;
int helixTurns=5;
// Initialization routine.

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
	int  i, j;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Command to push the hemisphere, which is drawn centered at the origin, 
	// into the viewing frustum.
	glTranslatef(0.0, 0.0, offset);

	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	// Hemisphere properties.
    if(wiredFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0.0, 0.0, 0.0);
    switch (userChoice) {
        case sphere:
            // Array of latitudinal triangle strips, each parallel to the equator, stacked one
            // above the other from the equator to the north pole.
            for (j = 0; j < q; j++)
            {
                // One latitudinal triangle strip.
                glBegin(GL_TRIANGLE_STRIP);
                for (i = 0; i <= p; i++)
                {
                    float red = (float) rand() / RAND_MAX;
                    float green = (float) rand() / RAND_MAX;
                    float blue = (float) rand() / RAND_MAX;
                    glColor3f(red, green, blue);
                    glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                               R * sin((float)(j + 1) / q * M_PI / 2.0),
                               -R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                    glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                               R * sin((float)j / q * M_PI / 2.0),
                               -R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                }
                glEnd();
            }
            for (j = q; j >= 0; j--)
            {
                // One latitudinal triangle strip.
                glBegin(GL_TRIANGLE_STRIP);
                for (i = 0; i <= p; i++)
                {
                    float red = (float) rand() / RAND_MAX;
                    float green = (float) rand() / RAND_MAX;
                    float blue = (float) rand() / RAND_MAX;
                    glColor3f(red, green, blue);
                    glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                               -R * sin((float)(j + 1) / q * M_PI / 2.0),
                               -R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                    glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                               -R * sin((float)j / q * M_PI / 2.0),
                               -R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                }
                glEnd();
            }
            break;
        case helix:

            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < helixVertices; i++) {
                float t=(float)i/(float)helixVertices;
                float angle = t * 2.0f * M_PI * helixTurns;

                float x = helixRadius * cos(angle);
                float y = helixRadius* sin(angle);
                float z = t*helixPitch*helixTurns;

                float red = (float) rand() / RAND_MAX;
                float green = (float) rand() / RAND_MAX;
                float blue = (float) rand() / RAND_MAX;
                glColor3f(red, green, blue);
                glVertex3f(x, y, z);

            }
            glEnd();

            break;
    }


	glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void spinDisplay() {
	Yangle += spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void spinDisplayReverse() {

	Yangle -= spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	std::cout << Yangle << std::endl;
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    prev_time=glutGet(GLUT_ELAPSED_TIME);
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplayReverse);

		break;
	default:
		break;
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'P':
		p += 1;
		glutPostRedisplay();
		break;
	case 'p':
		if (p > 3) p -= 1;
		glutPostRedisplay();
		break;
	case 'Q':
		q += 1;
		glutPostRedisplay();
		break;
	case 'q':
		if (q > 3) q -= 1;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case 'O':
		offset += 1;
		glutPostRedisplay();
		break;
	case 'o':
		offset -= 1;
		glutPostRedisplay();
		break;
    case 'W':
        wiredFrame=true;
        glutPostRedisplay();
        break;
    case 'w':
        wiredFrame=false;
        glutPostRedisplay();
        break;
    case 'R':
        helixRadius+=0.5f;
        glutPostRedisplay();
        break;
    case 'r':
        if(helixRadius>0.5f)
            helixRadius-=0.5f;
        glutPostRedisplay();
        break;
    case 'H':
        helixPitch+=0.1f;
        glutPostRedisplay();
        break;
    case 'h':
        if(helixPitch>0.2f)
            helixPitch-=0.1f;
        glutPostRedisplay();
        break;
    case 'N':
        helixVertices+=10;
        glutPostRedisplay();
        break;
    case 'n':
        if(helixVertices>10)
            helixVertices-=5;
        glutPostRedisplay();
        break;
	case ' ':
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press P/p to increase/decrease the number of longitudinal slices." << std::endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << std::endl
		<< "Press x, X, y, Y, z, Z to turn the Object."  << std::endl
        << "presses W/w, draw sphere in wireframe / draw filled sphere."  << std::endl
        << "presses R/r,  increase/decrease radius of the helix "<< std::endl
        << "pressesH/h, increase/decrease pitch of helix. "<< std::endl
        << "presses N/n, increase/decrease number of vertices used to draw the helix "<< std::endl;

}

// Main routine.
int main(int argc, char** argv)
{
    std::cout << "Which shape type do you want\n1) Sphere\n2) Helix\n>> ";
    std::cin >> userChoice;
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hemisphere.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
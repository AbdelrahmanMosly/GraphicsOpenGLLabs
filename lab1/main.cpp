// Interaction:
// Press +/- to add/erase random point ---> good practice to add interaction as a comment at the top of source code

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/vec3.hpp>
#include <random>
#include <iostream>

//points: datastructure to store current points
std::vector<glm::vec3> points;
// window dimension
float windowWidth = 500.0;
float windowHeight = 500.0;
//float orthogonals
float orthoRight=100.0;
float orthoTop=100.0;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1.0); // Default line width.
    /*
    ----------set point size below---------
    */
    glPointSize(5.0);
    //-------------------------------------

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    /*
    ----------write points drawing logic below------------
    */
    glBegin(GL_POINTS);
    for(glm::vec3 point: points) {
        glColor3f(dis(gen),dis(gen),dis(gen));
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
    //----------------------------------------------------
    /*
    ----------write lines drawing logic below------------
    */
    glBegin(GL_LINES);
    for(glm::vec3 point: points) {
        glColor3f(dis(gen),dis(gen),dis(gen));
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
    //----------------------------------------------------
    glFlush();
}
// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, orthoRight, 0.0, orthoTop, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: {
            exit(0);
        }
            /*
            ------------- Add +/- cases handling below (handle corner cases)----------------
            */
        case '+':
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(0.0, 1.0);

            glm::vec3 point(dis(gen) * (float)orthoRight, dis(gen) * (float)orthoTop, 0.0f);
            points.push_back(point);

            glutPostRedisplay();
            break;
        }case '-':
        {
            if(!points.empty()){
                points.pop_back();
                glutPostRedisplay();
            }
            break;
        }
            //-----------------------------------------------------------------------
        default:
            break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press +/- to add/erase random point" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    printInteraction(); // good practice to print how to interact
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RandomLines.cpp");
    glutDisplayFunc(drawScene);//drawing function
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);//handle keyboard events

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
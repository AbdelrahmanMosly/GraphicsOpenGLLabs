#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


#define VERTICES 0
#define INDICES 1
#define DDA_INDEX 0
#define BRESENHAM_INDEX 1

static float name_start_end[] =
        {
                30.0, 30.0, 0.0,
                10.0, 10.0, 0.0,
                70.0, 30.0, 0.0,
                90.0, 10.0, 0.0,
                70.0, 70.0, 0.0,
                90.0, 90.0, 0.0,
                30.0, 70.0, 0.0,
                10.0, 90.0, 0.0
        };
//Define DDA
vector<GLfloat> DDA(int x1,int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps= max(dx,dy);

    vector<GLfloat> vertices((steps + 1) * 3);

    float x_inc=dx/steps;
    float y_inc=dx/steps;

    for(int i=0;i<=steps;i++)
    {
        int x=round(x1);
        int y=round(y1);
        vertices[i*3]=x; //x
        vertices[i*3+1]=y; //y
        vertices[i*3+2]=0; //z

        x1+=x_inc;
        y1+=y_inc;
    }
    return vertices;
}


static unsigned int buffer[2]; // Array of buffer ids.

static unsigned int vao[2]; // Array of VAO ids.
// End globals.

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw annulus.
    glBindVertexArray(vao[DDA_INDEX]);
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS,0, 5);

//    // Draw triangle.
//    glBindVertexArray(vao[TRIANGLE]);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

// Initialization routine.
void setup(void)
{


    vector<GLfloat> name= DDA(0,0,5,5);
    
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glGenVertexArrays(2, vao); // Generate VAO ids.

    glBindVertexArray(vao[DDA_INDEX]);

    glGenBuffers(2, buffer);

    // Bind vertex buffer and reserve space.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, name.size() * sizeof(GLfloat), name.data(), GL_STATIC_DRAW);

//    // Copy vertex coordinates data into first half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1);
//
//    // Copy vertex color data into second half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(colors1), colors1);
//
//    // Bind and fill indices buffer.
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);

    // Enable two vertex arrays: co-ordinates and color.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Specify vertex and color pointers to the start of the respective data.
    glVertexPointer(3, GL_FLOAT, 0, 0);
//    glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(vertices1)));
    // END bind VAO id vao[ANNULUS].
//
//    // BEGIN bind VAO id vao[TRIANGLE] to the set of vertex array calls following.
//    glBindVertexArray(vao[TRIANGLE]);
//
//    glGenBuffers(1, buffer);
//
//    // Bind vertex buffer and reserve space.
//    glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2) + sizeof(colors2), NULL, GL_STATIC_DRAW);
//
//    // Copy vertex coordinates data into first half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);
//
//    // Copy vertex color data into second half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(colors2), colors2);
//
//    // Enable two vertex arrays: co-ordinates and color.
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
//
//    // Specify vertex and color pointers to the start of the respective data.
//    glVertexPointer(3, GL_FLOAT, 0, 0);
//    glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(vertices2)));
    // END bind VAO id vao[TRIANGLE].
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
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
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("squareAnnulusAndTriangleVAO.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
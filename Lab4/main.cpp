#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


#define VERTICES 0
#define DDA_INDEX 0
#define BRESENHAM_INDEX 1

#define DDA_XOFFSET 5
#define DDA_YOFFSET 5

#define BRESENHAM_XOFFSET 5
#define BRESENHAM_YOFFSET 25


int pointsDDACtr = 0;
int pointsBresenhamCtr = 0;
static GLfloat name_start_end[][4] =
        {
                {0,  0,  5,  10},
                {5,  10, 10, 0},
                {4,  5,  7,  5}, //A

                {12, 0,  12, 10},
                {12, 0,  17, 1},
                {12, 5,  17, 4},
                {17, 1,  17, 4}, //b

                {19, 1,  19, 4},
                {19, 0,  24, 1},
                {19, 5,  24, 4},
                {24, 0,  24, 10}, //d

                {26, 0,  26, 10},
                {26, 0,  31, 0},
                {26, 5,  31, 5},
                {26, 10, 31, 10},
                {31, 10, 31, 5},//e

                {33, 0,  33, 10}, // l

                {35, 0,  35, 10},
                {35, 9,  40, 9}, // r

                {42, 5,  42, 0},
                {42, 0,  47, 0},
                {42, 0,  47, 0},
                {42, 5,  47, 5},
                {42, 10, 47, 10},
                {47, 0,  47, 10},//a

                {49, 0,  49, 10},
                {49, 6,  54, 5},
                {54, 0,  54, 5}, // h


                {56, 0,  56, 5},
                {56, 5,  61, 5},
                {61, 0,  61, 5},
                {61, 5,  66, 5},
                {66, 0,  66, 5},// m

                {68, 5,  68, 0},
                {68, 0,  73, 0},
                {68, 5,  73, 5},
                {68, 10, 73, 10},
                {73, 0,  73, 10}, // a

                {75, 0,  75, 5},
                {75, 5,  80, 5},
                {80, 0,  80, 5},//n

        };

vector<GLfloat> DDA(float x1, float y1, float x2, float y2) {

    x1 += DDA_XOFFSET;
    y1 += DDA_YOFFSET;
    x2 += DDA_XOFFSET;
    y2 += DDA_YOFFSET;
    if(x2<x1)
    {
        int temp=x1;
        x1=x2;
        x2=temp;
        temp=y1;
        y1=y2;
        y2=temp;
    }


    int dx = x2 - x1;
    int dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));

    vector<GLfloat> vertices((steps + 1) * 3);

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    for (int i = 0; i <= steps; i++) {
        int x = round(x1);
        int y = round(y1);
        vertices[i * 3] = x; //x
        vertices[i * 3 + 1] = y; //y
        vertices[i * 3 + 2] = 0; //z

        x1 += x_inc;
        y1 += y_inc;
    }
    return vertices;
}

vector<GLfloat> bresenham(int x1, int y1, int x2, int y2) {
    x1 += BRESENHAM_XOFFSET;
    y1 += BRESENHAM_YOFFSET;
    x2 += BRESENHAM_XOFFSET;
    y2 += BRESENHAM_YOFFSET;
    int dx = x2 - x1;
    int dy = y2 - y1;

    int x = x1;
    int y = y1;


    int steps = max(abs(dx), abs(dy));
    vector<GLfloat> vertices((steps + 1) * 3);

    // -1 <slope m <1
    if (abs(dx) > abs(dy)) {
        int pk = 2 * abs(dy) - abs(dx);

        for (int i = 0; i <= steps; i++) {
            vertices[i * 3] = x; //x
            vertices[i * 3 + 1] = y; //y
            vertices[i * 3 + 2] = 0; //z

            x += dx>0?  1:  -1;
            if (pk < 0) {
                pk = pk + 2 * (abs(dy));
            }else{
                y += dy>0? 1 : -1;
                pk = pk + 2 * (abs(dy) -abs(dx)) ;
            }
        }
    } else {
        int pk = 2 * abs(dx) - abs(dy);

        for (int i = 0; i <= steps; i++) {
            vertices[i * 3] = x; //x
            vertices[i * 3 + 1] = y; //y
            vertices[i * 3 + 2] = 0; //z

            y += dy>0? 1 : -1;
            if (pk < 0) {
                pk = pk + 2 * (abs(dx));
            }else{
                x += dx>0?  1:  -1;
                pk = pk + 2 * (abs(dx) -abs(dy)) ;
            }
        }
    }
    return vertices;


}

static unsigned int buffer[2]; // Array of buffer ids.

static unsigned int vao[2]; // Array of VAO ids.
// End globals.

// Drawing routine.
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw annulus.
    glBindVertexArray(vao[DDA_INDEX]);
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, pointsDDACtr / 3);


    glBindVertexArray(vao[BRESENHAM_INDEX]);
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, pointsBresenhamCtr / 3);

    glFlush();
}
void setupDDA(){
    vector<GLfloat> nameDDA;

    int size_name_points = sizeof(name_start_end) / sizeof(name_start_end[0]);
    for (int i = 0; i < size_name_points; i++) {
        std::vector<GLfloat> line = DDA(name_start_end[i][0], name_start_end[i][1],
                                        name_start_end[i][2], name_start_end[i][3]);
        // Loop through the returned vector and add each element to the final result vector
        for (int j = 0; j < line.size(); j++) {
            pointsDDACtr++;
            nameDDA.push_back(line[j]);
        }
    }


    glClearColor(1.0, 1.0, 1.0, 0.0);

    glGenVertexArrays(2, vao); // Generate VAO ids.

    glBindVertexArray(vao[DDA_INDEX]);

    glGenBuffers(1, buffer);

    // Bind vertex buffer and reserve space.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, nameDDA.size() * sizeof(GLfloat), nameDDA.data(), GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Specify vertex and color pointers to the start of the respective data.
    glVertexPointer(3, GL_FLOAT, 0, 0);
}
void setupBresenham(){

    vector<GLfloat> nameBresenham;

    int size_name_points = sizeof(name_start_end) / sizeof(name_start_end[0]);
    for (int i = 0; i < size_name_points; i++) {
        std::vector<GLfloat> line = bresenham(name_start_end[i][0], name_start_end[i][1],
                                              name_start_end[i][2], name_start_end[i][3]);
        // Loop through the returned vector and add each element to the final result vector
        for (int j = 0; j < line.size(); j++) {
            pointsBresenhamCtr++;
            nameBresenham.push_back(line[j]);
        }
    }
    glBindVertexArray(vao[BRESENHAM_INDEX]);

    glGenBuffers(1, buffer);

    // Bind vertex buffer and reserve space.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, nameBresenham.size() * sizeof(GLfloat), nameBresenham.data(), GL_STATIC_DRAW);

    // Enable two vertex arrays: co-ordinates and color.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Specify vertex and color pointers to the start of the respective data.
    glVertexPointer(3, GL_FLOAT, 0, 0);
}

// Initialization routine.
void setup(void) {

    setupDDA();

    setupBresenham();
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

//    glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(vertices1)));
    // END bind VAO id vao[ANNULUS].
//
//    // BEGIN bind VAO id vao[TRIANGLE] to the set of vertex array calls following.




//    // Copy vertex coordinates data into first half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);
//
//    // Copy vertex color data into second half of vertex buffer.
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(colors2), colors2);
//



//    glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(vertices2)));
    // END bind VAO id vao[TRIANGLE].
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv) {
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
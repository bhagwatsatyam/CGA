#include <GL/glut.h> 
#include <cstdlib>
#include <iostream>
using namespace std;
void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0, 800, 0, 800); // set coordinate system
}
void my_display() {
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // boundary color (red)
    glBegin(GL_LINE_LOOP);
        glVertex2i(400, 600);
        glVertex2i(600, 200);
        glVertex2i(200, 200);
    glEnd(); 
    glFlush();
}

void boundary_fill(int x, int y, float* fillColor, float* boundaryColor)
{
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    bool isBoundary = (current[0] == boundaryColor[0] && current[1] == boundaryColor[1] && current[2] == boundaryColor[2]);
    bool isFilled = (current[0] == fillColor[0] && current[1] == fillColor[1] && current[2] == fillColor[2]);
    if (!isBoundary && !isFilled) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd(); 
        glFlush();
        // Recursively fill in 4 directions
        boundary_fill(x + 2, y, fillColor, boundaryColor);
        boundary_fill(x - 2, y, fillColor, boundaryColor);
        boundary_fill(x, y + 2, fillColor, boundaryColor);
        boundary_fill(x, y - 2, fillColor, boundaryColor);
    }
}
void mouse(int btn, int state, int x, int y) {
    y = 800 - y; // flip y-axis for OpenGL
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float boundaryColor[] = {1.0, 0.0, 0.0}; // red boundary
        float fillColor[] = {0.0, 1.0, 1.0};     // fill color (cyan)

        boundary_fill(x, y, fillColor, boundaryColor);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Boundary Fill Algorithm");
    cout << "Click inside the triangle to fill using Boundary Fill algorithm." << endl;
    glutDisplayFunc(my_display);
    glutMouseFunc(mouse);
    my_init();
    glutMainLoop();
    return 0;
}


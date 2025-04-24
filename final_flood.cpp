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

    glBegin(GL_LINE_LOOP);
    	glColor3f(1,0,0);
    	glVertex2i(400,200);
    	glColor3f(0,1,0);
    	glVertex2i(600,200);
    	glColor3f(0,0,1);
    	glVertex2i(200,200);
    	
    	glEnd();
    	glFlush();
}

void floodfill(int x,int y ,float * old ,float * newcolor)
{
	float c[3];
	glReadLine(x,y,1,1,GL_RGB,GL_FLOAT,c);
	if(c[0] == old[0] && c[1]==old[1] && c[2] == old[2])
	{
		float old[]={1.0,1.0,1.0};
		float newc[]={0.0,1.0,0.0};
		
		floodfill(x+2,y,old,newcolor);
		floddfill(x-2,y,old,newcolor);
		floodfill(x,y+2,old,newcolor);
		floodfill(x,y-2,old,newcolor);
	}
}
void mouse(int btn,int state ,int x, int y)
{
	y=800-y;
	if(btn==CLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		floodfill(x,y,old,newcolor);
		
	}
}

int main(int a,char ** b)
{
	glutInit(&a,b);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("flood fill");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
    	

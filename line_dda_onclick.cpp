/*
	TITLE : DDA LINE DRAWING ALGORITHM
	AUTHOR : SOORYA N KUMAR
	ROLL NO : 268
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

int xLine[100], yLine[100], pointsDrawn = 0, slope=2;

void dda(int x1, int y1, int x2, int y2, int slope)
{
	glColor3f(0.0, 0.0, 0.0);
     	glPointSize(2.0);
   
     	float steps, dx = x2 - x1, dy = y2 - y1;

     	if (abs(dx) > abs(dy)) 
     	{
        	steps = abs(dx);
     	}
     	else 
     	{	
         	steps = abs(dy);
     	}

     	float xInc = (float)dx / (float)steps;
     	float yInc = (float)dy / (float)steps;
     	float x,y;
		x = x1, y = y1;

     	glBegin(GL_POINTS);
     	for (int i = 0; i < steps; i++)
     	{	
        	glVertex2i(x, y);
          	x = x + xInc;
          	y = y + yInc;
     	}
     	glEnd();
     	glFlush();
}

void drawLine()
{
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		dda(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope);
	}
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)     
	{
		xLine[pointsDrawn] = x;
		yLine[pointsDrawn++] = 500 - y;
	}
	drawLine();
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("DDA Line Drawing Algorithm");	
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(0.000, 0.749, 1.000, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(drawLine);
	glutMainLoop();
	return 0;
}
/*END OF THE PROGRAM*/

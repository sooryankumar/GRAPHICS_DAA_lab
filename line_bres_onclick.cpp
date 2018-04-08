/*
	TITLE   : BRESSENHAM'S ALGORITHM
 	AUTHOR  : SOORYA N KUMAR
  	ROLL NO : 268

	Input : Coordinates of end-points of lines given by mouse click
*/

#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>

using namespace std;

int xLine[100], yLine[100], pointsDrawn = 0, slope;

int sign(int x)                         //to determine the sign, used in bressenham's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void setPixelLine(float x, float y)                      //function to plot the points obtained from bressenham's algorithm
{
  	glColor3f(0.0, 0.0, 0.0 );
	glPointSize(2.0);
  	glBegin(GL_POINTS);
  		glVertex2f(x,y);
  	glEnd();
}

void bressenham(int x2, int y2, int x3, int y3, int slope)   //Bressenham's line drawing algorithm
{
	int dx, dy, dx2, dy2, x, y, s1, s2, p;
	if(slope == 2)                                       //if slope is negative, exchange x and y for both endpoints
	{
		int temp = x2;
		x2 = y2;
		y2 = temp;
		temp = x3;
		x3 = y3;
		y3 = temp; 
	}
	dx = abs(x3 - x2);
	dx2 = 2 * dx;
	dy = abs(y3 - y2);
	dy2 = 2 * dy;
	s1 = sign(x3 - x2);               //s1 and s2 denote the sign of dx and dy respectively                
	s2 = sign(y3 - y2);	
	if(dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;	
	}
	p = dy2 - dx;
	x = x2;
	y = y2;
	for(int i = 0; i <= dx; i++)
	{
		if( slope == 1)
			setPixelLine(x, y);
		else
			setPixelLine(y, x);
		x = x + s1;
		if(p >= 0)
		{
			y = y + s2;
			p = p + 2 * (dy - dx);
		}
		else
			p = p + dy2;
	}
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
		bressenham(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope);
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
	glutCreateWindow("Bressenham's Line Drawing Algorithm");	
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

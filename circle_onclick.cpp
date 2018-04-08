/*
	TITLE   : MID-POINT CIRCLE DRAWING ALGORITHM
 	AUTHOR  : SOORYA N KUMAR
  	ROLL NO : 268

	Input : Midpoint of circle given by mouse click
*/

#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>

using namespace std;

int xc[100], yc[100], nodesDrawn=0, radius=30, color[3];

void circlePlotPoints( int x, int y )                      //Plots the circle points obtained from the mid-point algorithm
{
	glPointSize( 1.0 );
	for ( int i = 0; i < nodesDrawn; i++ )
	{
		if ( color[i] == 0 )
			glColor3f(1.0, 0.0, 0.0);               //assigns rgb values to the color array
		else if ( color[i] == 2 )
			glColor3f( 0, 1, 0 );
		glBegin(GL_LINES);
			glVertex2i(xc[i] + x, yc[i] + y );
			glVertex2i((xc[i] + x), (-y + yc[i] ));
		glEnd();
	}
}

void midPointCircle()
{
	float p, x, y;
	p = 1 - radius;                          // p is the decision parameter
	x = 0;
	y = radius;
	circlePlotPoints(x, y); 
	circlePlotPoints(-x, y);
	circlePlotPoints(-y, x);
	circlePlotPoints(y, x);                 //plots the points (x, y)
	while(x <= y)
	{	
		x = x + 1;
		if(p < 0)
		{
			p = p + 2*x + 1;
		}
		else
		{
			y = y - 1;
			p = p + 2*x + 1 - 2*y;
		}
		circlePlotPoints(x, y);
		circlePlotPoints(-x, y);
		circlePlotPoints(-y, x);
		circlePlotPoints(y, x);
		glFlush();
	}
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)     
	{
		xc[nodesDrawn] = x;                     //draw another node
		yc[nodesDrawn] = 500 - y;
		nodesDrawn++;
	}
	midPointCircle();
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Mid-Point Circle Drawing Algorithm");	
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(0.000, 0.749, 1.000, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(midPointCircle);
	glutMainLoop();
	return 0;
}

/*
	TITLE : BRESSENHAM LINE DRAWING ALGORITHM
	AUTHOR : SOORYA N KUMAR
	ROLL NO : 268
*/

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

int x1=10, y1=10, x2=100, y2=200;

void draw_pixel(int x, int y) 
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) 
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) 
		dx = -dx;
	if (dy < 0) 
		dy = -dy;

	incx = 1;
	if (x2 < x1) 
		incx = -1;
	incy = 1;
	if (y2 < y1) 
		incy = -1;

	x = x1; y = y1;

	if (dx > dy) 
	{
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2 * (dy-dx);
		inc2 = 2 * dy;
		for (i=0; i<dx; i++) 
		{
			if (e >= 0) 
			{
				y = y + incy;
				e = e + inc1;
			}
			else
				e = e + inc2;
			x = x + incx;
			draw_pixel(x, y);
		}

	} 
	else 
	{
		draw_pixel(x, y);
		e = 2 * dx-dy;
		inc1 = 2 * (dx-dy);
		inc2 = 2 * dx;
		for (i=0; i<dy; i++) 
		{
			if (e >= 0) 
			{
				x = x + incx;
				e = e + inc1;
			}
			else
				e = e + inc2;
			y = y + incy;
			draw_pixel(x, y);
		}
	}
}

void Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	draw_line(x1, x2, y1, y2);
	glFlush();
}

int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
/*END OF THE PROGRAM*/

/*
	TITLE   : LINE CLIPPING ALGORITHM
	AUTHOR  : SOORYA N KUMAR
  	ROLL NO : 268
*/

#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

const int x_max = 400;
const int y_max = 400;
const int x_min = 100;
const int y_min = 100;


int xc[100], yc[100],xLine[100], yLine[100], mouseX, mouseY, mouseLX, mouseLY, slope = 2, color[3], parent[10];
int lineCount = 0, linesDrawn = 0, pointsDrawn = 0, nodeCount;

int sign(int x)                         //to determine the sign, used in bressenham's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void setPixelLine(float x, float y)                      //function to plot the points obtained from bressenham's algorithm
{
  	glColor3f(0.0, 0.0, 0.0 );
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
	for(int i = 1; i <= dx; i++)
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
	glClear(GL_COLOR_BUFFER_BIT);
	bressenham( x_min, y_min, x_max, y_min, 1 );
  	bressenham( x_max, y_min, x_max, y_max, 2 );
  	bressenham( x_min, y_max, x_max, y_max, 1 );
  	bressenham( x_min, y_max, x_min, y_min, 2 );
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		bressenham(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope);
	}
}

void regionCode(int x1, int y1, int x2, int y2, int bit1[], int bit2[])
{
	if(x1 < x_min)
		bit1[3] = 1;
	if(x2 < x_min)
		bit2[3] = 1;
	if(x1 > x_max)
		bit1[2] = 1;
	if(x2 > x_max)
		bit2[2] = 1;
	if(y1 < y_min)
		bit1[1] = 1;
	if(y2 < y_min)
		bit2[1] = 1;
	if(y1 > y_max)
		bit1[0] = 1;
	if(y2 > y_max)
		bit2[0] = 1;
}

int checkOutside(int bit1[], int bit2[])
{
	for(int i = 0; i < 4; i++)
	{
		if(bit1[i] & bit2[i] == 1)	
			return 0;
	}
	return 1;
}

int checkInside(int bit1[], int bit2[])
{
	for(int i = 0; i < 4; i++)
	{
		if(bit1[i] | bit2[i] == 1)
			return 0;
	}
	return 1;
}

void leftClip(int bit1[], int i, int bit2[])
{
	if(bit1[3] == 1)
	{
		yLine[i] = ((float)(x_min - xLine[i])/(float)(xLine[i+1] - xLine[i])) * (yLine[i+1] - yLine[i]) + yLine[i];
		xLine[i] = x_min;
	}
	if(bit2[3] == 1)
	{
		yLine[i+1] = ((float)(x_min - xLine[i])/(float)(xLine[i+1] - xLine[i])) * (yLine[i+1] - yLine[i]) + yLine[i];
		xLine[i+1] = x_min;
	}
}

void rightClip(int bit1[], int i, int bit2[])
{
	if(bit1[2] == 1)
	{
		yLine[i] = ((float)(x_max - xLine[i])/(float)(xLine[i+1] - xLine[i])) * (yLine[i+1] - yLine[i]) + yLine[i];
		xLine[i] = x_max;
	}
	if(bit2[2] == 1)
	{
		yLine[i+1] = ((float)(x_max - xLine[i])/(float)(xLine[i+1] - xLine[i])) * (yLine[i+1] - yLine[i]) + yLine[i];
		xLine[i+1] = x_max;
	}
}

void bottomClip(int bit1[], int i, int bit2[])
{
	if(bit1[1] == 1)
	{
		xLine[i] = ((float)(y_min - yLine[i])/(float)(yLine[i+1] - yLine[i])) * (xLine[i+1] - xLine[i]) + xLine[i];
		yLine[i] = y_min;
	}
	if(bit2[1] == 1)
	{
		xLine[i+1] = ((float)(y_min - yLine[i])/(float)(yLine[i+1] - yLine[i])) * (xLine[i+1] - xLine[i]) + xLine[i]; 
		yLine[i+1] = y_min;
	}
}

void topClip(int bit1[], int i, int bit2[])
{
	if(bit1[0] == 1)
	{
		xLine[i] = ((float)(y_max - yLine[i])/(float)(yLine[i+1] - yLine[i])) * (xLine[i+1] - xLine[i]) + xLine[i];
		yLine[i] = y_max;
	}
	if(bit2[0] == 1)
	{
		xLine[i+1] = ((float)(y_max - yLine[i])/(float)(yLine[i+1] - yLine[i])) * (xLine[i+1] - xLine[i]) + xLine[i]; 
		yLine[i+1] = y_max;
	}
}

void lineClip(int bit1[], int i, int bit2[])
{
	leftClip(bit1, i, bit2);
	rightClip(bit1, i, bit2);
	bottomClip(bit1, i, bit2);
	topClip(bit1, i, bit2);
} 

void clip()
{
	for(int i = 0; i < pointsDrawn; i+=2)
	{
		int bit1[4] = {0}, bit2[4] = {0};
		regionCode(xLine[i], yLine[i], xLine[i+1], yLine[i+1], bit1, bit2);		
		if(checkOutside(bit1, bit2))
		{
			cout << "Line is not completely Outside.\n";
			int r = checkInside(bit1, bit2);
			if(r == 1)
			{
				cout << "Line is completely Inside\n";
				continue;
			}
			else
				lineClip(bit1, i, bit2);
		}
		else
		{
			xLine[i+1] = xLine[i];
			yLine[i+1] = yLine[i];
			cout << "Line is completely Outside.\n";
		}
		drawLine();
		regionCode(xLine[i], yLine[i], xLine[i+1], yLine[i+1], bit1, bit2);
	}
}

void mouse(int button, int state, int x, int y)
{	
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)              //if a left-click occured
	{
		xLine[pointsDrawn] = mouseLX = x;
		yLine[pointsDrawn] = mouseLY = 500 - y;
		pointsDrawn++;
	}
	drawLine();
}

void keyboardPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case  'c' : clip();                            //if 'c' character id pressed, then start line clipping
			break;
		default : cout <<"Invalid Key!!!"<< endl;
	}
}
 
void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Line Clipping Algorithm");
	glClear(GL_COLOR_BUFFER_BIT);	
	glClearColor(0.000, 0.749, 1.000, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(drawLine);
	glutMainLoop();
	return 0;
}
/*END OF THE PROGRAM*/

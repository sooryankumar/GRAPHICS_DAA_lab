#include<stdio.h>
#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>

using namespace std;

int xc[100], yc[100], xl[100], yl[100], sizec = 0, sizel = 0, radius = 20, mouseCX, mouseCY, mouseLX, mouseLY;
int flag = 1, nodeCount;

int sign(int x)
{
	return( (x>0) ? 1 : ( (x<0) ? -1 : 0) );
}

void setPixelCircle(float x, float y) 
{
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	for ( int i = 0; i < sizec; i++ )
	{
		glBegin(GL_POINTS);
			glVertex2f(x + xc[i], y + yc[i]);
		glEnd();
	}  
}

void setPixelLine(float x, float y) 
{
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
  	glBegin(GL_POINTS);
  		glVertex2f(x,y);
  	glEnd();
}

void midptCircle()
{
	float p = (5/4) - radius;
	float x = 0, y = radius;
	while ( x <= y )
	{
		x += 0.1;
		if ( p < 0 )
		{
			
			p += 2*x + 1;
		}
		else
		{
			y -= 0.1;
			p += 2*x + 1 - 2*y;
		}
		glColor3f( 0, 1, 1 );
		setPixelCircle( x, y );
		setPixelCircle( x, -y );
		setPixelCircle( -x, y );
		setPixelCircle( -x, -y );
		setPixelCircle( y, x );
		setPixelCircle( y, -x );
		setPixelCircle( -y, x );
		setPixelCircle( -y, -x );
		glFlush();
	}
}

void bres_general(int x1, int y0, int x2, int y2, int flag)
{
	int dx, dy, x, y, p, s1, s2, dx2, dy2, dxdy2, temp;
  	if ( flag == 1 )
  	{
  		temp = x1;
  		x1 = y0;
  		y0 = temp;
  		temp = x2;
  		x2 = y2;
  		y2 = temp;
  	}
  
  	dx = abs(x2 - x1);
  	dx2 = 2 * dx;
  	dy = abs(y2 - y0);
  	dy2 = 2 * dy;
  	dxdy2 = 2 * ( dy - dx );
  	s1 = sign(x2-x1);
  	s2 = sign(y2-y0);

  	if(dy > dx)
  	{
  		temp = dx; 
  		dx = dy; 
  		dy = temp; 
  	}

  	p = dy2 - dx;
  	x = x1;
  	y = y0;
  	int i;
  	for(i = 1; i <= dx; i++)
  	{
    		if ( flag == 0 )
	    		setPixelLine(x,y);
    		else
    	 		setPixelLine(y,x);
    		x = x + s1;

    		if( p >= 0 ) 
    		{
      			y = y + s2;
      			p = p + dxdy2;
    		}
    		else
	    		p = p + dy2;
  	}
  	glFlush();
}

void draw(void)
{  
	glClear(GL_COLOR_BUFFER_BIT);
	midptCircle();
  	for ( int i = 0; i+1 < sizel && sizel > 1  ; i += 2 )
  	{
  		if ( abs(xl[i+1]-xl[i]) > abs(yl[i+1]-yl[i]) )
			flag = 0;
		else
			flag = 1;
  		bres_general(xl[i],yl[i],xl[i+1],yl[i+1],flag);
  	}
}

void mouse( int key, int state, int x, int y )
{
	if ( state == GLUT_DOWN && key == GLUT_LEFT )
	{
		if ( sizec < nodeCount )
		{
			xc[sizec]  = mouseCX = x;
			yc[sizec++] = mouseCY = 480 - y;
		}
	}
	if ( state == GLUT_DOWN && key == GLUT_RIGHT_BUTTON )
	{
		int i =0;
		for ( i = 0; i < sizec; i++ )
		{
			if ( ((pow( (x - xc[i]), 2 ) + pow( ((480-y) - yc[i]), 2 )) - pow( radius, 2 )) < 0 )
			{
			
				break;
			}
		}
		
		if ( i != sizec )
		{
			xl[sizel] = mouseLX = x;
			yl[sizel++] = mouseLY = 480 - y;
		}
	}
	//initAdjMat();
	draw();
}

void init() 
{  
  	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  	glutInitWindowPosition(0,0);
  	glutInitWindowSize(640, 480);
  	glutCreateWindow("Bressenham-Line Drawing");
  	glClearColor(0.941, 0.502, 0.5020,0.0);
  	glColor3f(1.0,1.0,1.0);
  	gluOrtho2D(0,640,0,480);
}

int main(int argc, char *argv[]) 
{
	cout<<"Enter the node Count : ";
	cin>>nodeCount;
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}



#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

int x2 = 35, y2 = 150, radius = 10, m = 1, x4, y4, count = 0, xc[100], yc[100], flag = 0;

void drawRightLeg()
{
	int x, y, x3, y3;
	x = x2;
	y = y2 - 25;

	x3 = x + 7;
	y3 = y - 15;
	
	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x3, y3);
	glEnd();
	glFlush();
}

void drawLeftLeg()
{
	int x, y, x3, y3;
	x = x2;
	y = y2 - 25;

	x3 = x - 7;
	y3 = y - 15;

	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x3, y3);
	glEnd();
	glFlush();
}

void drawRightArm()
{
	int x, y, x3, y3;
	x = x2;
	y = y2 - radius;
	
	x3 = x + 7;
	y3 = y - 10;

	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x3, y3);
	glEnd();
	glFlush();
}

void drawLeftArm()
{
	int x, y, x3, y3;
	x = x2;
	y = y2 - radius;
	
	x3 = x - 7;
	y3 = y - 10;
	
	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x3, y3);
	glEnd();
	glFlush();
}

void drawBody()
{
	int x, y;
	x = x2;
	y = y2 - radius;
	y4 = y2 - 25;
	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x, y4);
	glEnd();
	glFlush();
}

void circlePlotPoints(int x, int y, int cir)
{
	glPointSize(1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
		glVertex2i(xc[cir] + x, yc[cir] + y);
		glVertex2i(xc[cir] + x, (-y + yc[cir]));
	glEnd();
	glFlush();
}

void drawCircle(int cir)
{
	if(cir == 0)
	{
		xc[0] = x2;
		yc[0] = y2;
	}
	else
	{
		xc[1] = x4;
		yc[1] = y4;
	}
	float p, x, y;
	p = 1 - radius;
	x = 0;
	y = radius;
	if(cir == 0)
	{
		circlePlotPoints(x, y, cir);
		circlePlotPoints(-x, y, cir);
		circlePlotPoints(-y, x, cir);
		circlePlotPoints(y, x, cir);
	}
	else
	{
		circlePlotPoints(x, y, 1);
		circlePlotPoints(-x, y, 1);
		circlePlotPoints(-y, x, 1);
		circlePlotPoints(y, x, 1);
	}
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
		if(cir == 0)
		{
			circlePlotPoints(x, y, cir);
			circlePlotPoints(-x, y, cir);
			circlePlotPoints(-y, x, cir);
			circlePlotPoints(y, x, cir);
		}
		else
		{
			circlePlotPoints(x, y, 1);
			circlePlotPoints(-x, y, 1);
			circlePlotPoints(-y, x, 1);
			circlePlotPoints(y, x, 1);
		}
		glFlush();
	}
}

void drawBalloon(int k)
{
	int x, y;
	if(k == 0)
	{
		x4 = 550;
		y4 = 240;
		x = x4;
		y = y4 - radius;
		glColor3f(1.0, 1.0, 1.0);
		drawCircle(1);
		glBegin(GL_LINES);
			glVertex2i(x, y);
			glVertex2i(x, y - 40);
		glEnd();
	}
	glFlush();
}

void moveBalloon()
{
	int x, y;
	if(x4 < 600)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		x4 += 5;
	}
	x4 = 610;
	y4 = 240;
	x = x4;
	y = y4 - radius;
	glColor3f(1.0, 1.0, 1.0);
	drawCircle(1);
	glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x, y - 40);
	glEnd();
	glFlush();
}

void draw()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex2i(0, 110);
		glVertex2i(350, 110);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(350, 110);
		glVertex2i(500, 175);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(500, 175);
		glVertex2i(600, 175);
	glEnd();

	glFlush();
}

void drawMan()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	drawCircle(0);
	drawBody();
	drawLeftArm();
	drawRightArm();
	drawLeftLeg();
	drawRightLeg();
	if(flag == 0)
		drawBalloon(0);
	glFlush();
}

void forward()
{
	while(x2 < 350)
	{
		x2 += 3;
		drawMan();
		glFlush();
	}
	int y5;
	while(x2 < 500)
	{
		x2 += 10;
		y5 = y2 - 40;
		if(y5 < 175)
		{
			y2 += 5;
			drawMan();
		}
		else
		{
			y2 = 175 + 40;
			drawMan();
		}
		glFlush();
	}
	while(x2 < 540)
	{
		drawBalloon(0);
		x2 += 1;
		drawMan();
		sleep(0.5);
		glFlush();
	}
	
	while(x2 < 600)
	{
		x2 += 3;
		flag = 1;
		moveBalloon();
		drawMan();
		glFlush();
	}
	while(y4 < 2000){
		sleep(0.8);
		moveBalloon();
	}
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && state == GLUT_LEFT_BUTTON)
	{
		forward();
		glFlush();
	}
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Animation");
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 800, 0, 300);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	//glutKeyboardFunc(keyboardPress);
	glutDisplayFunc(draw);
	drawMan();
	drawBalloon(0);
	glutMainLoop();
	return 0;
}

#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>

void Display(void)
{
	glClearColor(1.0,0.7,0.2,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	{
		glColor3f(0.3,0.3,0.0);
		glVertex2f(50,50);
		glVertex2f(300,50);
		glVertex2f(300,300);
		glVertex2f(50,300);
	}
	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Square");
	gluOrtho2D(0,500,0,500);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}

#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>

void Display(void)
{
	glClearColor(1.0,0.7,0.2,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Window");
	gluOrtho2D(0,100,0,100);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}

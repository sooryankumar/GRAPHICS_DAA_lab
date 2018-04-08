#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>

using namespace std;

void Display(void)
{
	glClearColor(0.000, 0.749, 1.000,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	cout<<"Press t for Translation\n";
	cout<<"Press r for Rotation\n";
	cout<<"Press s for Scaling\n";
	
	glColor3f(1,0.5,0.5);
	glPointSize(2.0);
	glBegin(GL_QUADS);
	{
		glColor3f(0.5,0,0);
		glVertex2f(10,10);
		glVertex2f(10,55);
		glVertex2f(55,55);
		glVertex2f(55,10);
	}
	glEnd();
	glFlush();
	
}

void translate()
{
	glTranslatef(10,10,0);
	glBegin(GL_QUADS);
	{
		glColor3f(0.0,0.7,0.0);
		glVertex2f(10,10);
		glVertex2f(10,55);
		glVertex2f(55,55);
		glVertex2f(55,10);
	}
	glEnd();
	glFlush();
}

void rotate()
{
	glRotatef (90, 0.0f, 0.0f, 0.1f);
	glBegin(GL_QUADS);
	{
		glColor3f(0.0,0.0,0.7);
		glVertex2f(10,10);
		glVertex2f(10,55);
		glVertex2f(55,55);
		glVertex2f(55,10);
	}
	glEnd();
	glFlush();
	
}

void scale()
{
	glScalef(1, 1.5, 1);
	glBegin(GL_QUADS);
	{
		glColor3f(0.0,0.0,0.7);
		glVertex2f(10,10);
		glVertex2f(10,55);
		glVertex2f(55,55);
		glVertex2f(55,10);
	}
	glEnd();
	glFlush();
}

void keyboardPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 't' : translate();         //if 't' character id pressed, then translation operation is called
			break;
		case 'r' : rotate();		//if 'r' character id pressed, then rotation operation is called
			break;
		case 's' : scale();		//if 's' character id pressed, then scaling operation is called
			break;
		default : cout << "Invalid Key !!!" << endl;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,500);
	glutInitWindowPosition(400,50);
	glutCreateWindow("2-D Transformations");
	gluOrtho2D(0,100,0,100);
	glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}

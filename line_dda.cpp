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

void line()
{
     glColor3f(0.0, 0.0, 0.0);
     glPointSize(2.0);
     int x1=10, y1=10, x2=100, y2=100;
     int steps, dx = x2 - x1, dy = y2 - y1;

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
     float x = x1, y = y1;

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
int main(int argc, char ** argv) 
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(500, 500);
     glutInitWindowPosition(100, 100);
     glutCreateWindow("DDA Line Drawing Algorithm");
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT);
     gluOrtho2D(0, 500, 0, 500);
     glMatrixMode(GL_PROJECTION);  
     glutDisplayFunc(line);
     glutMainLoop();
     return 0;
}
/*END OF THE PROGRAM*/

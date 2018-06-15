#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>

using namespace std;

int xLine[100],yLine[100],xc[100],yc[100],adjMatrix[20][20],points=0,nodes=0,x,y,slope=2,radius=20,nodeCount,row,col,startNode,color[3],queue[10],parent[10],distanceNode[10],front=-1,rear=-1,intialTime[10],finalTime[10],k=0,time1;

void dda(int x1,int y1, int x2, int y2, int slope)
{
	float steps,dx=x2-x1,dy=y2-y1,xInc,yInc,x,y;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	xInc=(float)dx/(float)steps;
	yInc=(float)dy/(float)steps;
	x=x1;
	y=y1;
	glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for(int i=0;i<steps;i++)
	{
		glVertex2i(x,y);
		x=x+xInc;
		y=y+yInc;
	}
	glEnd();
	glFlush();
}

void circlePlotPoints(int x,int y)
{
	glPointSize(2.0);
	for(int i=0;i<nodes;i++)
	{
		if(color[i]==0)
			glColor3f(0.0,0.0,0.0);
		else if(color[i]==1)
			glColor3f(0.5,0.5,0.5);
		else if(color[i]==2)
			glColor3f(1.0,0.5,0.0);
		glBegin(GL_LINES);
			glVertex2i(xc[i]+x,yc[i]+y);
			glVertex2i(xc[i]+x,-y+yc[i]);
		glEnd();
	}
}

void circle()
{
	float p,x,y;	
	p=1-radius;
	x=0;
	y=radius;
	circlePlotPoints(x,y);
	circlePlotPoints(-x,y);
	circlePlotPoints(-y,x);
	circlePlotPoints(y,x);
	while(x<=y)
	{
		x=x+1;
		if(p<0)
			p=p+2*x+1;
		else
		{
			y=y-1;
			p=p+2*x+1-2*y;
		}
		circlePlotPoints(x,y);
		circlePlotPoints(-x,y);
		circlePlotPoints(-y,x);
		circlePlotPoints(y,x);
	}
	glFlush();
}

void printAdjMatrix()
{
	adjMatrix[row][col]=1;
	adjMatrix[col][row]=1;
}

void drawCircleLine()
{
	for(int i=0;i+1<points&&points>1;i=i+2)
	{
		if(abs(xLine[i+1]-xLine[i])>abs(yLine[i+1]-yLine[i]))
			slope=1;
		else
			slope=2;
		if(points%2==0)
			printAdjMatrix();
		dda(xLine[i],yLine[i],xLine[i+1],yLine[i+1],slope);
	}
	circle();
}

void drawCharacter(int x,int y, char ch)
{
	glColor3f(0.8,0.0,0.0);
	glRasterPos2i(x,y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,ch);
}

void drawString(int x,int y,char *str)
{
	glColor3f(0.8,0.0,0.0);
	glRasterPos2i(x,y);
	for(str;*str!='\0';str++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*str);
}

void dfs_visit(int u)
{
	char ch[5];
	time1=time1+1;
	intialTime[u]=time1;
	color[u]=1;
	sprintf(ch,"%d",intialTime[u]);
	drawString(xc[u]-3,yc[u]+30,ch);
	cout<<u<<" ";
	for(int v=0;v<nodeCount;v++)
	{
		if(adjMatrix[u][v]==1 && color[v]==0)
		{
			parent[v]=u;
			dfs_visit(v);
		}
		sleep(1.0);
		drawCircleLine();
	}
	color[u]=2;
	time1=time1+1;
	finalTime[u]=time1;
	sprintf(ch,"%d",finalTime[u]);
	drawString(xc[u]-3,yc[u]-35,ch);
}

void dfs()
{
	int arr[10];
	for(int i=0;i<nodeCount;i++)
	{
		parent[i]=NULL;
		color[i]=0;
	}
	time1=0;
	for(int i=0;i<nodeCount;i++)
	{
		if(color[i]==0)
		{
			dfs_visit(i);
			arr[k++]=i;
		}
	}
	cout<<"Starting and Finishing Time:\n";
	for(int i=0;i<nodeCount;i++)
		cout<<i<<"->"<<intialTime[i]<<"/"<<finalTime[i]<<"\n";
		cout<<"DFS Finished!!!\n";
}	

void keyboard(unsigned char key, int x,int y)
{
	switch(key)
	{
		case 'd':dfs();
			break;
		default:cout<<"Invalid Choice\n";
	}
}

void mouse(int button,int state, int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(nodes<nodeCount)
		{
			xc[nodes]=x;
			yc[nodes]=500-y;
			nodes++;
		}
		else
		{
			cout<<"Adjacency Matrix\n";
			for(int i=0;i<nodeCount;i++)
			{
				for(int j=0;j<nodeCount;j++)
					cout<<adjMatrix[i][j]<<" ";
				cout<<endl;			
			}
		}
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		int i;
		for(i=0;i<nodes;i++)
		{
			int circleParam=((pow(x-xc[i],2) + (pow(500-y-yc[i],2)-(pow(radius,2)))));
			if(circleParam<0)
			{
				if(points%2==0)
					row=i;
				else
					col=i;
				break;
			}
		}
		if(i!=nodes)
		{	 					  				xLine[points]=xc[i];
			yLine[points]=yc[i];
			points++;
		}
	}
	drawCircleLine();
}

void initGraph()
{
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			adjMatrix[i][j]=0;
	for(int i=0;i<10;i++)
	{
		intialTime[i]=0;
		finalTime[i]=0;
	}
}

int main(int argc, char **argv)
{
	cout<<"Enter the no. of nodes:\n";
	cin>>nodeCount;
	initGraph();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("DFS");
	glClearColor(0.000,0.749,1.000,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}

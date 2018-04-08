/*
	TITLE   : DIJKSTRA'S ALGORITHM
  	AUTHOR  : SOORYA N KUMAR
  	ROLL NO : 268

 	Input : No. of nodes and the start node
*/

#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>

using namespace std;

int xc[100], yc[100],xLine[100], yLine[100], nodesDrawn = 0, pointsDrawn = 0, radius = 25, mouseX, mouseY, mouseLX, mouseLY, row, col, edgeCount=0, weight;
int slope = 2, nodeCount, arr[10],flag = 0, arr1[10];
int adjMatrix[10][10], startNode, queue[10], front = -1, rear = -1, color[3], parent[10], distanceNode[10], v1, v2, adjmat[10][10];
bool wait = false;

int sign(int x)                                           //to determine the sign, used in bressenham's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void setPixelLine(float x, float y, int col)                      //function to plot the points obtained from bressenham's algorithm
{ 	
	glPointSize(1.5);
	if(col == 0)	
		glColor3f(1.0, 0.0, 0.0 );
	else
		glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void circlePlotPoints( int x, int y )                      //Plots the circle points obtained from the mid-point algorithm
{
	glPointSize( 1.5 );
	for ( int i = 0; i < nodesDrawn; i++ )
	{
		if ( color[i] == 0 )
			glColor3f(0.0, 0.0, 0.0);               //assigns rgb values to the color array
		else if ( color[i] == 2 )
			glColor3f( 0.0, 1.0, 0.0 );
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

void drawString(int x, int y, char *str)
{
	glColor3f(0.8, 0.0, 0.0);
	glRasterPos2i(x, y);
	for( str; *str != '\0'; str++ )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *str);
}


void printAdjMatrix()
{
	adjMatrix[row][col] = weight;
	adjMatrix[col][row] = weight;			            
}

void bressenham(int x2, int y2, int x3, int y3, int slope, int col)   //Bressenham's line drawing algorithm
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
	for(int i = 0; i <= dx; i++)
	{
		if( slope == 1)
			setPixelLine(x, y, col);
		else
			setPixelLine(y, x, col);
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

void getWeight()
{
	if(wait == true)
	{
		cout << "\nEnter the weight : ";
		cin >> weight;	
		wait = false;
	}
}

void drawCircleLine()
{
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		if(pointsDrawn % 2 == 0)
		{                      		// to determine the number of times clicked to draw an edge
			printAdjMatrix();
		}	
		bressenham(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope, 0);
	}
	midPointCircle();
}

int sort(int arr[10])
{
	int min, node;
	min = 9999;
	for(int i = 0; i < nodeCount; i++)
	{
		if(arr[i] == 0)
			continue;
		else if(arr[i] < min )
		{
			min = arr[i];
			node = i;                   //return the number of node with min weight
		}		
	}
	return node;
}

void relax(int u, int v, int weight)
{
	if(distanceNode[v] > (distanceNode[u] + weight))
	{
		distanceNode[v] = distanceNode[u] + weight;
		parent[v] = u;
	}
} 

void drawEdge(int nodei, int nodej)
{
	color[nodei] = 2;
	color[nodej] = 2;	
	int slope;
	if(abs(xc[nodej] - xc[nodei]) > abs(yc[nodej] - yc[nodei]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
	bressenham(xc[nodei], yc[nodei], xc[nodej], yc[nodej], slope, 1);
}


void dijkstra(int startNode)
{	
	int x = 0, k = 0, isolatedNodes[10], q = 1;
	char ch[5];
	if(rear == -1)	
		rear = 0;
	else
		rear++;
	queue[rear] = startNode; 
	arr1[k++] = startNode; 
	int  r = 0, c = 0;
	for(int i = 0; i < nodeCount; i++)
	{
		for(int j = 0; j < nodeCount; j++)
		{
			if(adjMatrix[i][j] != 0)
			{
				r = 1;
				break;
			}
			else
				c++;	
		}
		if(c < nodeCount)
			continue;
		else
		{
			isolatedNodes[q++] = i;
			break;
		}
	}
	q = q - 1;					//insert the startNode to the queue
	while(front <= rear)
	{
		front++;
		if(front == nodeCount - q)
			break;
		int u = queue[front];
		x++;
		for(int v = 0; v < nodeCount; v++)
		{
			if( x >= nodeCount - q)                                    //if x = nodeCount, all nodes have been traversed
				break;
			if(adjMatrix[u][v] > 0 && color[v] == 0)
			{
				relax(u, v, adjMatrix[u][v]);
				arr[v] = distanceNode[v];
			}
			sleep(0.5);
		}
		if( x >= nodeCount - q )
			break;
		int p = sort(arr);
		arr[p] = 0;                                        //the node has been traversed
		queue[++rear] = p;
		arr1[k++] = p;
		drawEdge(u, p);
		color[p] = 2;
		sprintf(ch, "%d", p);
		drawString(xc[p]-3, yc[p]-35, ch);
	}
	for(int i = 0; i < nodeCount - q ; i++)
		cout << arr1[i] << " ";
}


		
void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)              //if a left-click occured
	{
		if(nodesDrawn < nodeCount)                                //if the number of nodes already drawn is less than the max number of nodes
		{
			xc[nodesDrawn] = mouseX = x;                     //draw another node
			yc[nodesDrawn] = mouseY = 500 - y;
			nodesDrawn++;
		}
		else                                               //if the number of nodes already drawn is greater than the max number of nodes         
		{
			cout << endl;
			cout << "\nAdjacency Matrix : \n";
			for(int i = 0; i < nodeCount; i++)                //print the adjacency matrix
			{
				for(int j = 0; j < nodeCount; j++)
					cout << adjMatrix[i][j] << " ";
				cout << endl;
			}
		}
	}
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)                //if a right-click occured
	{
		int i = 0;
		for(i = 0; i < nodesDrawn; i++)
		{
			int circleParam = ((pow(x - xc[i], 2) + (pow(500 - y - yc[i], 2) - (pow(radius, 2)))));  //calculate the circle equation x2+y2-r2
			if(circleParam < 0)
			{
				if(pointsDrawn % 2 == 0)     //to determine the number of times click occured
					row = i;
				else
					col = i;
				break;
			}	
		}
		if(i != nodesDrawn)
		{
			xLine[pointsDrawn] = mouseLX = xc[i];
			yLine[pointsDrawn] = mouseLY = yc[i];
			pointsDrawn++;
		}
		if(pointsDrawn % 2 == 0)
		{
			wait = true;                       //if wait = true, then the click has occured twice and user inputs the weight
			getWeight();
		}
	}
	drawCircleLine();
}


void keyboardPress(unsigned char key, int x, int y)
{
	cout << "\nThe order of traversal is : \n";
	switch(key)
	{
		case  'd' :  dijkstra(startNode);                //if 'd' character id pressed, then start dijikstra
			break;
		default : cout << "\nUnknown Key " << endl;
	}
}
 
void initAdjMatrix()                                   //initialize adjacency matrix
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			adjMatrix[i][j] = 0;
		}
		arr1[i] = 0;
	}
		
}

void initializeSingleSource(int startNode )
{
	for( int i=0; i < nodeCount; i++ )                         
	{
		parent[i] = NULL;                       //for all nodes, assign the parent as NULL,
		color[i] = 0;                           //color as white
		distanceNode[i] = 9999;                 //and distance as maximum
	}
	sleep(0.1);
	color[startNode] = 2;                          //assign the color of startNode as grey
	distanceNode[startNode] = 0;                   //make its distance as 1
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Dijkstra's Algorithm");	
	glClearColor(0.000, 0.749, 1.000, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
	cout << "\nEnter the number of nodes : ";
	cin >> nodeCount;
	cout << "\nEnter the starting node : ";
	cin >> startNode;
	initAdjMatrix();
	initializeSingleSource(startNode);
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}

/*  ----------END OF PROGRAM------------ */

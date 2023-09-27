// Includes 
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <gl/glut.h>

int le[500], re[500], flag = 0, m;
void init()
{
	gluOrtho2D(0, 500, 0, 500);
}
void edge(int x0, int y0, int x1, int y1)
{
	if (y1 < y0)
	{
		int tmp;
		tmp = y1;
		y1 = y0;
		y0 = tmp;
		tmp = x1;
		x1 = x0;
		x0 = tmp;
	}
	int x = x0;
	m = (y1 - y0) / (x1 - x0);
	for (int i = y0; i < y1; i++)
	{
		if (x < le[i])
			le[i] = x;
		if (x > re[i])
			re[i] = x;
		x += (1 / m);
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);


	// Square Shape
	glVertex2f(200, 100);
	glVertex2f(100, 200);
	glVertex2f(200, 300);
	glVertex2f(300, 200);

	/*
	//top triangle
	glVertex2f(300, 300);
	glVertex2f(250, 400);
	glVertex2f(350, 400);
	//bottom triangle
	glVertex2f(300, 300);
	glVertex2f(250, 200);
	glVertex2f(350, 200);
	//left top triangle
	glVertex2f(300, 300);
	glVertex2f(100, 300);
	glVertex2f(200, 350);
	//left bottom triangle
	glVertex2f(300, 300);
	glVertex2f(100, 300);
	glVertex2f(200, 250);
	*/

	glEnd();
	for (int i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}

	// Square Edges

	edge(200, 100, 100, 200);
	edge(100, 200, 200, 300);
	edge(200, 300, 300, 200);
	edge(300, 200, 200, 100);


	// for the required shape
	/*
	edge(300, 300, 250, 400);
	edge(250, 400, 350, 400);
	edge(350, 400, 300, 300);

	edge(300, 300, 250, 200);
	edge(250, 200, 350, 200);
	edge(350, 200, 300, 300);

	edge(300, 300, 100, 300);
	edge(100, 300, 200, 350);
	edge(200, 350, 300, 300);

	edge(300, 300, 100, 300);
	edge(100, 300, 200, 250);
	edge(200, 250, 300, 300);
	*/

	if (flag == 1)
	{
		for (int i = 0; i < 500; i++)
		{
			if (le[i] < re[i])
			{
				for (int j = le[i]; j < re[i]; j++)
				{
					glColor3f(1, 0, 0);
					glBegin(GL_POINTS);
					glVertex2f(j, i);
					glEnd();

				}

			}
		}
	}
	glFlush();
}
void ScanMenu(int id) {
	if (id == 1)
		flag = 1;
	else if (id == 2)
		flag = 0;
	else
		exit(0);

	glutPostRedisplay();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("scan line");
	init();
	glutDisplayFunc(display);
	glutCreateMenu(ScanMenu);
	glutAddMenuEntry("scanfill", 1);
	glutAddMenuEntry("clear", 2);
	glutAddMenuEntry("exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
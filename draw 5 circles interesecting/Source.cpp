#include <Windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.142857142857143
#define windowWidth 500
#define windowHeight 500
#define windowPositionX 0
#define windowPositionY 0

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);    // Clear color and create a white Bg 
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                    // reset the projection matrix 
	//gluOrtho2D(-(windowWidth / 2), (windowWidth / 2), -(windowHeight / 2), (windowHeight / 2));
}

void myReshape(int width, int height) {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glLoadIdentity();
	if (width >= height) {
		// aspect > = 1, set the hight from -250 to 250, and set the width to be larger }
		gluOrtho2D(-(windowWidth / 2) * aspect, (windowWidth / 2) * aspect, -(windowHeight / 2), (windowHeight / 2));
	}
	else {
		// aspect < 1, set the width from -1 to 1, with larger hight
		gluOrtho2D(-(windowWidth / 2), (windowWidth / 2), -(windowHeight / 2) / aspect, (windowHeight / 2) / aspect);
	}
}

void drawShape(int originX, int originY, int radius, int NoOfPoints) {
	glBegin(GL_TRIANGLE_STRIP);
	float th_Rad, x, y, theta;
	for (theta = 0; theta <= NoOfPoints; theta++) {
		th_Rad = (theta * 2 * PI) / NoOfPoints;
		x = radius * cos(th_Rad) + originX;
		y = radius * sin(th_Rad) + originY;
		glVertex2f(x, y);
	}
	glEnd();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);          // Clear the screen, --> Clear the buffer 
	glColor3f(0.0, 0.0, 0.0);

	// Circle on the right
	drawShape(100, 0, 100, 3);
	// Circle on the left
	drawShape(-100, 0, 100, 3);

	// Circle on the right
	drawShape(100, 0, 20, 360);
	// Circle on the left
	drawShape(-100, 0, 20, 360);

	glFlush();

}

void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("5 Circles Intersecting");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Callbacks
	myInit();
	glutDisplayFunc(draw);
	glutReshapeFunc(myReshape);


	glutMainLoop();
}
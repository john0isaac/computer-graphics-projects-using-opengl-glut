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

void drawShape(float originX, float originY, int radius, int shiftTheta, GLenum mode) {
	glBegin(mode);
	float th_Rad, x, y, theta, shift;
	glVertex2i(originX, originY);
	for (theta = 0; theta <= 90; theta++) {
		th_Rad = (theta * PI) / 180;
		shift = (shiftTheta * PI) / 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2i(x, y);
	}
	glEnd();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);          // Clear the screen, --> Clear the buffer 

	glColor3f(0.0, 0.0, 0.0);
	// Big Circle
	drawShape(0, 0, 200, 0, GL_POLYGON);
	drawShape(0, 0, 200, 90, GL_POLYGON);
	drawShape(0, 0, 200, 180, GL_POLYGON);
	drawShape(0, 0, 200, 270, GL_POLYGON);
	
	// Blue
	glColor3f(0.24, 0.28, 0.8);
	drawShape(2.5, 2.5, 190, 0, GL_POLYGON);

	// Red
	glColor3f(0.53, 0.0, 0.08);
	drawShape(-2.5, 2.5, 190, 90, GL_POLYGON);

	// Yellow
	glColor3f(1.0, 0.78, 0.05);
	drawShape(-2.5, -2.5, 190, 180, GL_POLYGON);

	// Green
	glColor3f(0.13, 0.69, 0.29);
	drawShape(2.5, -2.5, 190, 270, GL_POLYGON);

	glFlush();

}

void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("Colored Circle");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Callbacks
	myInit();
	glutDisplayFunc(draw);
	glutReshapeFunc(myReshape);


	glutMainLoop();
}
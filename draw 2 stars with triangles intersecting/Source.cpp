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

void drawStar(int originX, int originY, int radius, int shiftTheta, int NoOfPoints, float dividor, GLenum mode) {
	glBegin(mode);
	float th_Rad, x, y, shift;
	for (int theta = 0; theta <= NoOfPoints; theta++) {
		th_Rad = (theta * 2 * PI) / NoOfPoints;
		shift = (shiftTheta * PI) / 180;
		if (theta % 2 != 0){
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2i(x, y);
		}
		else {
			x = (radius * cos(th_Rad + shift) / dividor) + originX;
			y = (radius * sin(th_Rad + shift) / dividor) + originY;
			glVertex2i(x, y);
		}
	}
	glEnd();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);          // Clear the screen, --> Clear the buffer 
	
	// Outer Star
	glColor3f(0.2, 0.5, 0.7);
	drawStar(0, 0, 250, 65, 14, 1.5, GL_LINE_LOOP);
	
	
	// Inner Star
	glColor3f(1.000, 0.871, 0.678);
	drawStar(0, 0, 150, 45, 8, 4, GL_POLYGON);
	// Outer Line of Inner Star
	glColor3f(0.2, 0.5, 0.7);
	drawStar(0, 0, 150, 45, 8, 4, GL_LINE_LOOP);

	
	glColor3f(1.0, 1.0, 1.0);
	drawStar(0, 0, 100, 60, 12, 1.5, GL_POLYGON);
	glColor3f(0.2, 0.5, 0.7);
	drawStar(0, 0, 100, 60, 12, 1.5, GL_LINE_LOOP);
	
	glFlush();

}

void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("2 Stars Intersecting");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Callbacks
	myInit();
	glutDisplayFunc(draw);
	glutReshapeFunc(myReshape);


	glutMainLoop();
}
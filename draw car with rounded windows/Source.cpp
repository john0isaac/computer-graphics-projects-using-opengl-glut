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

void drawQuarterCircle(float originX, float originY, float radius, int shiftTheta) {
	float th_Rad, x, y, theta, shift;
	for (theta = 0; theta <= 90; theta++) {
		th_Rad = (theta * PI) / 180;
		shift = (shiftTheta * PI) / 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2f(x, y);
	}
}

void drawRoundedWindow(float originX, float originY, int width, int height, int radius, GLenum mode) {
	glBegin(mode);
	// Top Left
	glVertex2i((originX - (width / 2)) + radius, (originY + (height / 2)));
	drawQuarterCircle((originX - (width / 2)) + radius, (originY + (height / 2)) - radius, radius, 90);
	// Left Top
	glVertex2i((originX - (width / 2)), (originY + (height / 2)) - radius);
	
	
	// Left Bottom
	glVertex2i((originX - (width / 2)), (originY - (height / 2)) + radius);
	drawQuarterCircle((originX - (width / 2)) + radius, (originY - (height / 2)) + radius, radius, 180);
	// Bottom Left
	glVertex2i((originX - (width / 2)) + radius, (originY - (height / 2)));


	// Bottom Right
	glVertex2i((originX + (width / 2)) - radius, (originY - (height / 2)));
	drawQuarterCircle((originX + (width / 2)) - radius, (originY - (height / 2)) + radius, radius, 270);
	// Right Bottom
	glVertex2i((originX + (width / 2)), (originY - (height / 2)) + radius);
	
	
	// Right Top
	glVertex2i((originX + (width / 2)), (originY + (height / 2)) - radius);
	drawQuarterCircle((originX + (width / 2)) - radius, (originY + (height / 2)) - radius, radius, 0);
	// Top Right
	glVertex2i((originX + (width / 2)) - radius, (originY + (height / 2)));
	glEnd();
}

void drawShape(int originX, int originY, int radius, int shiftTheta, int NoOfPoints, GLenum mode) {
	glBegin(mode);
	float th_Rad, x, y, theta, shift;
	for (theta = 0; theta <= NoOfPoints; theta++) {
		th_Rad = (theta * 2 * PI) / NoOfPoints;
		shift = (shiftTheta * PI) / 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2f(x, y);
	}
	glEnd();
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Middle Car Body Outter Line
	glColor3f(0.18, 0.32, 0.56);
	glRectf(-120, -50, 120, 90);
	// Middle Car Body Inner Fill
	glColor3f(0.26, 0.44, 0.76);
	glRectf(-118, -48, 118, 88);

	// Rear Car Part Outter Line
	glColor3f(0.18, 0.32, 0.56);
	glRectf(120, -50, 200, 30);
	// Rear Car Part Inner Fill
	glColor3f(0.26, 0.44, 0.76);
	glRectf(120, -48, 198, 28);

	// Front Car Part Outter Line
	glColor3f(0.18, 0.32, 0.56);
	glRectf(-200, -50, -120, 30);
	// Front Car Part Inner Fill
	glColor3f(0.26, 0.44, 0.76);
	glRectf(-198, -48, -120, 28);

	glColor3f(1.0, 1.0, 1.0);
	drawRoundedWindow(-60, 50, 100, 50, 8, GL_POLYGON);
	drawRoundedWindow(60, 50, 100, 50, 8, GL_POLYGON);

	// Black Tires
	glColor3f(0.0, 0.0, 0.0);
	drawShape(-60, -75, 25, 0, 360, GL_POLYGON);
	drawShape(60, -75, 25, 0, 360, GL_POLYGON);
	
	// Orange Circle Tires
	glColor3f(1.0, 0.5, 0.0);
	drawShape(-60, -75, 10, 0, 360, GL_POLYGON);
	drawShape(60, -75, 10, 0, 360, GL_POLYGON);


	// Front Lights
	// Inner Red Fill
	glColor3f(0.8, 0.0, 0.0);
	drawShape(-205, 10, 10, 0, 360, GL_POLYGON);
	// Outter Black Line
	glColor3f(0.0, 0.0, 0.0);
	drawShape(-205, 10, 10, 0, 360, GL_LINE_LOOP);
	// Inner Red Fill
	glColor3f(0.8, 0.0, 0.0);
	drawShape(-205, -20, 10, 0, 360, GL_POLYGON);
	// Outter Black Line
	glColor3f(0.0, 0.0, 0.0);
	drawShape(-205, -20, 10, 0, 360, GL_LINE_LOOP);
	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("Car with Rounded Windows"); // Create and open Window
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Callback Functions
	myInit();
	glutDisplayFunc(draw);
	glutReshapeFunc(myReshape);
	//Change place of drawing
	//void (*myReshape)(int, int);
	//glutReshapeFunc();


	/*
	// Only when using input from keyboard or mouse
	glutMouseFunc();
	glutKeyboardFunc();
	*/

	glutMainLoop();
}
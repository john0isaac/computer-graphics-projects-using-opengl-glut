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

/*
	PI = 3.14
	R = 3
	Originx = 5
	Originy = 3
	For th = 0 to 360:
		th_Rad = th * PI/180
		x = R * Cos(th_Rad) + Originx
		y = R * Sin(th_Rad) + Originy
		Plot(x,y)
**/
/*
	sin^2(theta) + cos^2(theta) = 1

	PI = 3.14
	Originx = 
	Originy = 
	NoOfPoints = 1000000
	shiftTheta = 45
	For i = 0 to NoOfPoints:
		theRad = i * 2 * PI / NoOfPoints
		shift = shiftTheta * PI/180
		x = R * Cos(theRad + shift) + Originx
		y = R * Sin(theRad + shift) + Originy
**/
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
	if (width >= height){
		// aspect > = 1, set the hight from -250 to 250, and set the width to be larger }
		gluOrtho2D(-(windowWidth / 2) * aspect, (windowWidth / 2) * aspect, -(windowHeight / 2), (windowHeight / 2));
	}
	else{
		// aspect < 1, set the width from -1 to 1, with larger hight
		gluOrtho2D(-(windowWidth / 2), (windowWidth / 2), -(windowHeight / 2) / aspect, (windowHeight / 2) / aspect);
	}
}



void drawQuarterCircle(int originX, int originY, int radius) {
	glBegin(GL_POLYGON);
	float th_Rad, x, y, theta, shift;
	int shiftTheta = 0;
	glVertex2i(45, 45);
	for (theta = 0; theta <= 90; theta++) {
		th_Rad = (theta * PI)/ 180;
		shift = (shiftTheta * PI) / 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2i(x,y);
	}
	glEnd();
}
void drawCircle2(int originX, int originY, int radius, int shiftTheta, int NoOfPoints) {
	glBegin(GL_POINTS);
	float th_Rad, x, y, theta, shift;
	for (theta = 0; theta <= NoOfPoints; theta++) {
		th_Rad = (theta * 2 * PI) / NoOfPoints;
		shift = (shiftTheta * PI)/ 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2i(x, y);
	}
	glEnd();
}

void drawShape(int originX, int originY, int radius, int shiftTheta, int NoOfPoints) {
	glBegin(GL_LINE_LOOP);
	float th_Rad, x, y, theta, shift;
	for (theta = 0; theta <= NoOfPoints; theta++) {
		th_Rad = (theta * 2 * PI) / NoOfPoints;
		shift = (shiftTheta * PI) / 180;
		x = radius * cos(th_Rad + shift) + originX;
		y = radius * sin(th_Rad + shift) + originY;
		glVertex2i(x, y);
	}
	glEnd();
}
void draw() {
	drawQuarterCircle(45, 45, 45);

	
	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("My first Window"); // Create and open Window
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
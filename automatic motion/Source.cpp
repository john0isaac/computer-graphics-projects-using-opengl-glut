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
float translationX = 0.0;
float translationY = 0.0;
float angle = 0.0;

void idle() {
	glutPostRedisplay();
}

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
	// cube
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.8, 0.4, 0.2);
	
	glPushMatrix(); // Add Transformation to Matrix
	glTranslatef(translationX, translationY, 0);
	glRotatef(angle, 0, 0, 1);
	drawShape(0, 0, 100, 45, 4);
	glPopMatrix(); // Remove Transformation from Matrix

	
	glFlush();
	angle += 0.02;
	if (translationX < (windowWidth/2)){
		translationX += 0.05;
	}
	else if (translationX >= (windowWidth / 2)) {
		translationX = windowWidth / 2;
		if (translationY < (windowHeight / 2))
		translationY += 0.05;
	}
	else if (translationX < (windowWidth / 2)){
		cout << "true";
		translationX -= 0.01;
	}

}

void main(int argc, char** argv) {
	glutInit(&argc, argv); //Initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Mode and Color
	glutInitWindowSize(windowWidth, windowHeight); // Window size Initializiton
	glutInitWindowPosition(windowPositionX, windowPositionY); // Window Position

	glutCreateWindow("Automatic Motion");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Callbacks
	myInit();
	glutDisplayFunc(draw);
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);


	glutMainLoop();
}
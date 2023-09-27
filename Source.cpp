// Includes 
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <gl/glut.h>
#include <math.h>
using namespace std;
// constants values 
#define PI 3.14159256535898
#define windowWidth 600
#define windowHeight 600
#define windowPositionX 0
#define windowPositionY 0
// Functions Decleration
void myInit();
void myDisplay();
void reshape(int, int);
void DrawShape(float canterX, float canterY, float radius, float rotation, int numOfPoints, GLenum mode);
// Main Function
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);                         // Set Display Mode
	glutInitWindowSize(windowWidth, windowHeight);                        // Set Display Size
	glutInitWindowPosition(windowPositionX, windowPositionY);                    // Set window pos at the screen
	glutCreateWindow("Drawing OpenGL");                                   // Open the screen window

	myInit();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);            // it takes two arguments

	glutMainLoop();                      // it maintains displaying the output on the screen (continuously) 
	return 0;
}
// Functions 
void DrawShape(float centerX, float centerY, float radius, float rotation, int numOfPoints, GLenum mode) {
	glBegin(mode);
	// to fix the circle shape (increase the number of points) you need to use this
	for (int i = 0; i <= numOfPoints; i++) {
	float angle = 2 * PI * i / numOfPoints;      // angle in radians
		glVertex2f(centerX + cos(angle + rotation) * radius, centerY + sin(angle + rotation) * radius);
	}
	glEnd();
}
// here you could right all lines of code that will control your display objects
void myDisplay() {

	glClear(GL_COLOR_BUFFER_BIT);          // Clear the screen, --> Clear the buffer 
	glColor3f(0.0, 0.0, 0.0);              // 3 means 3 colors input values
	glPointSize(5);                        // to control the size of the points
	
	// USE THE FUNC HERE BEFORE (glflush())


	glBegin(GL_POLYGON);
	glVertex2f(0.0, -50.0);

	glVertex2f(50.0, -50.0);
	glVertex2f(50.0,0.0);

	
	glVertex2f(0.0, 0.0);
	glEnd();

	glFlush();                           // take the values from the buffer and display it on the screen
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);    // Clear color and create a white Bg 
	glColor3f(0.0f, 0.0f, 0.0f);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                    // reset the projection matrix 
	gluOrtho2D(-(windowWidth / 2) , (windowWidth / 2), -(windowHeight / 2), (windowHeight / 2));
}
// reshape width and hight to maintain the aspect ratio
void reshape(int w, int h) {
	glViewport(0, 0, w, h);              // 0 , 0 to not change the width and hight
	glMatrixMode(GL_PROJECTION);         // to operate on the projection matrix

	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glLoadIdentity();                    // reset the projection matrix 
	if (w >= h)
	{
		// aspect > = 1, set the hight from -250 to 250, and set the width to be larger }
		gluOrtho2D(-(windowWidth / 2) * aspect, (windowWidth / 2) * aspect, -(windowHeight / 2), (windowHeight / 2));
	}
	else
	{
		// aspect < 1, set the width from -1 to 1, with larger hight
		gluOrtho2D(-(windowWidth / 2), (windowWidth / 2), -(windowHeight / 2) / aspect, (windowHeight / 2) / aspect);
	}
}

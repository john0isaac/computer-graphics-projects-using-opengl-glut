#include <Windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <math.h>

//Cube Sides
int a[3] = { 10,10,10 },
b[3] = { 10, -10, 10 },
c[3] = { -10, -10,10 },
d[3] = { -10, 10, 10 },
e[3] = { 10, 10, -10 },
f[3] = { 10, -10,-10 },
g[3] = { -10,-10,-10 },
h[3] = { -10, 10,-10 };

float angle = 0.1;
// constants values 
#define PI 3.14159256535898
#define windowWidth 600
#define windowHeight 600
#define windowPositionX 0
#define windowPositionY 0
// Functions Decleration

void myInit();
//void reshape(int, int);
void drawCube(void);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int btn, int state, int x, int y);

// Main Function
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);                         // Set Display Mode
	glutInitWindowSize(windowWidth, windowHeight);                        // Set Display Size
	glutInitWindowPosition(windowPositionX, windowPositionY);                    // Set window pos at the screen
	glutCreateWindow("Rotating Cube");                                   // Open the screen window
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawCube);
	glutIdleFunc(drawCube);
	myInit();
	//glutReshapeFunc(reshape);            // it takes two arguments
	glutMainLoop();                      // it maintains displaying the output on the screen (continuously) 
	return 0;
}
// Functions 
void drawCube(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glutWireCube(20);
	glFlush();
	glutSwapBuffers();
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 0x1B:
	case 'q':
	case 'Q':
		exit(0);
		break;
	}
}

void Mouse(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN)
	{
		if (btn == GLUT_LEFT_BUTTON)
			angle = angle - 0.1f;
		else if (btn == GLUT_RIGHT_BUTTON)
			angle = angle + 0.1f;
		else
			angle = 0.0f;
	}
}

void myInit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                    // reset the projection matrix 
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);    // Clear color and create a balck Bg 
}

// reshape width and hight to maintain the aspect ratio
/*
void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);         // to operate on the projection matrix
	float aspect = w / h;
	glLoadIdentity();
	glViewport(0, 0, w, h);
	if (aspect >= 1)
		glOrtho(-(windowWidth * aspect), (windowHeight * aspect), -windowWidth, windowHeight, 1.0, -1.0);
	else
		glOrtho(-windowWidth, windowHeight, -(windowHeight / aspect), (windowWidth / aspect), 1.0, -1.0);
}
*/


#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <unistd.h>
#include "RawDatabase.h"
#include "mathclass.h"
#include "pm.h"

#define FRAMERATE 120

using namespace std;

GLdouble rot[16]={1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
GLfloat mousePosX, mousePosY;

float eye[3] = {0.0f, 0.0f, 300.0f};
float ori[3] = {0.0f, 0.0f, 0.0f};
float yvector[3] = {0.0f, 1.0f, 0.0f};

float fov = 45;

int width, height;
int iter = 0;

bool leftButton = false;

RawDatabase* database;
PmLinearMotion* target;
PmHuman* character;

void loadGlobalCoord() {
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], ori[0], ori[1], ori[2], yvector[0], yvector[1], yvector[2]);
	glMultMatrixd(rot);
}
void glutMotion(int x, int y) {
	if(leftButton) {
		float dx = x - mousePosX;
		float dy = y - mousePosY;

		mousePosX = x;
		mousePosY = y;

		ori[0] -= dx*0.04;
		ori[1] += dy*0.04;

		loadGlobalCoord();
	}
	return;
}
void glutMouse(int button, int state, int x, int y) {
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON: 
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
	}
	return;
}
void drawMotion() {
	for(int i = 0; i < character->getNumLinks(); i++)
	{
		int p = character->getParent(i);
		if(p != PmHuman::UNDEFINED)
		{
			jhm::position curPos = target->getPosture(iter).getGlobalPosition(i);
			jhm::position parentPos = target->getPosture(iter).getGlobalPosition(p);
			glBegin(GL_LINES);
			glVertex3f(curPos.x(), curPos.y(), curPos.z());
			glVertex3f(parentPos.x(), parentPos.y(), parentPos.z());
			glEnd();
		}
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, 1.0, .1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	loadGlobalCoord();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	drawMotion();

	glutSwapBuffers();
	glFlush();
}
void resize(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, .1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}
void myidle() {
	sleep(0.05);
	if(target->getSize()-1 > iter) iter += 1;
	glutPostRedisplay();
}
int main(int argc, char **argv) {
	database = new RawDatabase();
	database->setCharacter("../data/16");
	database->loadLinearMotions("../data");

	target = database->getRawLinearMotion(0);
	character = database->getCharacter();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(50, 0);
	glutCreateWindow("motion viewer");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(myidle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);

	glutMainLoop();

	return 0;
}


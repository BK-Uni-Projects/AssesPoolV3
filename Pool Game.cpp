// Pool Game.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include <glut.h>

#include "vecmath.h"
#include "keyboard.h"
#include "camera.h"
#include "table.h"

/*-----------------------------------------------------------
  Macros
  -----------------------------------------------------------*/
const float TWO_PI = 6.2832f;
const int SIM_UPDATE_MS = 10;

/*-----------------------------------------------------------
  globals
  -----------------------------------------------------------*/
table gTable;



//rendering options
#define DRAW_SOLID	(0)




void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set camera
	glLoadIdentity();
	gluLookAt(gCamPos(0),gCamPos(1),gCamPos(2),gCamLookAt(0),gCamLookAt(1),gCamLookAt(2),0.0f,1.0f,0.0f);

	//draw the ball
	glColor3f(1.0,1.0,1.0);
	for(int i=0;i<NUM_BALLS;i++)
	{
		glPushMatrix();
		glTranslatef(gTable.balls[i].position(0),(BALL_RADIUS/2.0),gTable.balls[i].position(1));
		#if DRAW_SOLID
		glutSolidSphere(gTable.balls[i].radius,32,32);
		#else
		glutWireSphere(gTable.balls[i].radius,12,12);
		#endif
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
	}
	glColor3f(1.0,1.0,1.0);

	//draw the table
	for(int i=0;i<NUM_CUSHIONS;i++)
	{	
		glBegin(GL_LINE_LOOP);
		glVertex3f (gTable.cushions[i].vertices[0](0), 0.0, gTable.cushions[i].vertices[0](1));
		glVertex3f (gTable.cushions[i].vertices[0](0), 0.1, gTable.cushions[i].vertices[0](1));
		glVertex3f (gTable.cushions[i].vertices[1](0), 0.1, gTable.cushions[i].vertices[1](1));
		glVertex3f (gTable.cushions[i].vertices[1](0), 0.0, gTable.cushions[i].vertices[1](1));
		glEnd();
	}

	for(int i=0;i<gTable.parts.num;i++)
	{
		glColor3f(1.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(gTable.parts.particles[i]->position(0),gTable.parts.particles[i]->position(1),gTable.parts.particles[i]->position(2));
		#if DRAW_SOLID
		glutSolidSphere(0.002f,32,32);
		#else
		glutWireSphere(0.002f,12,12);
		#endif
		glPopMatrix();		
	}
	/*
	glBegin(GL_LINE_LOOP);
	glVertex3f (TABLE_X, 0.0, -TABLE_Z);
	glVertex3f (TABLE_X, 0.1, -TABLE_Z);
	glVertex3f (TABLE_X, 0.1, TABLE_Z);
	glVertex3f (TABLE_X, 0.0, TABLE_Z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f (TABLE_X, 0.0, -TABLE_Z);
	glVertex3f (TABLE_X, 0.1, -TABLE_Z);
	glVertex3f (-TABLE_X, 0.1, -TABLE_Z);
	glVertex3f (-TABLE_X, 0.0, -TABLE_Z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f (TABLE_X, 0.0, TABLE_Z);
	glVertex3f (TABLE_X, 0.1, TABLE_Z);
	glVertex3f (-TABLE_X, 0.1, TABLE_Z);
	glVertex3f (-TABLE_X, 0.0, TABLE_Z);
	glEnd();
	*/

	//draw the cue
	if(gDoCue)
	{
		glBegin(GL_LINES);
		float cuex = sin(gCueAngle) * gCuePower;
		float cuez = cos(gCueAngle) * gCuePower;
		glColor3f(1.0,0.0,0.0);
		glVertex3f (gTable.balls[0].position(0), (BALL_RADIUS/2.0f), gTable.balls[0].position(1));
		glVertex3f ((gTable.balls[0].position(0)+cuex), (BALL_RADIUS/2.0f), (gTable.balls[0].position(1)+cuez));
		glColor3f(1.0,1.0,1.0);
		glEnd();
	}

	//glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void ChangeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,0.2,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0,0.7,2.1, 0.0,0.0,0.0, 0.0f,1.0f,0.0f);
	gluLookAt(gCamPos(0),gCamPos(1),gCamPos(2),gCamLookAt(0),gCamLookAt(1),gCamLookAt(2),0.0f,1.0f,0.0f);
}

void InitLights(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_ambient[] = { 2.0, 2.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void UpdateScene(int ms) 
{
	if(gTable.AnyBallsMoving()==false) gDoCue = true;
	else gDoCue = false;

	if(gDoCue)
	{
		if(gCueControl[0]) gCueAngle -= ((gCueAngleSpeed * ms)/1000);
		if(gCueControl[1]) gCueAngle += ((gCueAngleSpeed * ms)/1000);
		if (gCueAngle <0.0) gCueAngle += TWO_PI;
		if (gCueAngle >TWO_PI) gCueAngle -= TWO_PI;

		if(gCueControl[2]) gCuePower += ((gCuePowerSpeed * ms)/1000);
		if(gCueControl[3]) gCuePower -= ((gCuePowerSpeed * ms)/1000);
		if(gCuePower > gCuePowerMax) gCuePower = gCuePowerMax;
		if(gCuePower < gCuePowerMin) gCuePower = gCuePowerMin;
	}

	DoCamera(ms);

	gTable.Update(ms);

	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutPostRedisplay();
}

int _tmain(int argc, _TCHAR* argv[])
{
	gTable.SetupCushions();

	glutInit(&argc, ((char **)argv));
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,700);
	//glutFullScreen();
	glutCreateWindow("MSc Workshop : Pool Game");
	#if DRAW_SOLID
	InitLights();
	#endif
	glutDisplayFunc(RenderScene);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecKeyboardFunc);
	glutSpecialUpFunc(SpecKeyboardUpFunc);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

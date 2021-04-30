/*W1790251 - Dulana Sandes Ratnayake - 2019763*/
/*YOUTUBE VEDIO LINK - https://youtu.be/Nn5axeJZKEI */


#include "include\freeglut.h"	// OpenGL toolkit - in the local shared folder
#include <cmath>
#include <iostream>
using namespace std;

//set up some constants
#define LENGTH   4.0      // lengths of sides of random obstacles 
//car variables
GLfloat carX = 20.0; 
GLfloat carY = 20.0;
GLfloat carAngle = 0;

GLfloat score = 00;		//game score 


/* reshape callback function
   executed when window is moved or resized. */
void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();
	glOrtho(-21.0, 21.0, -21.0, 22.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

GLfloat rx1, rx2, rx3, rx4, rx5, ry1, ry2, ry3, ry4, ry5;	//Variables for Center cordinates of random obstales
void randomObstacles(void)
{
	//genarating random numbers for center cordinates of random objects (in between -18 and 18)
	rx1 = rand() % 36 - 18;
	ry1 = rand() % 36 - 18;
	rx2 = rand() % 36 - 18;
	ry2 = rand() % 36 - 18;
	rx3 = rand() % 36 - 18;
	ry3 = rand() % 36 - 18;
	rx4 = rand() % 36 - 18;
	ry4 = rand() % 36 - 18;
	rx5 = rand() % 36 - 18;
	ry5 = rand() % 36 - 18;

	//to geanarate x,y cordinates for first obstacle without blocking start,end gates
	while ((rx1 <= -12 && ry1 <= -11) || (rx1 >= 12 && ry1 >= 11)) 
	{		
		rx1 = rand() % 36 - 18;
		ry1 = rand() % 36 - 18;
		
	}
	//to geanarate x,y cordinates for second obstacle without blocking start,end gates and without overlapping with first obstacle
	while ( (rx2 <= -12 && ry2 <= -11) || (rx2 >= 12 && ry2 >= 11) ||
		(rx2 > (rx1 - LENGTH) && rx2 < (rx1 + LENGTH) && ry2 > (ry1 - LENGTH) && ry2 < (ry1 + LENGTH) ) )
	{
		rx2 = rand() % 36 - 18;
		ry2 = rand() % 36 - 18;

	}
	//to geanarate x,y cordinates for third obstacle without blocking start,end gates and without overlapping with first and second obstacles
	while ((rx3 <= -12 && ry3 <= -11) || (rx3 >= 12 && ry3 >= 11) ||
		(rx3 > (rx1 - LENGTH) && rx3 < (rx1 + LENGTH) && ry3 > (ry1 - LENGTH) && ry3 < (ry1 + LENGTH)) ||
		(rx3 > (rx2 - LENGTH) && rx3 < (rx2 + LENGTH) && ry3 > (ry2 - LENGTH) && ry3 < (ry2 + LENGTH)) )
	{
		rx3 = rand() % 36 - 18;
		ry3 = rand() % 36 - 18;

	}
	//to geanarate x,y cordinates for fourth obstacle without blocking start,end gates and without overlapping with first, second and third obstacles
	while ((rx4 <= -12 && ry4 <= -11) || (rx4 >= 12 && ry4 >= 11) ||
		(rx4 > (rx1 - LENGTH) && rx4 < (rx1 + LENGTH) && ry4 > (ry1 - LENGTH) && ry4 < (ry1 + LENGTH)) ||
		(rx4 > (rx2 - LENGTH) && rx4 < (rx2 + LENGTH) && ry4 > (ry2 - LENGTH) && ry4 < (ry2 + LENGTH)) ||
		(rx4 > (rx3 - LENGTH) && rx4 < (rx3 + LENGTH) && ry4 > (ry3 - LENGTH) && ry4 < (ry3 + LENGTH)) ) 
	{
		rx4 = rand() % 36 - 18;
		ry4 = rand() % 36 - 18;
	}
	//to geanarate x,y cordinates for fifth obstacle without blocking start,end gates and without overlapping with first, second, third and fourth obstacles
	while ((rx5 <= -12 && ry5 <= -11) || (rx5 >= 12 && ry5 >= 11) ||
		(rx5 > (rx1 - LENGTH) && rx5 < (rx1 + LENGTH) && ry5 > (ry1 - LENGTH) && ry5 < (ry1 + LENGTH)) ||
		(rx5 > (rx2 - LENGTH) && rx5 < (rx2 + LENGTH) && ry5 > (ry2 - LENGTH) && ry5 < (ry2 + LENGTH)) ||
		(rx5 > (rx3 - LENGTH) && rx5 < (rx3 + LENGTH) && ry5 > (ry3 - LENGTH) && ry5 < (ry3 + LENGTH)) ||
		(rx5 > (rx4 - LENGTH) && rx5 < (rx4 + LENGTH) && ry5 > (ry4 - LENGTH) && ry5 < (ry4 + LENGTH)))
	{
		rx5 = rand() % 36 - 18;
		ry5 = rand() % 36 - 18;
	}
}

int gridX = -19;
void gridOn(void) {		//grid on method (not working)
	glColor3f(0.0, 0.0, 0.0);
	for (gridX; gridX <= 19; gridX++) {
		glBegin(GL_LINE);
		glVertex2f(gridX, 20);
		glVertex2f(gridX, -20);
		glutPostRedisplay();
		glEnd();
		glFlush();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     /* clear window */

	gridOn();
	//Level restarting, When car goes to end gate
	if (carX >= 16 && carY >= 16) 
	{
		randomObstacles();
		score += 50;		//increase score
		carX = -15.0;		//set x cordinate to start gate
		carY = -15.0;		//set y cordinate to start gate
		cout << "Level Passed !" << endl;	//passing message to console
	}
	
	//Scoreboard Text
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-18, 21); //define position on the screen
	char* string = "Score";

	while (*string) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
	}


	//Random Obstacles
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0, 0.0f);
	glVertex2f(rx1 - LENGTH / 2, ry1 - LENGTH / 2);
	glVertex2f(rx1 - LENGTH / 2, ry1 + LENGTH / 2);
	glVertex2f(rx1 + LENGTH / 2, ry1 + LENGTH / 2);
	glVertex2f(rx1 + LENGTH / 2, ry1 - LENGTH / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0, 0.0f);
	glVertex2f(rx2 - LENGTH / 2, ry2 - LENGTH / 2);
	glVertex2f(rx2 - LENGTH / 2, ry2 + LENGTH / 2);
	glVertex2f(rx2 + LENGTH / 2, ry2 + LENGTH / 2);
	glVertex2f(rx2 + LENGTH / 2, ry2 - LENGTH / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0, 0.0f);
	glVertex2f(rx3 - LENGTH / 2, ry3 - LENGTH / 2);
	glVertex2f(rx3 - LENGTH / 2, ry3 + LENGTH / 2);
	glVertex2f(rx3 + LENGTH / 2, ry3 + LENGTH / 2);
	glVertex2f(rx3 + LENGTH / 2, ry3 - LENGTH / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0, 0.0f);
	glVertex2f(rx4 - LENGTH / 2, ry4 - LENGTH / 2);
	glVertex2f(rx4 - LENGTH / 2, ry4 + LENGTH / 2);
	glVertex2f(rx4 + LENGTH / 2, ry4 + LENGTH / 2);
	glVertex2f(rx4 + LENGTH / 2, ry4 - LENGTH / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0, 0.0f);
	glVertex2f(rx5 - LENGTH / 2, ry5 - LENGTH / 2);
	glVertex2f(rx5 - LENGTH / 2, ry5 + LENGTH / 2);
	glVertex2f(rx5 + LENGTH / 2, ry5 + LENGTH / 2);
	glVertex2f(rx5 + LENGTH / 2, ry5 - LENGTH / 2);
	glEnd();

	//CAR
	glPushMatrix();
	glTranslatef(carX, carY, 0);
	glRotatef(carAngle, 0.0f, 0.0f, 1.0f);
	
	//Front Part
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(2.0, 3.5);
	glVertex2f(2.0, 3.75);
	glVertex2f(-2.0, 3.75);
	glVertex2f(-2.0, 3.5);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(2.0, 3.25);
	glVertex2f(2.0, 4.0);
	glVertex2f(1.5, 3.25);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-2.0, 3.25);
	glVertex2f(-1.5, 3.25);
	glVertex2f(-2.0, 4.0);
	glEnd();

	//Back part - Spoiler
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, -3.0);
	glVertex2f(0.0, -1.5);
	glVertex2f(-0.5, -3.0);
	glVertex2f(-1.5, -3.0);
	glVertex2f(-1.5, -3.5);
	glVertex2f(1.5, -3.5);
	glVertex2f(1.5, -3.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.5, -3.0);
	glVertex2f(-1.5, -4.0);
	glVertex2f(-1.0, -3.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(1.5, -3.0);
	glVertex2f(1.5, -4.0);
	glVertex2f(1.0, -3.0);
	glEnd();
	//Front right tire
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(2.0, 2.0);
	glVertex2f(2.0, 3.0);
	glVertex2f(1.0, 3.0);
	glVertex2f(1.0, 2.0);
	glEnd();
	//Front left tire
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-2.0, 2.0);
	glVertex2f(-2.0, 3.0);
	glVertex2f(-1.0, 3.0);
	glVertex2f(-1.0, 2.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(2.0, 2.5);
	glVertex2f(-2.0, 2.5);
	glEnd();
	//Back right tire
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(2.0, -2.5);
	glVertex2f(2.0, -1.5);
	glVertex2f(1.0, -1.5);
	glVertex2f(1.0, -2.5);
	glEnd();
	//Back left tire
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-2.0, -1.5);
	glVertex2f(-2.0, -2.5);
	glVertex2f(-1.0, -2.5);
	glVertex2f(-1.0, -1.5);
	glEnd();
	//Car Body
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(1.0, -2.25);
	glVertex2f(1.5, -2.0);
	glVertex2f(1.5, 1.0);
	glVertex2f(0.0, 4.0);
	glVertex2f(-1.5, 1.0);
	glVertex2f(-1.5, -2.0);
	glVertex2f(-1.0, -2.25);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5, -1.5);
	glVertex2f(0.5, 1.0);
	glVertex2f(0.0, 1.5);
	glVertex2f(-0.5, 1.0);
	glVertex2f(-0.5, -1.5);
	glEnd();
	
	glPopMatrix();
	
	//Start Gate
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-20.0f, -20.0f);
	glVertex2f(-14.0, -20.0);
	glVertex2f(-14.0, -19.0);
	glVertex2f(-20.0, -19.0);
	glEnd();
	//End Gate
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(14.0, 19.0);
	glVertex2f(20.0, 19.0);
	glVertex2f(20.0, 20.0);
	glVertex2f(14.0, 20.0);
	glEnd();
	//Border - play area
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-20.0f, -20.0f);
	glVertex2f(20.0f, -20.0f);
	glVertex2f(20.0f, 20.0f);
	glVertex2f(-20.0f, 20.0f);
	glEnd();

	

	glFlush();     /* execute drawing commands in buffer */
}

/* graphics initialisation */
void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);     /* window will be cleared to gray */
}

//keyboard function
void keyboard(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case 'w':
		if (carAngle == 0 || carAngle == 360 || carAngle == -360)
		{
			if (carY <= 15) {	//car only moves in the play area - Border Collusion
				if (carX <= (rx1 + 3) && carX >= (rx1 - 3) && carY > (ry1 - 7) && carY < (ry1 - 2) ||
					carX <= (rx2 + 3) && carX >= (rx2 - 3) && carY > (ry2 - 7) && carY < (ry2 - 2) ||
					carX <= (rx3 + 3) && carX >= (rx3 - 3) && carY > (ry3 - 7) && carY < (ry3 - 2) ||		//collusion detection for Bottom faces of obstacles
					carX <= (rx4 + 3) && carX >= (rx4 - 3) && carY > (ry4 - 7) && carY < (ry4 - 2) ||
					carX <= (rx5 + 3) && carX >= (rx5 - 3) && carY > (ry5 - 7) && carY < (ry5 - 2) ) {
					
					cout << "Crashed! -10 points" << endl;
					score -= 10;		//deducting points after crashing
					cout << "Score is " << score << endl;
					break;
				}
				else {
					carY++;
					cout << "Move forward" << endl;
					glutPostRedisplay();
					break;
				}
			}
			else {
				cout << "Cannot Move" << endl;
				break;
			}
		}
		else if (carAngle == 90 || carAngle == -270 || carAngle == 450 || carAngle == -630)
		{
			if (carX >= -15){	//car only moves in the play area
				if (carX <= (rx1 + 6) && carX >= (rx1 + 2) && carY >(ry1 - 4) && carY < (ry1 + 4) ||
					carX <= (rx2 + 6) && carX >= (rx2 + 2) && carY >(ry2 - 4) && carY < (ry2 + 4) ||
					carX <= (rx3 + 6) && carX >= (rx3 + 2) && carY >(ry3 - 4) && carY < (ry3 + 4) ||		//collusion detection for Left face of obstacles
					carX <= (rx4 + 6) && carX >= (rx4 + 2) && carY >(ry4 - 4) && carY < (ry4 + 4) ||
					carX <= (rx5 + 6) && carX >= (rx5 + 2) && carY >(ry5 - 4) && carY < (ry5 + 4)) {
					
					cout << "Crashed! -10 points" << endl;
					score -= 10;		//deducting points after crashing
					cout << "Score is " << score << endl;
					break;
				}
				else {
					carX--;
					cout << "Move forward in left" << endl;
					glutPostRedisplay();
					break;
				}
			}
			else {
				cout << "Cannot Move" << endl;
				break;
			}
		}
		else if (carAngle == 180 || carAngle == -180 || carAngle == 540 || carAngle == -540)
		{
			if (carY >= -15) {	//car only moves in the play area
				if (carX <= (rx1 + 3) && carX >= (rx1 - 3) && carY >(ry1 + 2) && carY < (ry1 + 7) ||
					carX <= (rx2 + 3) && carX >= (rx2 - 3) && carY >(ry2 + 2) && carY < (ry2 + 7) ||
					carX <= (rx3 + 3) && carX >= (rx3 - 3) && carY >(ry3 + 2) && carY < (ry3 + 7) ||		//collusion detection for Top face of obstacles
					carX <= (rx4 + 3) && carX >= (rx4 - 3) && carY >(ry4 + 2) && carY < (ry4 + 7) ||
					carX <= (rx5 + 3) && carX >= (rx5 - 3) && carY >(ry5 + 2) && carY < (ry5 + 7) ) {

					cout << "Crashed! -10 points" << endl;
					score -= 10;		//deducting points after crashing
					cout << "Score is " << score << endl;
					break;
				}
				else {
					carY--;
					cout << "Move forward in back" << endl;
					glutPostRedisplay();
					break;
				}
			}
			else {
				cout << "Cannot Move" << endl;
				break;
			}
		}
		else
		{
			if (carAngle == 270 || carAngle == -90 || carAngle == 630 || carAngle == -450)
			{
				if (carX <= (rx1 - 2) && carX >= (rx1 - 6) && carY >(ry1 - 4) && carY < (ry1 + 4) ||
					carX <= (rx2 - 2) && carX >= (rx2 - 6) && carY >(ry2 - 4) && carY < (ry2 + 4) ||
					carX <= (rx3 - 2) && carX >= (rx3 - 6) && carY >(ry3 - 4) && carY < (ry3 + 4) ||		//collusion detection for Right face of obstacles
					carX <= (rx4 - 2) && carX >= (rx4 - 6) && carY >(ry4 - 4) && carY < (ry4 + 4) ||
					carX <= (rx5 - 2) && carX >= (rx5 - 6) && carY >(ry5 - 4) && carY < (ry5 + 4) ) {
				
					cout << "Crashed! -10 points" << endl;
					score -= 10;		//deducting points after crashing
					cout << "Score is " << score << endl;
					break;
				}
				else {
					if (carX <= 15) {	//car only moves in the play area
						carX++;
						cout << "Move forward in right" << endl;
						glutPostRedisplay();
						break;
					}
					else {
						cout << "Cannot Move" << endl;
						break;
					}
				}
			}
		}
		
	case 's':
		if (carAngle == 0)
		{
			if (carX <= (rx1 + 3) && carX >= (rx1 - 3) && carY >(ry1 + 2) && carY < (ry1 + 7) ||
				carX <= (rx2 + 3) && carX >= (rx2 - 3) && carY >(ry2 + 2) && carY < (ry2 + 7) ||
				carX <= (rx3 + 3) && carX >= (rx3 - 3) && carY >(ry3 + 2) && carY < (ry3 + 7) ||		//collusion detection for Top face of obstacles
				carX <= (rx4 + 3) && carX >= (rx4 - 3) && carY >(ry4 + 2) && carY < (ry4 + 7) ||
				carX <= (rx5 + 3) && carX >= (rx5 - 3) && carY >(ry5 + 2) && carY < (ry5 + 7)) {
			
				cout << "Crashed! -10 points" << endl;
				score -= 10;		//deducting points after crashing
				cout << "Score is " << score << endl;
				break;
			}
			else {
				if (carY >= -15) {	//car only moves in the play area
					carY--;
					cout << "Move backward" << endl;
					glutPostRedisplay();
					break;
				}
				else {
					break;
				}
			}
		}
		else if (carAngle == 90 || carAngle == -270)
		{
			if (carX <= (rx1 - 2) && carX >= (rx1 - 6) && carY >(ry1 - 4) && carY < (ry1 + 4) ||
				carX <= (rx2 - 2) && carX >= (rx2 - 6) && carY >(ry2 - 4) && carY < (ry2 + 4) ||
				carX <= (rx3 - 2) && carX >= (rx3 - 6) && carY >(ry3 - 4) && carY < (ry3 + 4) ||		//collusion detection for Right face of obstacles
				carX <= (rx4 - 2) && carX >= (rx4 - 6) && carY >(ry4 - 4) && carY < (ry4 + 4) ||
				carX <= (rx5 - 2) && carX >= (rx5 - 6) && carY >(ry5 - 4) && carY < (ry5 + 4)) {
			
				cout << "Crashed! -10 points" << endl;
				score -= 10;		//deducting points after crashing
				cout << "Score is " << score << endl;
				break;
			}
			else {
				if (carX <= 15) {	//car only moves in the play area
					carX++;
					cout << "Move backward in left" << endl;
					glutPostRedisplay();
					break;
				}
				else {
					break;
				}
			}
		}
		else if (carAngle == 180 || carAngle == -180)
		{
			if (carX <= (rx1 + 3) && carX >= (rx1 - 3) && carY >(ry1 - 7) && carY < (ry1 - 2) ||
				carX <= (rx2 + 3) && carX >= (rx2 - 3) && carY >(ry2 - 7) && carY < (ry2 - 2) ||
				carX <= (rx3 + 3) && carX >= (rx3 - 3) && carY >(ry3 - 7) && carY < (ry3 - 2) ||		//collusion detection for Bottom faces of obstacles
				carX <= (rx4 + 3) && carX >= (rx4 - 3) && carY >(ry4 - 7) && carY < (ry4 - 2) ||
				carX <= (rx5 + 3) && carX >= (rx5 - 3) && carY >(ry5 - 7) && carY < (ry5 - 2)) {
			
				cout << "Crashed! -10 points" << endl;
				score -= 10;		//deducting points after crashing
				cout << "Score is " << score << endl;
				break;
			}
			else {
				if (carY <= 15) {	//car only moves in the play area
					carY++;
					cout << "Move backward" << endl;
					glutPostRedisplay();
					break;
				}
				else {
					break;
				}
			}
		}
		else
		{
			if (carAngle == 270 || carAngle >= -90)
			{
				if (carX <= (rx1 + 6) && carX >= (rx1 + 2) && carY > (ry1 - 4) && carY < (ry1 + 4) ||
					carX <= (rx2 + 6) && carX >= (rx2 + 2) && carY >(ry2 - 4) && carY < (ry2 + 4) ||
					carX <= (rx3 + 6) && carX >= (rx3 + 2) && carY >(ry3 - 4) && carY < (ry3 + 4) ||		//collusion detection for Left face of obstacles
					carX <= (rx4 + 6) && carX >= (rx4 + 2) && carY >(ry4 - 4) && carY < (ry4 + 4) ||
					carX <= (rx5 + 6) && carX >= (rx5 + 2) && carY >(ry5 - 4) && carY < (ry5 + 4)) {
				
					cout << "Crashed! -10 points" << endl;
					score -= 10;		//deducting points after crashing
					cout << "Score is " << score << endl;
					break;
				}
				else {
					if (carX >= -15) {	//car only moves in the play area
						carX--;
						cout << "Move backward in right" << endl;
						glutPostRedisplay();
						break;
					}
					else {
						break;
					}
				}
			}
			else
			{
				carAngle == 0;
				glutPostRedisplay();
			}
		}
	case 'd':
		carAngle -= 90;		//Rotate car to the right
		cout << "Rotate to Right" << endl;
		glutPostRedisplay();
		break;
	case 'a':
		carAngle += 90;		//Rotate car to the left
		cout << "Rotate to Left" << endl;
		glutPostRedisplay();
		break;

	default:
		cout << "! - Invalid Input - !" << endl;	//If user enters a key except w,a,s,d this will pass message to the console
		break;
	}

}

void popUpMenu(int option) {
	switch (option)
	{
	case 1:
		gridOn();
		glutPostRedisplay();
		break;
	case 2:
		randomObstacles();
		glutPostRedisplay();
		break;
	default:
		break;
	}
	
}
int main(int argc, char** argv)
{
	/* window management code ... */
/* initialises GLUT and processes any command line arguments */
	glutInit(&argc, argv);
	/* use single-buffered window and RGBA colour model */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	/* creates an OpenGL window with command argument in its title bar */
	glutCreateWindow("Car game");
	
	glutCreateMenu(popUpMenu);
	glutAddMenuEntry("Grid On", 1);
	glutAddMenuEntry("Pattern Change", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


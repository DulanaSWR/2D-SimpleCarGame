/*
 5CCGD003W - Tutorial 1 - example code
 program draws a white rectangle on a black background
*/
// Code by Dr Anastassia Angelopoulou 


#include "include\freeglut.h"	// OpenGL toolkit - in the local shared folder
#include <iostream>

//set up some constants
#define X_CENTRE 0.0      /* centre point of square */
#define Y_CENTRE 0.0
#define LENGTH   1.0      /* lengths of sides of square */

GLfloat red = 1.0, green = 1.0, blue = 1.0;


/* reshape callback function
executed when window is moved or resized */
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	/* uses orthographic (parallel) projection
	use xmin = -1, xmax = 1
	ymin = -1, ymax = 1
	znear = -1, zfar = 1 - not relevant here (2D) */
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


/* display callback function
called whenever contents of window need to be re-displayed */
//this is the all important drawing method - all drawing code goes in here
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   /* clear window */
	glColor3f(red, green, blue);        /* white drawing objects */
   
    /* define object to be drawn as a square polygon */
	glBegin(GL_POLYGON);

	//specify the vertices (points in 3D space) of the shape - note that these are 2D points
	glVertex2f(X_CENTRE - LENGTH / 2, Y_CENTRE - LENGTH / 2);
	glVertex2f(X_CENTRE - LENGTH / 2, Y_CENTRE + LENGTH / 2);
	glVertex2f(X_CENTRE + LENGTH / 2, Y_CENTRE + LENGTH / 2);
	glVertex2f(X_CENTRE + LENGTH / 2, Y_CENTRE - LENGTH / 2);

	glEnd();

	glFlush();     /* execute drawing commands in buffer */
}

/* graphics initialisation */
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   /* window will be cleared to black */
}

//rename this to main(...) and change example 2 to run this main function
int main(int argc, char** argv)
{
	/* window management code ... */
	/* initialises GLUT and processes any command line arguments */
	glutInit(&argc, argv);
	/* use single-buffered window and RGBA colour model */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* window width = 400 pixels, height = 400 pixels */
	glutInitWindowSize(400, 400);
	/* window upper left corner at (100, 100) */
	glutInitWindowPosition(100, 100);
	/* creates an OpenGL window with command argument in its title bar */
	glutCreateWindow("Example 1");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}


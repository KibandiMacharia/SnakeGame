#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/glu.h>
#include "game.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#define COLUMNS 40
#define ROWS 40
#define FPS 6

extern short sDirection;
bool gameOver = false;

int score = 0;

void timer_callback(int);
void display_callback();
void reshape_callback(int,int);
void keyboard_callback(int, int, int);//key pressed,position of mouse

void init() {
	glClearColor(0.0,0.0,0.0,1.0);//set background color
	initGrid(COLUMNS, ROWS);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake 2D game");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);//called when window is first created
	glutTimerFunc(0,timer_callback,0);// registers callback to be triggerred after particular time
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return 0;
}

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);//clear color in new frame to glcolor
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();//load next frame
	//display game over message
	if (gameOver) {
		char _score[10];
		_itoa_s(score, _score, 10);//integer to character
		char text[50] = "Your score is ";
		strcat_s(text, _score);
		MessageBoxA(NULL, text, "Game Over", 0);
		exit(0);
	}
}

void reshape_callback(int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);// set viewport where objects appear
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//no changes to matrix at first
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

//display animation
void timer_callback(int) {
	glutPostRedisplay();//call display funcion immediately
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

//keyboard input
void keyboard_callback(int key, int, int) {
	switch (key)
	{//if key up
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
			sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
			sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
			sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
			sDirection = LEFT;
		break;
	default:
		break;
	}
}

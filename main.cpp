#include <GLUT/glut.h>
#include <stdio.h>
#include <random>
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "CONST.h"
#include "MODEL.h"
#include "header.h"
#include "esa.cpp"
#include "bird.cpp"
#include "taka.cpp"


int main(int argc, char *argv[]){
	srand((unsigned int)time(NULL));

	for(int i = 0; i < _NumberOfBird_; i++){
		birdList.push_back(bird());
	}

	for(int i = 0; i < 10; i++){
		takaList.push_back(taka());
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutCreateWindow(argv[0]);
//	glutMouseFunc( mouse );
	glutDisplayFunc(display);
	buildDisplayList();
	glutTimerFunc(20, timer, 0);
	glutMainLoop();



	return 0;
}

void display(void){
	glClearColor(0.8,0.8,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for(auto &elem: esaList){
		glPushMatrix();
		glColor3d(elem.color.r,elem.color.g,elem.color.b);
		glTranslated(elem.position.x,elem.position.y,0);
		glCallList(1);
		glPopMatrix();
	}

	for(auto &elem: birdList){
		glPushMatrix();
		glColor3d(elem.color.r,elem.color.g,elem.color.b);
		glTranslated(elem.position.x,elem.position.y,0);
		glCallList(1);
		glPopMatrix();
	}

	for(auto &elem: takaList){
		glPushMatrix();
		glColor3d(elem.color.r,elem.color.g,elem.color.b);
		glTranslated(elem.position.x,elem.position.y,0);
		glCallList(1);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void buildDisplayList(){ //boidとしての円
	glNewList(1,GL_COMPILE);

	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++){
		double x = cos(i*M_PI/180.0);
		double y = sin(i*M_PI/180.0);
		glVertex2d(x*0.01,y*0.01);
	}
	glEnd();

	glEndList();

}

void timer(int value){ //一定時間ごとに呼び出し,移動用
	//鳥を動かす
	//for(int i = 0; i < birdList.size(); i++){
	//
	if(rand()%30 == 0){
		esaList.push_back(esa());
	}
	for(auto &elem: birdList){
		elem.move();
	}

	for(auto &elem: takaList){
		elem.move();
	}
	

	glutPostRedisplay();
	glutTimerFunc(10,timer,0);
}



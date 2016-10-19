#include <GL/glut.h>
#include <stdio.h>
#include <random>
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "header.h"

using namespace std;

#define ID_DRAW_BOID 1

void mouse( int button, int state, int x, int y ){
	//マウスの左ボタンが押された時に、マウスポインタの座標を更新
	if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ){
		bird newBird = bird();
		newBird.position.x = ((double)x-400)/400;
		newBird.position.y = -((double)y-400)/400;
		birdList.push_back(newBird);
	}
	if( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN ){
		enemy newEnemy = enemy();
		newEnemy.position.x = ((double)x-400)/400;
		newEnemy.position.y = -((double)y-400)/400;
		newEnemy.color.r = 1;
		newEnemy.color.g = 0;
		newEnemy.color.b = 0;
		enemyList.push_back(newEnemy);
	}
}

int main(int argc, char *argv[]){
	srand((unsigned int)time(NULL));

	for(int i = 0; i < _NumberOfBird_; i++){
		birdList.push_back(bird());
	}

	for(int i = 0; i < 49; i++){
		int x = 10 + 16 * i;
		int y = 10;
		enemy newEnemy = enemy();
		newEnemy.position.x = ((double)x-400)/400;
		newEnemy.position.y = -((double)y-400)/400;
		newEnemy.color.r = 1;
		newEnemy.color.g = 0;
		newEnemy.color.b = 0;
		newEnemy.speed = 0;
		enemyList.push_back(newEnemy);
	}

	for(int i = 0; i < 49; i++){
		int x = 10 + 16 * i;
		int y = 790;
		enemy newEnemy = enemy();
		newEnemy.position.x = ((double)x-400)/400;
		newEnemy.position.y = -((double)y-400)/400;
		newEnemy.color.r = 1;
		newEnemy.color.g = 0;
		newEnemy.color.b = 0;
		newEnemy.speed = 0;
		enemyList.push_back(newEnemy);
	}

	for(int i = 0; i < 49; i++){
		int y = 10 + 16 * i;
		int x = 10;
		enemy newEnemy = enemy();
		newEnemy.position.x = ((double)x-400)/400;
		newEnemy.position.y = -((double)y-400)/400;
		newEnemy.color.r = 1;
		newEnemy.color.g = 0;
		newEnemy.color.b = 0;
		newEnemy.speed = 0;
		enemyList.push_back(newEnemy);
	}

	for(int i = 0; i < 49; i++){
		int y = 10 + 16 * i;
		int x = 790;
		enemy newEnemy = enemy();
		newEnemy.position.x = ((double)x-400)/400;
		newEnemy.position.y = -((double)y-400)/400;
		newEnemy.color.r = 1;
		newEnemy.color.g = 0;
		newEnemy.color.b = 0;
		newEnemy.speed = 0;
		enemyList.push_back(newEnemy);
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutCreateWindow(argv[0]);
	glutMouseFunc( mouse );
	glutDisplayFunc(display);
	buildDisplayList();
	glutTimerFunc(20, timer, 0);
	glutMainLoop();

	return 0;
}

//初期化
bird::bird(){
	position.x	= rand()%200/100.0 - 1;
	position.y	= rand()%200/100.0 - 1;
	direction	= rand()%int(M_PI*200)/100.0 - M_PI;
	speed		= rand()%100/100.0;
	color.r		= rand()%70/100.0 + 0.2;
	color.g		= rand()%70/100.0 + 0.2;
	color.b		= rand()%70/100.0 + 0.2;
}


//移動
void bird::move(){

//	if(rand()%6 == 0){
	if(true){
		int rule1birdCount = 0;
		int rule2birdCount = 0;
		int rule3birdCount = 0;
		int rule4birdCount = 0;
		double rule1centerX = 0;
		double rule1centerY = 0;
		double rule2centerX = 0;
		double rule2centerY = 0;
		double rule3centerX = 0;
		double rule3centerY = 0;
		double rule3speed = 0;
		double rule4centerX = 0;
		double rule4centerY = 0;
		double nextStepX = 0;
		double nextStepY = 0;
		double colorR = 0;
		double colorG = 0;
		double colorB = 0;
		
		//for(int i = 0; i < birdList.size(); i ++){
		for(auto &elem: birdList){
			if(this == &elem) continue;
			double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));

			if(distance < _rule1Distance_){
				rule1birdCount ++;
				rule1centerX	+= elem.position.x;
				rule1centerY	+= elem.position.y;
			}
			if(distance < _rule2Distance_){
				rule2birdCount ++;
				rule2centerX	+= elem.position.x;
				rule2centerY	+= elem.position.y;
			}
			if(distance < _rule3Distance_){
				rule3birdCount ++;
				rule3speed		+= elem.speed;
//				rule3direction	+= elem.direction;
				rule3centerX	+= cos(elem.direction);
				rule3centerY	+= sin(elem.direction);
				colorR			+= elem.color.r;
				colorG			+= elem.color.g;
				colorB			+= elem.color.b;
			}

			if(distance < 0.01){
				nextStepX += rand()%2000/100.0 - 10;
				nextStepY += rand()%2000/100.0 - 10;
				//speed *= 0.5;
//				elem.speed *= 0.1;
			}

			/*
			if(speed < 0.01){
				for(int i = 0; i < birdList.size(); i++){
					if(this == &birdList[i]){
						//birdList.
						//remove(birdList, i);
						birdList.erase(birdList.begin() + i);
					}
				}

				for(int i = 0; i < birdList.size(); i++){
					if(&elem == &birdList[i]){
						//birdList.
						//remove(birdList, i);
						birdList.erase(birdList.begin() + i);
					}
				}
			}
			*/

		}

		for(auto &elem: enemyList){
			double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));

			if(distance < _rule4Distance_){
				rule4birdCount ++;
				rule4centerX	+= elem.position.x;
				rule4centerY	+= elem.position.y;
			}
			if(distance < 0.05){
				speed *= 1.01;
			}
		}

		if(rule1birdCount != 0){
			double centerXave = rule1centerX/rule1birdCount;
			double centerYave = rule1centerY/rule1birdCount;

			nextStepX += (centerXave - position.x) * _rule1Effect_;
			nextStepY += (centerYave - position.y) * _rule1Effect_;
		}

		if(rule2birdCount != 0){
			double centerXave = rule2centerX/rule2birdCount;
			double centerYave = rule2centerY/rule2birdCount;

			nextStepX += (position.x - centerXave) * _rule2Effect_;
			nextStepY += (position.y - centerYave) * _rule2Effect_;

			double newR = colorR/rule3birdCount;
			double newG = colorG/rule3birdCount;
			double newB = colorB/rule3birdCount;

			color.r = newR * _colorEffect_ + color.r * (1-_colorEffect_);
			color.g = newG * _colorEffect_ + color.g * (1-_colorEffect_);
			color.b = newB * _colorEffect_ + color.b * (1-_colorEffect_);
		}

		if(rule3birdCount != 0){
			double newSpeed		= rule3speed / rule3birdCount;
			double centerXave = rule3centerX / rule3birdCount;
			double centerYave = rule3centerY / rule3birdCount;

			speed		= newSpeed * _speedEffect_ + speed * (1-_speedEffect_);
			nextStepX += centerXave * _rule3Effect_;
			nextStepY += centerYave * _rule3Effect_;
		}

		if(rule4birdCount != 0){
			double centerXave = rule4centerX/rule4birdCount;
			double centerYave = rule4centerY/rule4birdCount;

			nextStepX += (position.x - centerXave) * _rule4Effect_;
			nextStepY += (position.y - centerYave) * _rule4Effect_;
		}

		nextStepX += cos(direction) * _defaultEffect_;
		nextStepY += sin(direction) * _defaultEffect_;

		nextStepX += (rand()%200/100.0 - 1) * _randomEffect_;
		nextStepY += (rand()%200/100.0 - 1) * _randomEffect_;

		direction = atan2(nextStepY, nextStepX);
	}


	/*
	if(position.x > 0.9) direction = direction + M_PI * 0.1;
	if(position.x < -0.9) direction = direction + M_PI * 0.1;
	if(position.y > 0.9) direction = direction + M_PI * 0.1;
	if(position.y < -0.9) direction = direction + M_PI * 0.1;

	if(position.x > 1) position.x = 1;
	if(position.x < -1) position.x = -1;
	if(position.y > 1) position.y = 1;
	if(position.y < -1) position.y = -1;
	*/

	position.x += cos(direction)*speed/100;
	position.y += sin(direction)*speed/100;

	if(position.x > 1) position.x -= 2;
	if(position.x < -1) position.x -= -2;
	if(position.y > 1) position.y -= 2;
	if(position.y < -1) position.y -= -2;


}

void enemy::move(){

	if(true){
		double rule1birdCount = 0;
		double rule1centerX = 0;
		double rule1centerY = 0;
		double nextStepX = 0;
		double nextStepY = 0;
		
		for(auto &elem: birdList){
			if(this == &elem) continue;
			double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));

			if(distance < _enemy1Distance_){
				rule1birdCount ++;
				rule1centerX	+= elem.position.x;
				rule1centerY	+= elem.position.y;
			}

			if(distance < 0.01){
				for(int i = 0; i < birdList.size(); i++){
					if(&elem == &birdList[i]){
						//birdList.
						//remove(birdList, i);
						birdList.erase(birdList.begin() + i);
					}
				}
			}

		}

		if(rule1birdCount != 0){
			double centerXave = rule1centerX/rule1birdCount;
			double centerYave = rule1centerY/rule1birdCount;

			nextStepX += (centerXave - position.x) * _enemy1Effect_;
			nextStepY += (centerYave - position.y) * _enemy1Effect_;
		}

		nextStepX += cos(direction) * _defaultEffect_;
		nextStepY += sin(direction) * _defaultEffect_;

		nextStepX += (rand()%200/100.0 - 1) * _randomEffect_;
		nextStepY += (rand()%200/100.0 - 1) * _randomEffect_;

		direction = atan2(nextStepY, nextStepX);
	}

	position.x += cos(direction)*speed/100;
	position.y += sin(direction)*speed/100;

	if(position.x > 1) position.x -= 2;
	if(position.x < -1) position.x -= -2;
	if(position.y > 1) position.y -= 2;
	if(position.y < -1) position.y -= -2;


}




void display(void){
	glClearColor(0.9,0.9,0.9,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//for(int j=0;j<birdList.size();j++){
	for(auto &elem: birdList){
		glPushMatrix();
		glColor3d(elem.color.r,elem.color.g,elem.color.b);
		glTranslated(elem.position.x,elem.position.y,0);
		glCallList(ID_DRAW_BOID);
		glPopMatrix();
	}

	for(auto &elem: enemyList){
		glPushMatrix();
		glColor3d(elem.color.r,elem.color.g,elem.color.b);
		glTranslated(elem.position.x,elem.position.y,0);
		glCallList(ID_DRAW_BOID);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void timer(int value){ //一定時間ごとに呼び出し,移動用
	//鳥を動かす
	//for(int i = 0; i < birdList.size(); i++){
	for(auto &elem: birdList){
		elem.move();
	}
	for(auto &elem: enemyList){
		elem.move();
	}
	glutPostRedisplay();
	glutTimerFunc(10,timer,0);
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



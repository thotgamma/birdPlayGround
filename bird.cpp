#include "esa.h"
#include "bird.h"
#include "taka.h"
#include "MODEL.h"
#include "CONST.h"
#include <random>



bird::bird(){
	position	= Position();
	direction	= rand()%int(M_PI*200)/100.0 - M_PI;
	speed		= rand()%100/100.0;
	life		= rand()%1000/10;
	color		= Color(0.1, 0.1, life/100);
}

bird::bird(Position pos){
	position	= pos;
	direction	= rand()%int(M_PI*200)/100.0 - M_PI;
	speed		= rand()%100/100.0;
	life		= rand()%1000/10;
	color		= Color(0.1, 0.1, life/100);
}

void bird::move(){

	int esaCount  = 0;
	int birdCount = 0;
	int takaCount = 0;
	
	Position esaPosition	= Position(0,0);
	Position birdPosition	= Position(0,0);
	Position takaPosition	= Position(0,0);

	double nextStepX = 0;
	double nextStepY = 0;

	for(auto &elem: esaList){
		double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));
		if(distance < esaRange){
			esaCount ++;
			esaPosition += elem.position;
		}
	}
	if(esaCount != 0) esaPosition /= esaCount;
	
	for(auto &elem: birdList){
		if(this == &elem) continue;
		double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));
		if(distance < birdRange){
			birdCount ++;
			birdPosition += elem.position;
		}
	}
	if(birdCount != 0) birdPosition /= birdCount;

	for(auto &elem: takaList){
		double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));
		if(distance < takaRange){
			takaCount ++;
			takaPosition += elem.position;
		}
	}
	if(takaCount != 0) takaPosition /= takaCount;

	if(position.x > 1) position.x -= 2;
	if(position.x < -1) position.x -= -2;
	if(position.y > 1) position.y -= 2;
	if(position.y < -1) position.y -= -2;

}

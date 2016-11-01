#include "taka.h"
#include "bird.h"
#include "esa.h"
#include "MODEL.h"
#include "CONST.h"
#include <random>



taka::taka(){
	position	= Position();
	direction	= rand()%int(M_PI*200)/100.0 - M_PI;
	life		= rand()%1000/10;
	color		= Color(life/100, 0.1, 0.1);
}

taka::taka(Position pos){
	position	= pos;
	direction	= rand()%int(M_PI*200)/100.0 - M_PI;
	life		= rand()%1000/10;
	color		= Color(life/100, 0.1, 0.1);
}

void taka::move(){

	if(true){
		double rule1birdCount = 0;
		double rule1centerX = 0;
		double rule1centerY = 0;
		double nextStepX = 0;
		double nextStepY = 0;
		
		for(auto &elem: birdList){
			double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));

			if(distance < _enemy1Distance_){
				rule1birdCount ++;
				rule1centerX	+= elem.position.x;
				rule1centerY	+= elem.position.y;
			}

			if(distance < 0.01){
				for(int i = 0; i < birdList.size(); i++){
					if(&elem == &birdList[i]){
						life += elem.life/10;
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

	position.x += cos(direction)*life/10000;
	position.y += sin(direction)*life/10000;

	if(position.x > 1) position.x -= 2;
	if(position.x < -1) position.x -= -2;
	if(position.y > 1) position.y -= 2;
	if(position.y < -1) position.y -= -2;

	if(life > 100){
		takaList.push_back(taka(position));
		life /= 2;
	}

	life -= 0.01;
	if(life < 0.01){
		for(int i = 0; i < takaList.size(); i++){
			if(this == &takaList[i]){
				esaList.push_back(esa(position));
				takaList.erase(takaList.begin() + i);
				break;
			}
		}
	}

}

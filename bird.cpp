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
	double rule5distance = 100;
	double rule5X = 0;
	double rule5Y= 0;

	double nextStepX = 0;
	double nextStepY = 0;

	for(auto &elem: esaList){
		double distance = sqrt( pow(position.x - elem.position.x, 2) + pow(position.y - elem.position.y, 2));
		if(distance < _rule5Distance_){
			if(distance < rule5distance){
				rule5distance = distance;
				rule5X = elem.position.x;
				rule5Y = elem.position.y;
			}
		}

		if(distance < 0.01){
			life += elem.ate();
		}
	}
	
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
			rule3centerX	+= cos(elem.direction);
			rule3centerY	+= sin(elem.direction);
		}

		if(distance < 0.01){
			nextStepX += rand()%2000/100.0 - 10;
			nextStepY += rand()%2000/100.0 - 10;
		}
	}

	for(auto &elem: takaList){
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

	if(rule5distance != 100){
		nextStepX += (rule5X - position.x) * _rule5Effect_;
		nextStepY += (rule5Y - position.y) * _rule5Effect_;
	}

	nextStepX += cos(direction) * _defaultEffect_;
	nextStepY += sin(direction) * _defaultEffect_;

	nextStepX += (rand()%200/100.0 - 1) * _randomEffect_;
	nextStepY += (rand()%200/100.0 - 1) * _randomEffect_;

	direction = atan2(nextStepY, nextStepX);

	position.x += cos(direction)*speed/100;
	position.y += sin(direction)*speed/100;

	if(position.x > 1) position.x -= 2;
	if(position.x < -1) position.x -= -2;
	if(position.y > 1) position.y -= 2;
	if(position.y < -1) position.y -= -2;

	if(life > 100){
		birdList.push_back(bird(position));
		life /= 2;
	}

	life -= 0.01;
	if(life < 0.01){
		for(int i = 0; i < birdList.size(); i++){
			if(this == &birdList[i]){
				birdList.erase(birdList.begin() + i);
				break;
			}
		}
	}


}

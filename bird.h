#ifndef BIRD_H 
#define BIRD_H

#include "MODEL.h"
#include <vector>

class bird{
	public:


		Position	position;
		double		direction;	//0.0 to 360.0
		double		speed;		//0.0 to 1.0
		double		life;
		Color		color;

		double		esaRange;
		double		birdRange;
		double		takaRange;

		//初期化
		bird();
		bird(Position pos);
		void move();
};

std::vector<bird> birdList;

#endif

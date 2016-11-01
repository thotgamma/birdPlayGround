#ifndef TAKA_H
#define TAKA_H

#include "MODEL.h"
#include <vector>

class taka{
	public:
		Position	position;
		double		direction;	//0.0 to 360.0
		double		life;
		Color		color;

		//初期化
		taka();
		taka(Position pos);
		void move();
};

std::vector<taka> takaList;

#endif

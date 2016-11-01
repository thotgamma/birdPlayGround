#ifndef ESA_H 
#define ESA_H

#include "MODEL.h"
#include <vector>

class esa{
	public:
		Position	position;
		Color		color;
		double		quantity;

		//初期化
		esa();
		esa(Position pos);
		double ate();
};

std::vector<esa> esaList;

#endif

#ifndef MODEL_H
#define MODEL_H

#include <random>

struct Color{
	double r;
	double g;
	double b;

	Color(){
		r = rand()%70/100.0 + 0.2;
		g = rand()%70/100.0 + 0.2;
		b = rand()%70/100.0 + 0.2;
	}

	Color(double r, double g, double b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

struct Position{
	double x;
	double y;

	Position(){
		x = rand()%200/100.0 - 1;
		y = rand()%200/100.0 - 1;
	}

	Position(double x, double y){
		this->x = x;
		this->y = y;
	}
};


#endif

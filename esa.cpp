#include "esa.h"
#include "MODEL.h"
#include "CONST.h"


esa::esa(){
	position	= Position();
	quantity	= rand()%100;
	color = Color(0.3,quantity/100,0.3);
}

esa::esa(Position pos){
	position	= pos;
	quantity	= rand()%100;
	color = Color(0.3,quantity/100,0.3);
}

double esa::ate(){
	double ate = rand()%100/10;
	if(quantity < ate) ate = quantity;
	quantity -= ate;
	color = Color(0.3,quantity/100,0.3);
	if(quantity < 0.01){
		for(int i = 0; i < esaList.size(); i++){
			if(this == &esaList[i]){
				esaList.erase(esaList.begin() + i);
				break;
			}
		}
	}
	
	return ate;
}


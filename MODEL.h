#ifndef MODEL_H
#define MODEL_H

#include <random>
#include <vector>

struct Edge;
struct Node;
struct Brain;
struct Color;
struct Position;

struct Edge{
	double weight;
	Node* nextNode;
	Edge(){
	}
	Edge(Node* nextNode){
		this->weight = 0;
		this->nextNode = nextNode;
	}

	Edge(Node* nextNode, double weight){
		this->weight = weight;
		this->nextNode = nextNode;
	}
};

struct Node{
	double reg;
	std::vector<Edge> edges;
	Node(){
	}

	void calc(){
		for(auto &elem: edges){
			elem.nextNode->reg += elem.weight * reg;
		}
	}
};

struct Brain{
	std::vector<Node> inputLayer;
	std::vector<Node> interLayer;
	std::vector<Node> outputLayer;

	void createNet(){
		for(auto &inputElem: inputLayer){
			for(auto &interElem: inputLayer){
				inputElem.edges.push_back(Edge(&interElem));
			}
		}

		for(auto &interElem: interLayer){
			for(auto &outputElem: outputLayer){
				interElem.edges.push_back(Edge(&outputElem));
			}
		}
	}

	void calc(){
		for(auto &inputElem: inputLayer){
			inputElem.calc();
		}
		for(auto &interElem: interLayer){
			interElem.calc();
		}
	}

	void reset(){
		for(auto &inputElem: inputLayer){
			inputElem.reg = 0;
		}
		for(auto &interElem: interLayer){
			interElem.reg = 0;
		}
		for(auto &outputElem: outputLayer){
			outputElem.reg = 0;
		}
	}
};

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


	Position operator+(Position p){
		return Position(x + p.x, y + p.y);
	}

	Position operator-(Position p){
		return Position(x - p.x, y - p.y);
	}

	Position operator+=(Position p){
		return Position(x += p.x, y += p.y);
	}

	Position operator-=(Position p){
		return Position(x -= p.x, y -= p.y);
	}

	Position operator/(int i){
		return Position(x / i, y / i);
	}

	Position operator/=(int i){
		return Position(x /= i, y /= i);
	}

};


#endif

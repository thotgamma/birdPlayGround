const int _NumberOfBird_		= 200;

const double _rule1Distance_	= 0.1;
const double _rule1Effect_		= 3;

const double _rule2Distance_	= 0.03;
const double _rule2Effect_		= 20;

const double _rule3Distance_	= 0.08;
const double _rule3Effect_		= 4;

//const double _rule4Distance_	= 0.3;
const double _rule4Distance_	= 0.2;
const double _rule4Effect_		= 10;

const double _speedEffect_		= 0.1;
const double _colorEffect_		= 0.1;

const double _defaultEffect_	= 1;
const double _randomEffect_		= 0.3;

const double _enemy1Distance_ = 0.3;
const double _enemy1Effect_ = 0.8;

int main(int argc, char *argv[]);
class bird{
	public:
		//鳥のプロパティ
		struct S_position{
			double x;		//-1.0 to 1.0
			double y;		//-1.0 to 1.0
		} position;

		double direction;	//0.0 to 360.0
		double speed;		//0.0 to 1.0

		struct S_color{
			double r;		//0.0 to 1.0
			double g;		//0.0 to 1.0
			double b;		//0.0 to 1.0
		} color;

		//初期化
		bird();

		//移動
		void move();

};

class enemy:public bird{
	public:
	void move();
};

//画面上の鳥をひとまとめに管理する
std::vector<bird> birdList;
std::vector<enemy> enemyList;

void display(void);
void timer(int value);
void buildDisplayList();

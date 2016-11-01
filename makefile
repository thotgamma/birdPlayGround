make:
	g++ -framework OpenGL -framework GLUT -framework Foundation -Wno-deprecated -std=c++11 main.cpp -o birdSim 

run:
	./oceanSim

quick:
	g++ -framework OpenGL -framework GLUT -framework Foundation -Wno-deprecated -std=c++11 main.cpp -o birdSim
	./oceanSim

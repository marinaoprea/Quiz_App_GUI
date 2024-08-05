build:
	g++ *.cpp `wx-config --libs --cxxflags` -o app

run:
	./app

clean:
	clear && rm app
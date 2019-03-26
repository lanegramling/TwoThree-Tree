lab5: main.o
	g++ -std=c++11 -g -Wall main.o -o lab5
main.o: main.cpp TwoThreeTree.h TwoThreeTree.hpp TwoThreeNode.h TwoThreeNode.hpp
	g++ -std=c++11 -g -Wall -c main.cpp
clean:
	rm *.o lab5

flags = -Wall -g -std=c++14

all: chen_p1

run: chen_p1
	./chen_p1 p1_sample1.txt 0011 100

chen_p1: chen_p1.o
	g++ $(flags) chen_p1.o -o chen_p1

chen_p1.o: chen_p1.cpp
	g++ -c $(flags) chen_p1.cpp -o chen_p1.o

clean:
	rm *.o chen_p1

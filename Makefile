CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2


all: main

clean:
	rm -f main.exe *.o

main: main.o
	$(CXX) $^ -o $@


## Dependencies

main.o: main.cpp

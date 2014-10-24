COMPILER = g++
OPT = -std=c++11
all: mbp
mbp: main.o Algorithm.o Graph.o DataStructure.o
	$(COMPILER) $(OPT) main.o Algorithm.o Graph.o DataStructure.o
main.o: main.cpp DataStructure.h Heap.h Graph.h Algorithm.h
	$(COMPILER) $(OPT) main.cpp -c
Algorithm.o: Algorithm.h Graph.h Utils.h
	$(COMPILER) $(OPT) Algorithm.cpp -c
Graph.o: Graph.h Utils.h
	$(COMPILER) $(OPT) Graph.cpp -c
DataStructure.o: DataStructure.h
	$(COMPILER) $(OPT) DataStructure.cpp -c

clean:
	rm *.o 

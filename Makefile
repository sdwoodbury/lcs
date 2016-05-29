all: lcs.o
	g++ -Wall lcs.o -o Driver.out -fopenmp -std=c++11
lcs.o: lcs.cpp
	g++ -Wall -c lcs.cpp -fopenmp -std=c++11

run:
	./Driver.out sequences
clean:
	rm -f *.o *~ Driver.out

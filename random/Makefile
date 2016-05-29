all: rand.o
	g++ -Wall rand.o -o driver.out
rand.o: rand.cpp
	g++ -Wall -c rand.cpp
run:
	./driver.out 10000
clean:
	rm -f driver.out *.o *~

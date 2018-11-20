all: hello
hello: main.o
	g++ main.o -o ncalc
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -rf *o ncalc
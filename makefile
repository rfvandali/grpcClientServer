
all: server

server: main.o
	g++ -g -o server main.o

main.o: main.cpp
	g++ -g -c main.cpp

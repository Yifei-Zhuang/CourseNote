CC = clang++
CFLAGS = -g -Wall -O2 --std=c++20 

all: hw6
hw6: main.cpp Vector.hpp Vector.cpp main.o Vector.o
	$(CC) $(CFLAGS) main.o Vector.o -o hw6
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
Vector.o: Vector.cpp Vector.hpp
	$(CC) $(CFLAGS) -c Vector.cpp

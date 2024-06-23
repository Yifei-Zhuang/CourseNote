all: fraction
CC=clang++
CFLAGS= -g -Wall -O2 --std=c++20
fraction: main.o main.cpp fraction.cpp fraction.hpp fraction.o
	${CC} ${CFLAGS} main.o fraction.o -o fraction
main.o: fraction.cpp fraction.hpp main.cpp
	${CC} ${CFLAGS} main.cpp -c 
fraction.o: fraction.cpp fraction.hpp
	${CC} ${CFLAGS} fraction.cpp -c 	

.PHONY: clean
clean: 
	rm -f *.o
CC = clang++
CFLAGS = -Wall -g -O2 --std=c++20

main: main.cpp main.o 
	$(CC) $(CFLAGS) main.o -o main

main.o: main.cpp assemble.cpp disAssembler.cpp disAssembler.hpp assemble.hpp utils.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o main
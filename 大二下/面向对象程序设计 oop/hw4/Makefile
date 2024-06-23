all: pdadd pdremove pdshow pdlist
CC = g++
CFLAGS = --std=c++20 -Wall -g
pdadd : pdadd.cpp Entity.cpp Entity.hpp pdadd.o Entity.o utils.o
	$(CC) $(CFLAGS) pdadd.o Entity.o  -o pdadd
pdremove: pdremove.cpp Entity.cpp Entity.hpp pdremove.o Entity.o utils.o
	$(CC) $(CFLAGS) pdremove.o Entity.o -o pdremove
pdshow: pdshow.cpp Entity.cpp Entity.hpp pdshow.o Entity.o utils.o
	$(CC) $(CFLAGS) pdshow.o Entity.o -o pdshow
pdlist: pdlist.cpp Entity.cpp Entity.hpp pdlist.o Entity.o utils.o
	$(CC) $(CFLAGS) pdlist.o Entity.o -o pdlist
Entity.o :  Entity.cpp Entity.hpp
	$(CC) $(CFLAGS) -c Entity.cpp 
pdadd.o :  pdadd.cpp Entity.cpp Entity.hpp Entity.o
	$(CC) $(CFLAGS) -c pdadd.cpp 
pdremove.o : pdremove.cpp Entity.cpp Entity.hpp Entity.o
	$(CC) $(CFLAGS) -c pdremove.cpp 
pdshow.o : pdshow.cpp Entity.cpp Entity.hpp Entity.o
	$(CC) $(CFLAGS) -c pdshow.cpp 
pdlist.o : pdlist.cpp Entity.cpp Entity.hpp Entity.o
	$(CC) $(CFLAGS) -c pdlist.cpp 
utils.o : utils.cpp Entity.cpp Entity.hpp Entity.o
	$(CC) $(CFLAGS) -c utils.cpp 

.PHONY: clean
clean:
	rm -f *.o pdadd pdremove pdshow pdlist
all : DH bigInteger
.PHONY : all
CFLAGS = -g -O2 -Wall --std=c++17
OBJS1 = bigInteger.o
OBJS2 = DH.o
CXX = g++

bigInteger : $(OBJS1)
	$(CXX) -o bigInteger $(OBJS1) $(CFLAGS)

DH :$(OBJS2)
	$(CXX) -o DH $(OBJS2) $(CFLAGS)

$(OBJS1):%.o:%.cpp
	$(CXX) -c $< $(CFLAGS) -o $@

$(OBJS2):%.o:%.cpp
	$(CXX) -c $< $(CFLAGS) -o $@

.PHONY:clean
clean:
	-$(RM) DH bigInteger $(OBJS1) $(OBJS2)

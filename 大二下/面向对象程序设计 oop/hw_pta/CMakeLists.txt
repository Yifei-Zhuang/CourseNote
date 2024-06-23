PROJECT(HW1)

SET(SRC_LIST hw1.cpp)
set(CMAKE_CXX_FLAGS   "--std=c++14 -g -Wall -O2")    
ADD_EXECUTABLE(hw1 ${SRC_LIST})
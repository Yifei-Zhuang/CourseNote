PROJECT(HW2)

SET(SRC_LIST hw2.cpp)
set(CMAKE_CXX_FLAGS   "--std=c++17 -g -Wall -O2")    
ADD_EXECUTABLE(hw2 ${SRC_LIST})
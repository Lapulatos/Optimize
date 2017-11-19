CXX = g++
CXXFLAGS = -std=c++11 -O3 -I../include -I/usr/local/include/eigen3

OBJ = newton.o sucfal.o gldseg.o sptdst.o inpoltn.o exception.o main.o
SRC = $(OBJ:.o=.cpp)
TARGET = test

all : $(TARGET)

$(OBJ) : $(SRC)
	$(CXX) $(CXXFLAGS) -c $^

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean :
	rm -f $(OBJ) $(TARGET)


CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11
TARGET = ACOColoring
SRC = ACOColoring.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

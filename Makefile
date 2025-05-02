CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11

TARGETS = ACOColoring EarlyGreedACOColoring

all: $(TARGETS)

ACOColoring: ACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o ACOColoring ACOColoring.cpp

EarlyGreedACOColoring: GreedyStartACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOColoring GreedyStartACOColoring.cpp

clean:
	rm -f $(TARGETS)
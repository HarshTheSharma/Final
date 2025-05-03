CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11

TARGETS = ACOColoring EarlyGreedACOColoring GreedyStartACOMultiThreaded

all: $(TARGETS)

ACOColoring: ACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o ACOColoring ACOColoring.cpp

EarlyGreedACOColoring: GreedyStartACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOColoring GreedyStartACOColoring.cpp

GreedyStartACOMultiThreaded: GreedyStartACOMultiThreaded.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOMultiThreaded GreedyStartACOMultiThreaded.cpp

clean:
	rm -f $(TARGETS)
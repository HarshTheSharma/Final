CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11

TARGETS = ACOColoring EarlyGreedACOColoring ACOMultiThreaded

all: $(TARGETS)

ACOColoring: ACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o ACOColoring ACOColoring.cpp

EarlyGreedACOColoring: GreedyStartACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOColoring GreedyStartACOColoring.cpp

ACOMultiThreaded: ACOMultiThreaded.cpp
	$(CXX) $(CXXFLAGS) -o ACOMultiThreaded ACOMultiThreaded.cpp

clean:
	rm -f $(TARGETS)
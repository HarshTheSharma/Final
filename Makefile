CXX = g++
CXXFLAGS = -O2 -std=c++11

TARGETS = ACOColoring EarlyGreedACOColoring GreedyStartACOMultiThreaded verify

all: $(TARGETS)

verify: verify.cpp
	$(CXX) $(CXXFLAGS) -o verify verify.cpp

ACOColoring: ACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o ACOColoring ACOColoring.cpp

EarlyGreedACOColoring: GreedyStartACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOColoring GreedyStartACOColoring.cpp

GreedyStartACOMultiThreaded: GreedyStartACOMultiThreaded.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOMultiThreaded GreedyStartACOMultiThreaded.cpp

clean:
	rm -f $(TARGETS)
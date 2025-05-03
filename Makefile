CXX = g++
CXXFLAGS = -O2 -std=c++11

TARGETS = ACOColoring GreedyStartACOColoring verify

all: $(TARGETS)

verify: verify.cpp
	$(CXX) $(CXXFLAGS) -o verify verify.cpp

ACOColoring: ACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o ACOColoring ACOColoring.cpp

GreedyStartACOColoring: GreedyStartACOColoring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOColoring GreedyStartACOColoring.cpp

clean:
	rm -f $(TARGETS)
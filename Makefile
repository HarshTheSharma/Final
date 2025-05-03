CXX = g++
CXXFLAGS = -O2 -std=c++11

TARGETS = ACOloring GreedyStartACOloring verify

all: $(TARGETS)

verify: verify.cpp
	$(CXX) $(CXXFLAGS) -o verify verify.cpp

ACOloring: ACOloring.cpp
	$(CXX) $(CXXFLAGS) -o ACOloring ACOloring.cpp

GreedyStartACOloring: GreedyStartACOloring.cpp
	$(CXX) $(CXXFLAGS) -o GreedyStartACOloring GreedyStartACOloring.cpp

clean:
	rm -f $(TARGETS)
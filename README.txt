To the run the script with tests:
    ensure verify.cpp, runTests, and ACOloring.cpp are present
    remake the program with `make clean` and `make`
    run the normal tests with `./runTests ACOloring tests/`
    run the normal large tests (which take forever) with `./runTests ACOloring largeTests/`

To observe random output behavior, adjust the ALPHA value in ACOloring.cpp as stated in the comments and observe Test1's output with multiple runs.

The runTests script is modified to compare the first line of the ACOloring output with the output test and use the rest of  
the output alongside verify.cpp in order to make sure the result reported by the function aligns with the coloring it provides.

To run ACOloring on it's own:
    Enter n m c           (nodeCount, edgeCount, maxColorCount)
          u v             
          u v...          (the edges of the graph)



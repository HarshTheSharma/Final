#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

vector<pair<int, int>> graph;

int isValidColoring(const vector<int>& coloring) {
    int conflicts = 0;
    for (pair<int, int> edge : graph) {
        if (coloring[edge.first] == coloring[edge.second]) conflicts++;
    }
    return conflicts;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./verify <input_file> <output_to_test>\n";
        return 2;
    }

    string inputFile = argv[1];
    string testFile = argv[2];
    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Could not open input file: ";
        return 2;
    }

    int n, m, c, givenErrorCt, node, color;;
    fin >> n >> m >> c;
    graph.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        graph[i] = make_pair(u, v);
    }
    fin.close();
    fin.open(testFile);
    vector<int> coloring(n, -1);
    fin >> givenErrorCt;
    for (int i = 0; i < n; ++i) {
        if (!(fin >> node >> color)) {
            cerr << "bad input coloring input\n";
            return 2;
        }
        coloring[node] = color;
    }
    fin.close();
    if (givenErrorCt == isValidColoring(coloring)) {
        cout << "1\n"; // correct
        return 0;
    } else {
        cout << "0\n"; // they lied
        return 1;
    }
}

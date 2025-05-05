#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>

using namespace std;

#define ANT_COUNT 50
#define ITERATIONS 100
#define ALPHA 0.7 // set to 1 to observe the algorithms random behavior when it comes to test 1
#define BETA 7
#define RHO 0.3
#define Q 100.0

int n, m, c;
vector<pair<int, int>> graph;
vector<vector<double>> pheromones;

double findConflicts(const vector<int>& coloring, int node = -1, int color = -1) {
    int conflicts = 0;
    // conflicts for the whole graph
    if (node == -1 || color == -1) {
        for (pair<int, int>& edge : graph) if (coloring[edge.first] == coloring[edge.second]) conflicts++;
    
    // conflicts after coloring a single node
    } else {
        for (pair<int, int>& edge : graph) {
            if ((edge.first == node && coloring[edge.second] == color) || (edge.second == node && coloring[edge.first] == color)) conflicts++;
        }
    }
    return conflicts;
}

int makeDecision(int node, const vector<int>& coloring) {
    vector<double> probs(c);
    double sum = 0.0;

    for (int color = 0; color < c; color++) {
        //pheromone information
        double pheromone = pheromones[node][color];
        //heuristic information
        double heuristic =  1.0 / (1 + (findConflicts(coloring, node, color)));
        //building the probability list
        probs[color] = pow(pheromone, ALPHA) * pow(heuristic, BETA);
        sum += probs[color];
    }

    // Select color based on probabilities
    double randVal = (double)rand() / RAND_MAX;
    for (int color = 0; color < c; color++) {
        probs[color] /= sum;                    // Normalize probabilities
        if (randVal <= probs[color]) return color;
        randVal -= probs[color];
    }
    return c - 1;   // Fallback to the last color if all else fails
}

void ACOloring(vector<int>& coloring, int& conflicts) {
    // Main Ant Colony Optimization loop
    for (int it = 0; it < ITERATIONS; it++) {
        for (int ant = 0; ant < ANT_COUNT; ant++) {
            vector<int> antColoring(n, -1);

            // Make Decicions until all nodes are colored and find conflicts
            for (int node = 0; node < n; node++) antColoring[node] = makeDecision(node, antColoring);
            int antConflicts = findConflicts(antColoring);

            // Update the best coloring found so far
            if (antConflicts < conflicts) {
                conflicts = antConflicts;
                coloring = antColoring;
                if (conflicts == 0) break; // Stop if a perfect coloring is found
            }

            // Reinforce pheromones based on the ant's path
            for (int i = 0; i < n; i++) pheromones[i][antColoring[i]] += Q / (1.0 + antConflicts);
        }
        
        // Evaporate pheromones
        for (int i = 0; i < n; i++) for (int color = 0; color < c; color++) pheromones[i][color] *= (1.0 - RHO);
    }
}

int main(int argc, char* argv[]) {
    cin >> n >> m >> c;
    graph.resize(m);
    pheromones.assign(n, vector<double>(c, 1.0));
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        graph[i] = make_pair(u, v);
    }

    srand(time(0));
    vector<int> coloring(n);
    int conflicts = INT_MAX;

    ACOloring(coloring, conflicts);

    cout << conflicts << "\n";
    for (int i = 0; i < n; i++) cout << i << " " << coloring[i] << "\n";
    return 0;
}

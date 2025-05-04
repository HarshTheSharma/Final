#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>

using namespace std;

#define ANT_COUNT 100
#define ITERATIONS 1000
#define ALPHA 1.0
#define BETA 5.0
#define RHO 0.1
#define Q 100.0

int n, m, c;
vector<pair<int, int>> graph;
vector<vector<double>> pheromones;

double findConflicts(const vector<int>& coloring, int node = -1, int color = -1) {
    int conflicts = 0;
    // conflicts for the whole graph
    if (node == -1 || color == -1) {
        for (pair<int, int>& edge : graph) if (coloring[edge.first] == coloring[edge.second]) conflicts++;
        return conflicts;
    
    // conflicts after coloring a single node
    } else {
        for (pair<int, int>& edge : graph) {
            int u = edge.first, v = edge.second;
            if ((u == node && coloring[v] == color) || (v == node && coloring[u] == color))
                conflicts++;
        }
        return 1.0 / (1 + conflicts);
    }
}

void greedyColoring(vector<int>& coloring, int& conflicts) {
    coloring.assign(n, -1);
    vector<vector<int>> adj(n);
    conflicts = 0;
    // adjacency list
    for (pair<int, int>& edge : graph) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    for (int node = 0; node < n; node++) {
        vector<bool> used(c, 0); // Colors used by neighbors
        // Mark colors used by neighbors
        for (int neighbor : adj[node]) if (coloring[neighbor] != -1 && coloring[neighbor] < c) used[coloring[neighbor]] = 1;

        bool assigned = 0;
        for (int color = 0; color < c; color++) {
            if (!used[color]) {
                coloring[node] = color;
                assigned = true;
                break;
            }
        }

        // If all colors are used, assign a random color
        if (!assigned) coloring[node] = rand() % c;
    }

    // Add conflicts 
    conflicts += findConflicts(coloring);
}

int makeDecision(int node, const vector<int>& coloring) {
    vector<double> probs(c);
    double sum = 0.0;

    for (int color = 0; color < c; color++) {
        //pheromone information
        double tau = pheromones[node][color];
        //heuristic information
        double eta = findConflicts(coloring, node, color);
        //building the probability distribution
        probs[color] = pow(tau, ALPHA) * pow(eta, BETA);
        sum += probs[color];
    }

    double randVal = (double)rand() / INT_MAX * sum;

    for (int color = 0; color < c; color++) {
        if (randVal <= probs[color]) return color;
        randVal -= probs[color];
    }
    return c - 1;
}

void ACOColoring(vector<int>& coloring, int& conflicts) {
    // Main Ant Colony Optimization loop
    for (int it = 0; it < ITERATIONS; it++) {
        for (int ant = 0; ant < ANT_COUNT; ant++) {
            vector<int> runColoring(n, -1);

            for (int node = 0; node < n; node++) {
                runColoring[node] = makeDecision(node, runColoring);
            }

            int runConflicts = findConflicts(runColoring);

            if (runConflicts < conflicts) {
                conflicts = runConflicts;
                coloring = runColoring;
            }
            // Reinforce pheromones based on the ant's path
            for (int i = 0; i < n; i++) pheromones[i][runColoring[i]] += Q / (1.0 + conflicts);
        }
        
        // Evaporate pheromones
        for (int i = 0; i < n; i++) for (int color = 0; color < c; color++) pheromones[i][color] *= (1.0 - RHO);
        if (conflicts == 0) break; // Stop if no conflicts
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
    greedyColoring(coloring, conflicts);
    ACOColoring(coloring, conflicts);

    cout << conflicts << "\n";
    for (int i = 0; i < n; i++) cout << i << " " << coloring[i] << "\n";
    return 0;
}

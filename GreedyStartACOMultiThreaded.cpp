#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <pthread.h>

using namespace std;

#define ITERATIONS 2000
#define ALPHA 1.0
#define BETA 2.0
#define RHO 0.1
#define Q 100.0

int n, m, c, ANT_COUNT = 0;
vector<pair<int, int>> graph;
vector<vector<double>> pheromones;
pthread_mutex_t pheromone_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t result_mutex = PTHREAD_MUTEX_INITIALIZER;

struct AntResult {
    vector<int> coloring;
    int conflicts = INT_MAX;
};

AntResult globalResult;

double findConflicts(const AntResult& result, int node = -1, int color = -1) {
    int conflicts = 0;
    if (node == -1 || color == -1) {
        for (pair<int, int>& edge : graph)
            if (result.coloring[edge.first] == result.coloring[edge.second])
                conflicts++;
        return conflicts;
    } else {
        for (pair<int, int>& edge : graph) {
            int u = edge.first, v = edge.second;
            if ((u == node && result.coloring[v] == color) || (v == node && result.coloring[u] == color))
                conflicts++;
        }
        return 1.0 / (1 + conflicts);
    }
}

void greedyColoring(AntResult& result) {
    result.coloring.assign(n, -1);
    vector<vector<int>> adj(n);
    for (pair<int, int>& edge : graph) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    for (int node = 0; node < n; ++node) {
        vector<bool> used(c, 0);
        for (int neighbor : adj[node])
            if (result.coloring[neighbor] != -1 && result.coloring[neighbor] < c)
                used[result.coloring[neighbor]] = 1;

        bool assigned = 0;
        for (int color = 0; color < c; ++color) {
            if (!used[color]) {
                result.coloring[node] = color;
                assigned = true;
                break;
            }
        }
        if (!assigned) result.coloring[node] = rand() % c;
    }
    result.conflicts = findConflicts(result);
}

int makeDecision(int node, const AntResult& result) {
    vector<double> probs(c);
    double sum = 0.0;

    for (int color = 0; color < c; color++) {
        double tau = pheromones[node][color];
        double eta = findConflicts(result, node, color);
        probs[color] = pow(tau, ALPHA) * pow(eta, BETA);
        sum += probs[color];
    }

    double randVal = (double)rand() / INT_MAX * sum;

    for (int color = 0; color < c; ++color) {
        if (randVal <= probs[color]) return color;
        randVal -= probs[color];
    }
    return c - 1;
}

void* runAnt(void* arg) {
    AntResult localResult;
    localResult.coloring.assign(n, -1);
    for (int node = 0; node < n; ++node)
        localResult.coloring[node] = makeDecision(node, localResult);

    localResult.conflicts = findConflicts(localResult);

    pthread_mutex_lock(&pheromone_mutex);
    for (int i = 0; i < n; ++i)
        pheromones[i][localResult.coloring[i]] += Q / (1.0 + localResult.conflicts);
    pthread_mutex_unlock(&pheromone_mutex);

    pthread_mutex_lock(&result_mutex);
    if (localResult.conflicts < globalResult.conflicts) {
        globalResult = localResult;
    }
    pthread_mutex_unlock(&result_mutex);

    return nullptr;
}

void ACOColoring(AntResult& result) {
    globalResult = result;

    for (int it = 0; it < ITERATIONS; ++it) {
        pthread_t threads[ANT_COUNT];

        for (int i = 0; i < ANT_COUNT; ++i)
            pthread_create(&threads[i], nullptr, runAnt, nullptr);

        for (int i = 0; i < ANT_COUNT; ++i)
            pthread_join(threads[i], nullptr);

        for (int i = 0; i < n; ++i)
            for (int color = 0; color < c; ++color)
                pheromones[i][color] *= (1.0 - RHO);
    }

    result = globalResult;
}

int main() {
    ANT_COUNT = sysconf(_SC_NPROCESSORS_ONLN);
    cin >> n >> m >> c;
    graph.resize(m);
    pheromones.assign(n, vector<double>(c, 1.0));
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph[i] = make_pair(u, v);
    }

    srand(time(0));

    AntResult result;
    greedyColoring(result);
    ACOColoring(result);

    cout << result.conflicts << "\n";
    for (int i = 0; i < n; ++i) cout << i << " " << result.coloring[i] << "\n";
    return 0;
}

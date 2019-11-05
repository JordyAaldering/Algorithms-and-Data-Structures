#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int vertexCount = 0;
std::vector<int>* graph;
std::vector<bool> visited;

int componentCount = 0;
std::vector<int>* components;
std::vector<std::pair<int, int>> componentRoots;

void addEdge(int c1, int c2) {
    graph[c1].push_back(c2);
    graph[c2].push_back(c1);
}

int createGraph(const std::string &filename) {
    std::cout << __func__ << std::endl;
    std::fstream fs("..\\samples\\" + filename + ".in");

    int edgeCount, c1, c2;
    fs >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    while (fs >> c1 >> c2) {
        addEdge(c1, c2);
    }

    fs = std::fstream("..\\samples\\" + filename + ".out");
    int expected;
    fs >> expected;
    return expected;
}

void dfs(int i) {
    components[componentCount].push_back(i);
    visited[i] = true;

    for (int j : graph[i]) {
        if (!visited[j]) {
            dfs(j);
        }
    }
}

void calculateConnectedComponents() {
    std::cout << __func__ << std::endl;
    components = new std::vector<int>[vertexCount];
    visited.resize(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            dfs(i);
            componentCount++;
        }
    }
}

std::pair<int, int> bfs(int s) {
    std::vector<int> distances(vertexCount);
    std::fill(distances.begin(), distances.end(), -1);
    distances[s] = 0;

    std::queue<int> queue;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                distances[i] = distances[s] + 1;
                queue.push(i);
            }
        }
    }

    std::pair<int, int> pair(0, distances[0]);
    for (int j = 1; j < vertexCount; j++) {
        if (distances[j] > pair.second) {
            pair = std::make_pair(j, distances[j]);
        }
    }

    return pair;
}

std::pair<int, int> bfs(int s, int maxDistance) {
    std::vector<int> distances(vertexCount);
    std::fill(distances.begin(), distances.end(), -1);
    distances[s] = 0;

    std::queue<int> queue;
    queue.push(s);
    bool loop = true;

    while (!queue.empty() && loop) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                distances[i] = distances[s] + 1;
                queue.push(i);

                if (distances[i] >= maxDistance) {
                    loop = false;
                    break;
                }
            }
        }
    }

    std::pair<int, int> pair(0, distances[0]);
    for (int j = 1; j < vertexCount; j++) {
        if (distances[j] > pair.second) {
            pair = std::make_pair(j, distances[j]);
        }
    }

    return pair;
}

void calculateComponentRootsByShortestPath() {
    std::cout << __func__ << std::endl;
    componentRoots.resize(componentCount);
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < componentCount; i++) {
        std::pair<int, int> from = bfs(components[i][0]);
        int distance = (int) from.second / 2;
        componentRoots[i] = bfs(from.first, distance);
    }
}

void connectComponentsToBiggest() {
    std::cout << __func__ << std::endl;

    int bestComponent = 0;
    for (int i = 1; i < componentCount; i++) {
        if (componentRoots[i].second > componentRoots[bestComponent].second) {
            bestComponent = i;
        }
    }

    for (int i = 0; i < componentCount; i++) {
        if (i != bestComponent) {
            addEdge(componentRoots[i].first, componentRoots[bestComponent].first);
        }
    }
}

int calculateLongestPath() {
    std::cout << __func__ << std::endl;
    int from = bfs(0).first;
    std::pair<int, int> to = bfs(from);
    return std::max(0, to.second - 1);
}

void printGraph() {
    for (int i = 0; i < vertexCount; i++) {
        std::cout << "Adjacency list of " << i << ": head";
        for (int j : graph[i]) {
            std::cout << " -> " << j;
        }
        std::cout << std::endl;
    }
}

int main() {
    int expected = createGraph("small_10");
    calculateConnectedComponents();
    calculateComponentRootsByShortestPath();
    connectComponentsToBiggest();

    //printGraph();

    int length = calculateLongestPath();
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl;

    return 0;
}

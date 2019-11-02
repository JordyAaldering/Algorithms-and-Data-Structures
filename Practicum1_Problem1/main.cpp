#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cassert>

int vertexCount = 0;
std::vector<int>* graph;
std::vector<bool> visited;

int componentCount = 0;
std::vector<int>* components;
std::vector<int> componentRoots;
std::vector<int> componentRootDepths;

void addEdge(int c1, int c2) {
    graph[c1].push_back(c2);
    graph[c2].push_back(c1);
}

void resetVisited() {
    std::fill(visited.begin(), visited.end(), false);
}

void createGraph(const std::string &filename) {
    std::cout << __func__ << std::endl;
    std::fstream fs("..\\samples\\" + filename + ".in");

    int edgeCount, c1, c2;
    fs >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    while (fs >> c1 >> c2) {
        addEdge(c1, c2);
    }
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

void connectedComponentDFS(int i) {
    components[componentCount].push_back(i);
    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = graph[i].begin(); j != graph[i].end(); j++) {
        if (!visited[*j]) {
            connectedComponentDFS(*j);
        }
    }
}

void calculateConnectedComponents() {
    std::cout << __func__ << std::endl;
    components = new std::vector<int>[vertexCount];
    visited.resize(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            connectedComponentDFS(i);
            componentCount++;
        }
    }
}

void calculateComponentRoots() {
    std::cout << __func__ << std::endl;
    componentRoots.resize(componentCount);

    for (int i = 0; i < componentCount; i++) {
        int bestRootIndex = -1;
        int bestRootSize = -1;

        for (int j : components[i]) {
            int currentSize = graph[j].size();
            if (currentSize > bestRootSize) {
                bestRootIndex = j;
                bestRootSize = currentSize;
            }
        }

        assert(bestRootIndex >= 0);
        assert(bestRootSize >= 0);
        componentRoots[i] = bestRootIndex; // == -1 ? components[i][0] : bestRootIndex;
    }
}

int depthDFS(int i, int depth) {
    int newBiggestDepth = -1;
    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = graph[i].begin(); j != graph[i].end(); j++) {
        if (!visited[*j]) {
            int nextDepth = depthDFS(*j, depth + 1);
            newBiggestDepth = std::max(newBiggestDepth, nextDepth);
        }
    }

    newBiggestDepth = std::max(newBiggestDepth, depth);
    assert(newBiggestDepth >= 0);
    return newBiggestDepth;
}

void calculateComponentRootDepths() {
    std::cout << __func__ << std::endl;
    componentRootDepths.resize(componentCount);
    resetVisited();

    for (int i = 0; i < componentCount; i++) {
        componentRootDepths[i] = depthDFS(componentRoots[i], 0);
    }
}

void connectComponents() {
    std::cout << __func__ << std::endl;
    int longestDepthIndex = -1;
    int longestDepthSize = -1;

    for (int i = 0; i < componentCount; i++) {
        if (componentRootDepths[i] > longestDepthSize) {
            longestDepthIndex = componentRoots[i];
            longestDepthSize = componentRootDepths[i];
        }
    }

    assert(longestDepthIndex >= 0);
    assert(longestDepthSize >= 0);

    for (int i = 0; i < componentCount; i++) {
        if (componentRoots[i] != longestDepthIndex) {
            addEdge(componentRoots[i], longestDepthIndex);
        }
    }
}

std::pair<int, int> bfs(int s) {
    std::vector<int> distances(vertexCount);
    std::fill(distances.begin(), distances.end(), -1);
    distances[s] = 0;

    std::queue<int> queue;
    queue.push(s);

    std::vector<int>::iterator i;
    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (i = graph[s].begin(); i != graph[s].end(); i++) {
            if (distances[*i] == -1) {
                distances[*i] = distances[s] + 1;
                queue.push(*i);
            }
        }
    }

    for (int j = 0; j < vertexCount; j++) {
        assert(distances[j] >= 0);
    }

    int nodeIndex = -1;
    int maxDistance = -1;

    for (int j = 0; j < vertexCount; j++) {
        if (distances[j] > maxDistance) {
            nodeIndex = j;
            maxDistance = distances[j];
        }
    }

    assert(nodeIndex >= 0);
    assert(maxDistance >= 0);

    return std::make_pair(nodeIndex, maxDistance);
}

int calculateLongestPath() {
    std::cout << __func__ << std::endl;
    std::pair<int, int> from, to;
    from = bfs(0);
    to = bfs(from.first);

    return std::max(0, to.second - 1);
}

int readExpected(const std::string &filename) {
    std::fstream fs("..\\samples\\" + filename + ".out");

    int expected;
    fs >> expected;
    return expected;
}

int main() {
    // failed: big_7, big_8, big_9, big_10
    // overflowed: big_3
    std::string filename = "big_10";

    createGraph(filename);
    calculateConnectedComponents();
    calculateComponentRoots();
    calculateComponentRootDepths();
    connectComponents();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl;

    return 0;
}

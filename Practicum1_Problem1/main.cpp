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

void calculateComponentRootsBySize() {
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
        componentRoots[i] = bestRootIndex;
    }
}

int depthDFS(int i, int depth) {
    int newBiggestDepth = -1;
    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = graph[i].begin(); j != graph[i].end(); j++) {
        if (!visited[*j]) {
            int currentDepth = depthDFS(*j, depth + 1);
            newBiggestDepth = std::max(newBiggestDepth, currentDepth);
        }
    }

    newBiggestDepth = std::max(newBiggestDepth, depth);
    assert(newBiggestDepth >= 0);
    return newBiggestDepth;
}

void calculateComponentRootsByMinDepth() {
    std::cout << __func__ << std::endl;
    componentRoots.resize(componentCount);
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < componentCount; i++) {
        int bestRootIndex = -1;
        int bestRootDepth = -1;

        for (int j : components[i]) {
            int currentDepth = depthDFS(j, 0);
            if (currentDepth < bestRootDepth || bestRootDepth == -1) {
                bestRootIndex = j;
                bestRootDepth = currentDepth;
            }
        }

        assert(bestRootIndex >= 0);
        assert(bestRootDepth >= 0);
        componentRoots[i] = bestRootIndex;
    }
}

void calculateComponentRootMaxDepths() {
    std::cout << __func__ << std::endl;
    componentRootDepths.resize(componentCount);
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < componentCount; i++) {
        componentRootDepths[i] = depthDFS(componentRoots[i], 0);
    }
}

void connectComponentsToBiggest() {
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

void connectComponentsToAll() {
    for (int i = 0; i < componentCount; i++) {
        for (int j = i + 1; j < componentCount; j++) {
            addEdge(componentRoots[i], componentRoots[j]);
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
    // All Incomplete!
    // RootsByMinDepth, ComponentsToBiggest: s11(+1), b7(+1), b8(+11), b9(+9), b10(+9)
    // RootsByMinDepth, ComponentsToAll: s3(-1), s5(-1), s9(+1), s11(+1), b5(+2), b6(+2), b7(+1), b8(+11)
    // RootsBySize, ComponentsToBiggest: b7, b8, b9, b10
    // RootsBySize, ComponentsToAll:
    // overflowed: big_3
    std::string filename = "big_10";

    createGraph(filename);
    calculateConnectedComponents();
    calculateComponentRootsByMinDepth();
    calculateComponentRootMaxDepths();
    connectComponentsToAll();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl;

    return 0;
}

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
std::vector<std::pair<int, int>> componentRoots;

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

void calculateComponentRootsByShortestPath() {
    std::cout << __func__ << std::endl;
    componentRoots.resize(componentCount);
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < componentCount; i++) {
        std::pair<int, int> bestRoot(-1, -1);

        for (int j : components[i]) {
            std::pair<int, int> root = bfs(j);

            if (root.second < bestRoot.second || bestRoot.second == -1) {
                bestRoot = root;
            }
        }

        assert(bestRoot.first >= 0);
        assert(bestRoot.second >= 0);

        componentRoots[i] = bestRoot;
    }
}

void connectComponentsToBiggest() {
    std::cout << __func__ << std::endl;

    int biggestComponent = 0;
    for (int i = 1; i < componentCount; i++) {
        if (componentRoots[i].second > componentRoots[biggestComponent].second) {
            biggestComponent = i;
        }
    }

    for (int i = 0; i < componentCount; i++) {
        if (i != biggestComponent) {
            addEdge(componentRoots[i].first, componentRoots[biggestComponent].first);
        }
    }
}

int calculateLongestPath() {
    std::cout << __func__ << std::endl;
    int from = bfs(0).first;
    std::pair<int, int> to = bfs(from);
    return std::max(0, to.second - 1);
}

int readExpected(const std::string &filename) {
    std::fstream fs("..\\samples\\" + filename + ".out");
    int expected;
    fs >> expected;
    return expected;
}

int main() {
    std::string filename = "small_7";

    createGraph(filename);
    calculateConnectedComponents();
    calculateComponentRootsByShortestPath();
    connectComponentsToBiggest();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl;

    return 0;
}

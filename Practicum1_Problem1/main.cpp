#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

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
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
}

void createGraph(const std::string &filename) {
    std::cout << "Creating Graph..." << std::endl;
    std::fstream fs("..\\samples\\" + filename + ".in");

    int edgeCount, c1, c2;
    fs >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    while (fs >> c1 >> c2) {
        addEdge(c1, c2);
    }
}

void ccsUtil(int i) {
    components[componentCount].push_back(i);
    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = graph[i].begin(); j != graph[i].end(); j++) {
        if (!visited[*j]) {
            ccsUtil(*j);
        }
    }
}

void calculateComponents() {
    std::cout << "Calculating Components..." << std::endl;
    components = new std::vector<int>[vertexCount];
    visited.resize(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            ccsUtil(i);
            componentCount++;
        }
    }
}

void calculateComponentRoots() {
    std::cout << "Calculating Component Roots..." << std::endl;
    componentRoots.resize(componentCount);

    for (int i = 0; i < componentCount; i++) {
        int bestRootIndex = -1;
        int bestRootSize = -1;

        for (int j : components[i]) {
            if (graph[j].size() >= bestRootSize) {
                bestRootIndex = j;
                bestRootSize = graph[j].size();
            }
        }

        componentRoots[i] = bestRootIndex == -1 ? components[i][0] : bestRootIndex;
    }
}

int depthUtil(int i, int depth) {
    int newBestDepth = -1;
    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = graph[i].begin(); j != graph[i].end(); j++) {
        if (!visited[*j]) {
            int nextDepth = depthUtil(*j, depth + 1);
            newBestDepth = std::max(newBestDepth, nextDepth);
        }
    }

    return std::max(depth, newBestDepth);
}

void calculateComponentRootDepths() {
    std::cout << "Calculating Component root depths..." << std::endl;
    componentRootDepths.resize(componentCount);
    resetVisited();

    for (int i = 0; i < componentCount; i++) {
        componentRootDepths[i] = depthUtil(componentRoots[i], 0);
    }
}

void connectComponents() {
    std::cout << "Connecting Components..." << std::endl;
    int longestDepthIndex = -1;
    int longestDepthSize = -1;

    for (int i = 0; i < componentCount; i++) {
        if (componentRootDepths[i] > longestDepthSize) {
            longestDepthIndex = componentRoots[i];
            longestDepthSize = componentRootDepths[i];
        }
    }

    for (int i = 0; i < componentCount; i++) {
        if (componentRoots[i] != longestDepthIndex) {
            addEdge(componentRoots[i], longestDepthIndex);
        }
    }
}

std::pair<int, int> bfs(int s) {
    std::vector<int> distances(vertexCount);
    std::queue<int> queue;
    std::vector<int>::iterator i;

    distances[s] = 0;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (i = graph[s].begin(); i != graph[s].end(); i++) {
            if (distances[*i] == 0) {
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

    return std::make_pair(nodeIndex, maxDistance);
}

int calculateLongestPath() {
    std::cout << "Calculating Longest Path..." << std::endl;
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
    // failed: small_2, small_9, big_5, big_7, big_8, big_9, big_10
    // overflowed: big_3
    std::string filename = "big_10";

    createGraph(filename);
    calculateComponents();
    calculateComponentRoots();
    calculateComponentRootDepths();
    connectComponents();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl;

    return 0;
}

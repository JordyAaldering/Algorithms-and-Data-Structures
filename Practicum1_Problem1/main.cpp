#include <iostream>
#include <fstream>
#include <vector>
#include <list>

std::vector<int> *graph;
int vertexCount = 0;
bool *visited;

std::vector<int> *components;
int componentCount = 0;
int *componentRoots;
int *componentRootDepths;

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
    std::fstream fs("..\\samples\\" + filename + ".in");

    int E, c1, c2;
    fs >> vertexCount >> E;
    while (fs >> c1 >> c2) {
        addEdge(c1, c2);
    }

    graph = new std::vector<int>[vertexCount];
    components = new std::vector<int>[vertexCount];
    visited = new bool[vertexCount];
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
    resetVisited();

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            ccsUtil(i);
            componentCount++;
        }
    }
}

void calculateComponentRoots() {
    componentRoots = new int[componentCount];

    for (int i = 0; i < componentCount; i++) {
        int bestRootIndex = 0;
        int bestRootSize = 0;

        for (int j : components[i]) {
            if (graph[j].size() >= bestRootSize) {
                bestRootIndex = j;
                bestRootSize = graph[j].size();
            }
        }

        componentRoots[i] = bestRootIndex;
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
    componentRootDepths = new int[componentCount];

    resetVisited();
    for (int i = 0; i < componentCount; i++) {
        componentRootDepths[i] = depthUtil(componentRoots[i], 0);
    }
}

void connectComponents() {
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
    int distances[vertexCount];
    std::list<int> queue;
    std::vector<int>::iterator i;

    distances[s] = 0;
    queue.push_back(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop_front();

        for (i = graph[s].begin(); i != graph[s].end(); i++) {
            if (distances[*i] == 0) {
                distances[*i] = distances[s] + 1;
                queue.push_back(*i);
            }
        }
    }

    int nodeIndex = 0;
    int maxDistance = 0;

    for (int j = 0; j < vertexCount; j++) {
        if (distances[j] > maxDistance) {
            nodeIndex = j;
            maxDistance = distances[j];
        }
    }

    return std::make_pair(nodeIndex, maxDistance);
}

int calculateLongestPath() {
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
    std::string filename = "big_1";

    createGraph(filename);
    calculateComponents();
    calculateComponentRoots();
    calculateComponentRootDepths();
    connectComponents();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << length << " " << expected << std::endl;

    return 0;
}

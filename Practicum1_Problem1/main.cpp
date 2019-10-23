#include <iostream>
#include <fstream>
#include <vector>
#include <list>

int V;
int CCCount = 0;

std::vector<int>* Graph;
std::vector<int>* CCS;

int* CCRoots;
int* CCRootDepths;
bool* visited;

void addEdge(int c1, int c2)
{
    Graph[c1].push_back(c2);
    Graph[c2].push_back(c1);
}

void resetVisited()
{
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
}

void ccsUtil(int i)
{
    CCS[CCCount].push_back(i);

    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = Graph[i].begin(); j != Graph[i].end(); j++) {
        if (!visited[*j]) {
            ccsUtil(*j);
        }
    }
}

int depthUtil(int i, int depth)
{
    int newBestDepth = -1;

    visited[i] = true;
    std::vector<int>::iterator j;

    for (j = Graph[i].begin(); j != Graph[i].end(); j++) {
        if (!visited[*j]) {
            int nextDepth = depthUtil(*j, depth + 1);
            newBestDepth = std::max(newBestDepth, nextDepth);
        }
    }

    return std::max(depth, newBestDepth);
}

std::pair<int, int> bfs(int s)
{
    int distances[V];
    std::list<int> queue;
    std::vector<int>::iterator i;

    distances[s] = 0;
    queue.push_back(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop_front();

        for (i = Graph[s].begin(); i != Graph[s].end(); i++) {
            if (distances[*i] == 0) {
                distances[*i] = distances[s] + 1;
                queue.push_back(*i);
            }
        }
    }

    int nodeIndex = 0;
    int maxDistance = 0;

    for (int j = 0; j < V; j++) {
        if (distances[j] > maxDistance) {
            nodeIndex = j;
            maxDistance = distances[j];
        }
    }

    return std::make_pair(nodeIndex, maxDistance);
}

void createGraph(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".in");

    int E, c1, c2;
    fs >> V >> E;

    while (fs >> c1 >> c2) {
        addEdge(c1, c2);
    }

    Graph = new std::vector<int>[V];
    CCS = new std::vector<int>[V];
    visited = new bool[V];
}

int readExpected(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".out");

    int expected;
    fs >> expected;
    return expected;
}

void calculateCCS()
{
    resetVisited();

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            ccsUtil(i);
            CCCount++;
        }
    }
}

void calculateCCRoots()
{
    CCRoots = new int[CCCount];

    for (int i = 0; i < CCCount; i++) {
        int bestRootIndex = 0;
        int bestRootSize = 0;

        for (int j : CCS[i]) {
            if (Graph[j].size() >= bestRootSize) {
                bestRootIndex = j;
                bestRootSize = Graph[j].size();
            }
        }

        CCRoots[i] = bestRootIndex;
    }
}

void calculateCCRootDepths()
{
    CCRootDepths = new int[CCCount];

    resetVisited();
    for (int i = 0; i < CCCount; i++) {
        CCRootDepths[i] = depthUtil(CCRoots[i], 0);
    }
}

void extendGraph()
{
    int longestDepthIndex = -1;
    int longestDepthSize = -1;

    for (int i = 0; i < CCCount; i++) {
        if (CCRootDepths[i] > longestDepthSize) {
            longestDepthIndex = CCRoots[i];
            longestDepthSize = CCRootDepths[i];
        }
    }

    for (int i = 0; i < CCCount; i++) {
        if (CCRoots[i] != longestDepthIndex) {
            addEdge(CCRoots[i], longestDepthIndex);
        }
    }
}

int calculateLongestPath()
{
    std::pair<int, int> from, to;
    from = bfs(0);
    to = bfs(from.first);

    return std::max(0, to.second - 1);
}

int main()
{
    std::string filename = "big_1";

    createGraph(filename);
    calculateCCS();
    calculateCCRoots();
    calculateCCRootDepths();
    extendGraph();

    int length = calculateLongestPath();
    int expected = readExpected(filename);
    std::cout << length << " " << expected << std::endl;

    return 0;
}

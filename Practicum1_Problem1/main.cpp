#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;

int vertexCount, edgeCount;
vector<int>* graph;
vector<bool> visited;
vector<pair<int, int>> roots;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

static pair<int, int> max(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second ? a : b;
}

int createGraph(const std::string &filename) {
    std::fstream fs("..\\samples\\" + filename + ".in");
    fs >> vertexCount >> edgeCount;
    graph = new vector<int>[vertexCount];

    int a, b;
    while (fs >> a >> b) {
        addEdge(a, b);
    }

    fs = std::fstream("..\\samples\\" + filename + ".out");
    int expected;
    fs >> expected;
    return expected;
}

void createGraph() {
    int a, b;
    for (int i = 0; i < edgeCount; i++) {
        std::cin >> a >> b;
        addEdge(a, b);
    }
}

pair<int, int> bfs(int s) {
    vector<int> distances(vertexCount, -1);
    distances[s] = 0;

    queue<int> queue;
    queue.push(s);

    pair<int, int> bestRoot(s, 0);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        visited[s] = true;

        for (int i : graph[s]) {
            visited[i] = true;

            if (distances[i] == -1) {
                pair<int, int> root(i, distances[s] + 1);
                distances[i] = root.second;
                queue.push(i);

                bestRoot = max(bestRoot, root);
            }
        }
    }

    return bestRoot;
}

pair<pair<int, int>, vector<int>> bfsCached(int s) {
    vector<int> distances(vertexCount, -1);
    distances[s] = 0;

    queue<int> queue;
    queue.push(s);

    vector<int> pred(vertexCount);
    pair<int, int> bestRoot(s, 0);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        visited[s] = true;

        for (int i : graph[s]) {
            visited[i] = true;

            if (distances[i] == -1) {
                pair<int, int> root(i, distances[s] + 1);
                distances[i] = root.second;
                pred[i] = s;
                queue.push(i);

                bestRoot = max(bestRoot, root);
            }
        }
    }

    return std::make_pair(bestRoot, pred);
}

int calculateRoots() {
    pair<int, int> bestRoot(0, 0);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i] && !graph[i].empty()) {
            auto t1 = bfs(graph[i][0]);
            auto res = bfsCached(t1.first);
            auto t2 = res.first;

            pair<int, int> root(t2.first, (int) t2.second / 2);
            for (int depth = 1; depth <= root.second; depth++) {
                root.first = res.second[root.first];
            }

            roots.push_back(root);
            bestRoot = max(bestRoot, root);
        }
    }

    return bestRoot.first;
}

void connectTrees(int bestRootIndex) {
    for (pair<int, int> root : roots) {
        if (root.first != bestRootIndex) {
            addEdge(root.first, bestRootIndex);
        }
    }
}

int calculateLongestPath(int bestRootIndex) {
    pair<int, int> t1 = bfs(bestRootIndex);
    pair<int, int> t2 = bfs(t1.first);
    return std::max(0, t2.second - 1);
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //std::cin >> vertexCount >> edgeCount;
    std::cout << createGraph("big_2") << " ";

    if (vertexCount <= 2) {
        std::cout << "0";
    }
    else if (edgeCount <= 1) {
        std::cout << "1";
    }
    else {
        //graph = new vector<int>[vertexCount];
        visited.resize(vertexCount);

        //createGraph();
        int bestRootIndex = calculateRoots();
        connectTrees(bestRootIndex);
        std::cout << calculateLongestPath(bestRootIndex);
    }

    return 0;
}

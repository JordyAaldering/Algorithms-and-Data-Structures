#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int vertexCount, edgeCount;
std::vector<int>* graph;

int treeCount;
std::vector<int>* trees;
std::vector<std::pair<int, int>> roots;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

int createGraph(const std::string &filename) {
    std::fstream fs("..\\samples\\" + filename + ".in");

    fs >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    int a, b;
    while (fs >> a >> b) {
        addEdge(a, b);
    }

    fs = std::fstream("..\\samples\\" + filename + ".out");
    int expected;
    fs >> expected;
    return expected;
}

void readStdin() {
    std::cin >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    int a, b;
    for (int i = 0; i < edgeCount; i++) {
        std::cin >> a >> b;
        addEdge(a, b);
    }
}

void dfs(int i, std::vector<bool>& visited) {
    trees[treeCount].push_back(i);
    visited[i] = true;

    for (int j : graph[i]) {
        if (!visited[j]) {
            dfs(j, visited);
        }
    }
}

/**
 * Finds separate trees by applying DFS.
 */
void calculateTrees() {
    trees = new std::vector<int>[vertexCount];
    std::vector<bool> visited(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            dfs(i, visited);
            treeCount++;
        }
    }
}

std::pair<int, int> bfs(int s) {
    std::vector<int> distances(vertexCount, -1);

    std::queue<int> queue;
    distances[s] = 0;
    queue.push(s);

    int bestIndex = s;

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                int distance = distances[s] + 1;
                distances[i] = distance;
                queue.push(i);

                if (distance > distances[bestIndex]) {
                    bestIndex = i;
                }
            }
        }
    }

    return std::make_pair(bestIndex, distances[bestIndex]);
}

std::pair<std::pair<int, int>, std::vector<int>> bfsCached(int s) {
    std::vector<int> distances(vertexCount, -1);
    std::vector<int> pred(vertexCount, -1);

    std::queue<int> queue;
    distances[s] = 0;
    queue.push(s);

    int bestIndex = s;

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                int distance = distances[s] + 1;
                distances[i] = distance;
                pred[i] = s;
                queue.push(i);

                if (distance > distances[bestIndex]) {
                    bestIndex = i;
                }
            }
        }
    }

    return std::make_pair(std::make_pair(bestIndex, distances[bestIndex]), pred);
}

void calculateRoots() {
    roots.resize(treeCount);

    for (int i = 0; i < treeCount; i++) {
        std::pair<int, int> t1 = bfs(trees[i][0]);
        auto res = bfsCached(t1.first);
        std::pair<int, int> t2 = res.first;

        int root = t2.first;
        int maxDepth = (int) t2.second / 2;
        for (int depth = 1; depth <= maxDepth; depth++) {
            root = res.second[root];
        }

        roots[i] = std::make_pair(root, maxDepth);
    }
}

void connectTrees() {
    int bestIndex = 0;
    for (int i = 1; i < treeCount; i++) {
        if (roots[i].second > roots[bestIndex].second) {
            bestIndex = i;
        }
    }

    for (int i = 0; i < treeCount; i++) {
        if (i != bestIndex) {
            addEdge(roots[i].first, roots[bestIndex].first);
        }
    }
}

int calculateLongestPath() {
    int fromIndex = bfs(0).first;
    int toDepth = bfs(fromIndex).second;
    return std::max(0, toDepth - 1);
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    readStdin();
    int length;

    if (vertexCount <= 2) {
        length = 0;
    }
    else if (edgeCount <= 1) {
        length = 1;
    }
    else {
        calculateTrees();
        calculateRoots();
        connectTrees();
        length = calculateLongestPath();
    }

    std::cout << length;
    return 0;
}

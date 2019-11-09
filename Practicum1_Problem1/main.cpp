#include <iostream>
//#include <fstream>
#include <utility>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair, std::make_pair;
using std::cin, std::cout;

int vertexCount, edgeCount;
vector<int>* graph;
vector<bool> visited;
vector<pair<int, int>> roots;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

/*int createGraph(const std::string &filename) {
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
}*/

void readStdin() {
    cin >> vertexCount >> edgeCount;
    graph = new vector<int>[vertexCount];

    int a, b;
    for (int i = 0; i < edgeCount; i++) {
        cin >> a >> b;
        addEdge(a, b);
    }
}

pair<pair<int, int>, vector<int>> bfs(int s) {
    vector<int> distances(vertexCount, -1);
    distances[s] = 0;

    queue<int> queue;
    queue.push(s);

    vector<int> pred(vertexCount, -1);
    pair<int, int> bestRoot(s, 0);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                int dist = distances[s] + 1;
                distances[i] = dist;
                if (dist > bestRoot.second) {
                    bestRoot = make_pair(i, dist);
                }

                queue.push(i);
                pred[i] = s;
            }

            visited[i] = true;
        }
    }

    return make_pair(bestRoot, pred);
}

pair<int, int> calculateRoots() {
    pair<int, int> bestRoot(0, 0);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i] && !graph[i].empty()) {
            pair<pair<int, int>, vector<int>> t1 = bfs(graph[i][0]);
            pair<pair<int, int>, vector<int>> t2 = bfs(t1.first.first);

            int root = t2.first.first;
            int maxDepth = (int) t2.first.second / 2;
            for (int depth = 1; depth <= maxDepth; depth++) {
                root = t2.second[root];
            }

            pair<int, int> p = make_pair(root, maxDepth);
            roots.push_back(p);
            if (p.second > bestRoot.second) {
                bestRoot = p;
            }
        }
    }

    return bestRoot;
}

void connectTrees(pair<int, int> bestRoot) {
    for (pair<int, int> root : roots) {
        if (root.first != bestRoot.first) {
            addEdge(root.first, bestRoot.first);
        }
    }
}

int calculateLongestPath() {
    int fromIndex = bfs(0).first.first;
    int toDepth = bfs(fromIndex).first.second;
    return std::max(0, toDepth - 1);
}

int main() {
    std::iostream::sync_with_stdio(false);
    cin.tie(nullptr);

    //cout << createGraph("big_10") << " ";
    readStdin();

    if (vertexCount <= 2) {
        cout << 0;
    }
    else if (edgeCount <= 1) {
        cout << 1;
    }
    else {
        visited.resize(vertexCount);
        pair<int, int> bestRoot = calculateRoots();
        connectTrees(bestRoot);
        cout << calculateLongestPath();
    }

    return 0;
}

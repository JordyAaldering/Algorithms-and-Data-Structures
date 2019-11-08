#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int vertexCount;
std::vector<int>* graph;
std::vector<bool> visited;

int componentCount;
std::vector<int>* trees;
std::vector<std::pair<int, int>> roots;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
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

void readStdin() {
    int edgeCount, a, b;
    std::cin >> vertexCount >> edgeCount;
    graph = new std::vector<int>[vertexCount];

    for (int i = 0; i < edgeCount; i++) {
        std::cin >> a >> b;
        addEdge(a, b);
    }
}

void dfs(int i) {
    trees[componentCount].push_back(i);
    visited[i] = true;

    for (int j : graph[i]) {
        if (!visited[j]) {
            dfs(j);
        }
    }
}

/**
 * Finds separate trees by applying DFS.
 */
void calculateTrees() {
    std::cout << __func__ << std::endl;

    trees = new std::vector<int>[vertexCount];
    visited.resize(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            dfs(i);
            componentCount++;
        }
    }
}

std::pair<int, int> bfs(int s, int maxDistance = -1) {
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
                if (maxDistance >= 0 && distances[i] >= maxDistance) {
                    return std::make_pair(i, distances[i]);
                }

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

/**
 * Calculates the roots of each tree by finding the node
 * with the shortest distance to all other nodes.
 */
void calculateRoots() {
    std::cout << __func__ << std::endl;

    roots.resize(componentCount);
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < componentCount; i++) {
        std::pair<int, int> from = bfs(trees[i][0]);
        int distance = (int) from.second / 2;
        roots[i] = bfs(from.first, distance);
    }
}

/**
 * Connects all trees by adding an edge from every
 * root to the root with the biggest depth.
 */
void connectTrees() {
    std::cout << __func__ << std::endl;

    int bestComponent = 0;
    for (int i = 1; i < componentCount; i++) {
        if (roots[i].second > roots[bestComponent].second) {
            bestComponent = i;
        }
    }

    for (int i = 0; i < componentCount; i++) {
        if (i != bestComponent) {
            addEdge(roots[i].first, roots[bestComponent].first);
        }
    }
}

/**
 * Calculates the longest simple path by applying BFS.
 */
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

void test(const std::string& filename) {
    int expected = createGraph(filename);
    calculateTrees();
    calculateRoots();
    connectTrees();

    //printGraph();

    int length = calculateLongestPath();
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl << std::endl;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string small[] = {"small_1", "small_2", "small_3", "small_4", "small_5", "small_6", "small_7", "small_8", "small_9", "small_10"};
    std::string big[] = {/*"big_1", "big_2", "big_3",*/ "big_4", "big_5", "big_6", "big_7", "big_8", /*"big_9", "big_10"*/};

    for (const std::string& s : big) {
        std::cout << s << std::endl;
        test(s);
        componentCount = 0;
    }

    return 0;
}

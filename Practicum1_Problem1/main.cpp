#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int vertexCount, edgeCount;
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

void calculateTreesDFS(int i) {
    trees[componentCount].push_back(i);
    visited[i] = true;

    for (int j : graph[i]) {
        if (!visited[j]) {
            calculateTreesDFS(j);
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
            calculateTreesDFS(i);
            componentCount++;
        }
    }
}

std::pair<int, int> bfs(int s, std::vector<int>& path) {
    std::vector<int> distances(vertexCount);
    std::fill(distances.begin(), distances.end(), -1);
    distances[s] = 0;

    std::queue<int> queue;
    queue.push(s);
    path.push_back(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop();

        for (int i : graph[s]) {
            if (distances[i] == -1) {
                distances[i] = distances[s] + 1;
                queue.push(i);
            }
        }
    }

    // return the pair with the highest distance
    int bestIndex = 0;
    for (int j = 1; j < vertexCount; j++) {
        if (distances[j] > distances[bestIndex]) {
            bestIndex = j;
        }
    }

    return std::make_pair(bestIndex, distances[bestIndex]);
}

/**
 * Calculates the roots of each tree by finding the node
 * with the shortest distance to all other nodes.
 */
void calculateRoots() {
    std::cout << __func__ << std::endl;

    roots.resize(componentCount);

    for (int i = 0; i < componentCount; i++) {
        int fromIndex = bfs(trees[i][0]).first;
        std::pair<int, int> to = bfs(fromIndex);

        int maxDepth = (int) to.second / 2;
        //roots[i] = ;
    }
}

/**
 * Connects all trees by adding an edge from every
 * root to the root with the biggest depth.
 */
void connectTrees() {
    std::cout << __func__ << std::endl;

    int bestIndex = 0;
    for (int i = 1; i < componentCount; i++) {
        if (roots[i].second > roots[bestIndex].second) {
            bestIndex = i;
        }
    }

    for (int i = 0; i < componentCount; i++) {
        if (i != bestIndex) {
            addEdge(roots[i].first, roots[bestIndex].first);
        }
    }
}

/**
 * Calculates the longest simple path by applying BFS twice.
 */
int calculateLongestPath() {
    std::cout << __func__ << std::endl;

    int fromIndex = bfs(0).first;
    int toDepth = bfs(fromIndex).second;
    return std::max(0, toDepth - 1);
}

int run(const std::string& filename) {
    std::cout << filename << std::endl;

    int expected = createGraph(filename);
    calculateTrees();
    calculateRoots();
    connectTrees();

    int length = calculateLongestPath();
    std::cout << "Done! Got: " << length << ", should be: " << expected << std::endl << std::endl;
    return length;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string small[] = {"small_1", "small_2", "small_3", "small_4", "small_5", "small_6", "small_7", "small_8", "small_9", "small_10"};
    std::string big[] = {/*"big_1", "big_2", "big_3",*/ "big_4", "big_5", "big_6", "big_7", "big_8", "big_9", /*"big_10"*/};

    for (const std::string& s : small) {
        run(s);
        componentCount = 0;
    }

    for (const std::string& s : big) {
        run(s);
        componentCount = 0;
    }

    return 0;
}

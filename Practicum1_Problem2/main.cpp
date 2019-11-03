#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

std::vector<int>* graph;
int streets, intersections, bins;

void readFromStdin() {
    std::cin >> streets >> intersections >> bins;
    graph = new std::vector<int>[intersections];

    for (int i = 0; i < streets; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

int readFromFile(const std::string &filename) {
    std::fstream fs("..\\samples\\" + filename + ".in");
    fs >> streets >> intersections >> bins;
    graph = new std::vector<int>[intersections];

    int a, b;
    while (fs >> a >> b) {
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    fs = std::fstream("..\\samples\\" + filename + ".out");
    std::string expected;
    fs >> expected;
    return expected.compare("impossible");
}

std::pair<int, int> bfs() {
    int colors[intersections];
    colors[0] = 1;
    for (int i = 1; i < intersections; ++i) {
        colors[i] = -1;
    }

    std::pair<int, int> sizes;
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v = graph[u].begin(); v != graph[u].end(); v++) {
            if (graph[u][*v] && colors[*v] == -1) {
                int color = 1 - colors[u];
                colors[*v] = color;
                color == 0 ? ++sizes.first : ++sizes.second;
                q.push(*v);
            }
        }
    }
}

void printGraph() {
    for (int i = 0; i < intersections; i++) {
        std::cout << "Adjacency list of " << i << ": head";
        for (int j : graph[i]) {
            std::cout << " -> " << j;
        }
        std::cout << std::endl;
    }
}

void run(const std::string& filename) {
    bool expected = readFromFile(filename);
    std::pair<int, int> sizes = bfs();
    bool actual = sizes.first >= bins || sizes.second >= bins;

    std::cout << "Expected: " << (expected ? "possible" : "impossible")
              << ", should be: " << (actual ? "possible" : "impossible")
              << std::endl;
}

int main() {
    std::string small[] = {"small_1", "small_2", "small_3", "small_4", "small_5", "small_6"};
    std::string big[] = {"big_1", "big_2", "big_3", "big_4", "big_5", "big_6"};
    std::string extra[] = {"extra_1", "extra_2", "extra_3", "extra_4", "extra_5", "extra_6", "extra_7", "extra_8"};

    for (const std::string& s : small) {
        run(s);
    }

    return 0;
}

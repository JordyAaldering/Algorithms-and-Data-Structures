#ifndef PRACTICUM1_PROBLEM1_GRAPH_H
#define PRACTICUM1_PROBLEM1_GRAPH_H

class Graph {
private:
    int V;  /// amount of vertices
    bool *visited;  /// visited vertices

    std::vector<int>* G;    /// the graph as a linked list
    std::vector<int>* CCS;  /// the connected components (cc) as linked lists

    int CCCount = 0;    /// amount of connected components
    int* CCRoots;       /// cc vertices with smallest depth of their cc
    int* CCRootDepths;  /// maximum depth of each cc root

    void resetVisited();

    void ccsUtil(int i);

    int depthUtil(int i, int depth = 0);

    std::pair<int, int> bfs(int s);

public:
    explicit Graph(int v);

    void addEdge(int a, int b);

    void calculateCCS();

    void calculateCCRoots();

    void calculateCCRootDepths();

    void extendGraph();

    int calculateLongestPath();

    void print();
};

#endif //PRACTICUM1_PROBLEM1_GRAPH_H

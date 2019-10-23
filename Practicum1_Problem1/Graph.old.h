#ifndef PRACTICUM1_PROBLEM1_GRAPH_OLD_H
#define PRACTICUM1_PROBLEM1_GRAPH_OLD_H

class Graph {
private:
    int V;            /// amount of vertices
    int CCCount = 0;  /// amount of connected components

    std::vector<int>* G;    /// the graph as a linked list
    std::vector<int>* CCS;  /// the connected components (cc) as linked lists

    int* CCRoots;       /// cc vertices with smallest depth of their cc
    int* CCRootDepths;  /// maximum depth of each cc root
    bool* visited;      /// visited vertices

    void resetVisited();

    void ccsUtil(int i);

    int depthUtil(int i, int depth = 0);

    std::pair<int, int> bfs(int s);

public:
    explicit Graph(int v);

    void addEdge(int c1, int c2);

    void calculateCCS();

    void calculateCCRoots();

    void calculateCCRootDepths();

    void extendGraph();

    int calculateLongestPath();

    void print();
};

#endif //PRACTICUM1_PROBLEM1_GRAPH_OLD_H

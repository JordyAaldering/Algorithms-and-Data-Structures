#ifndef PRACTICUM1_PROBLEM1_GRAPH_H
#define PRACTICUM1_PROBLEM1_GRAPH_H

class Graph {
private:

    /// amount of vertices
    int V;

    /// visited vertices
    bool *visited;

    /// the graph as a linked list
    std::vector<int>* G;
    /// the connected components (cc) as linked lists
    std::vector<int>* CCS;

    /// amount of connected components
    int CCCount = 0;
    /// cc vertices with most neighbors
    int* CCRoots;
    /// maximum depth of each cc root
    int* CCRootDepths;

    void resetVisited();

    void calculateCCSUtil(int i);

    int calculateRootsUtil(int i, int depth = 0);

    int depthUtil(int i, int depth = 0);

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

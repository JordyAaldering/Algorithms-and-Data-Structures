#ifndef PRACTICUM1_PROBLEM1_GRAPH_H
#define PRACTICUM1_PROBLEM1_GRAPH_H

class Graph {
private:

    /// amount of vertices
    int V;
    /// the graph as a linked list
    std::vector<int>* G;
    /// visited vertices
    bool *visited;

    /// amount of connected components
    int CCCount = 0;
    /// the connected components (cc)
    std::vector<int>* CCS;
    /// cc vertices with most neighbors
    int* CCRoots;
    /// maximum depth of each cc root
    int* CCRootDepths;

    void resetVisited();

    void ccsUtil(int i);

    int rootsUtil(int i, int depth = 0);

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

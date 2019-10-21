#include <iostream>
#include <vector>

class Graph
{
private:
    int V; // amount of vertices
    std::vector<int>* G; // the graph

    int CCCount = 0; // amount of connected components
    std::vector<int>* CCS; // the connected components
    int* CCRoots; // connected component vertices with most neighbors


public:
    explicit Graph(int v)
    {
        this->V = v;
        this->G = new std::vector<int>[v];
        this->CCS = new std::vector<int>[v];
    }

    void addEdge(int a, int b)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void dfsUtil(int i, bool *visited)
    {
        CCS[CCCount].push_back(i);

        visited[i] = true;
        std::vector<int>::iterator j;
        for (j = G[i].begin(); j != G[i].end(); ++j) {
            if (!visited[*j]) {
                dfsUtil(*j, visited);
            }
        }
    }

    void calculateCCS()
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsUtil(i, visited);
                CCCount++;
            }
        }
    }

    void calculateCCRoots()
    {
        CCRoots = new int[CCCount];
        for (int i = 0; i < CCCount; i++) {
            int bestRootIndex = -1;
            int bestRootSize = -1;

            for (int j : CCS[i]) {
                int size = G[j].size();
                if (size > bestRootSize) {
                    bestRootIndex = j;
                    bestRootSize = size;
                }
            }

            CCRoots[i] = bestRootIndex;
        }
    }

    void print()
    {
        for (int i = 0; i < V; i++)
        {
            std::cout << "Adjacency list of " << i << ": head";
            for (int j : G[i]) {
                std::cout << " -> " << j;
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < CCCount; i++)
        {
            std::cout << "Connected Component: ";
            for (int j : CCS[i]) {
                std::cout << j << ", ";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < CCCount; i++) {
            std::cout << "CC root " << i << ": " << CCRoots[i] << std::endl;
        }
    }
};

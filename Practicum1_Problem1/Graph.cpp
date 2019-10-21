#include <iostream>
#include <vector>

class Graph
{
private:
    int V;
    std::vector<int>* G;

    int CCount;
    std::vector<int>* CCS;

public:
    explicit Graph(int v)
    {
        this->V = v;
        this->G = new std::vector<int>[v];
        this->CCount = 0;
        this->CCS = new std::vector<int>[v];
    }

    void addEdge(int a, int b)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void dfsUtil(int i, bool *visited)
    {
        CCS[CCount].push_back(i);

        visited[i] = true;
        std::vector<int>::iterator j;
        for (j = G[i].begin(); j != G[i].end(); ++j) {
            if (!visited[*j]) {
                dfsUtil(*j, visited);
            }
        }
    }

    void dfs()
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsUtil(i, visited);
                CCount++;
            }
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

        for (int i = 0; i < CCount; i++)
        {
            std::cout << "Connected Component: ";
            for (int j : CCS[i]) {
                std::cout << j << ", ";
            }
            std::cout << std::endl;
        }
    }
};

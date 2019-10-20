#include<iostream>
#include<vector>

class Graph
{
private:
    std::vector<int> *G;
    int V;

    void dfsUtil(int v, bool *visited)
    {
        visited[v] = true;
        std::cout << v << " ";

        std::vector<int>::iterator i;
        for (i = G[v].begin(); i != G[v].end(); ++i) {
            if (!visited[*i]) {
                dfsUtil(*i, visited);
            }
        }
    }

public:
    explicit Graph(int v)
    {
        this->V = v;
        this->G = new std::vector<int>[v];
    }

    void addEdge(int v, int w)
    {
        G[v].push_back(w);
        G[w].push_back(v);
    }

    void dfs(int v)
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        dfsUtil(v, visited);
    }

    void print()
    {
        for (int i = 0; i < V; i++)
        {
            std::cout << "Adjacency list of " << i << ": head";
            for (int x : G[i]) {
                std::cout << " -> " << x;
            }
            std::cout << std::endl;
        }
    }
};

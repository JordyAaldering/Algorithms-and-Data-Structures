#include <iostream>
#include <vector>

void addEdge(std::vector<int> G[], int a, int b)
{
    G[a].push_back(b);
    G[b].push_back(a);
}

void printGraph(std::vector<int> G[], int V)
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

int main() {
    int V, E;
    std::cin >> V >> E;

    std::vector<int> G[V];
    for (int i = 0; i < E; i++) {
        int c1, c2;
        std::cin >> c1 >> c2;
        addEdge(G, c1, c2);
    }

    printGraph(G, V);
    return 0;
}

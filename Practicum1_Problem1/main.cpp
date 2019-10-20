#include "Graph.cpp"

Graph readFromUser()
{
    int V, E;
    std::cin >> V >> E;

    Graph G(V);
    for (int i = 0; i < E; i++) {
        int c1, c2;
        std::cin >> c1 >> c2;
        G.addEdge(c1, c2);
    }

    return G;
}

Graph readFromFile()
{
    Graph G(0);
    return G;
}

Graph readFromTest()
{
    Graph G(5);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 3);

    return G;
}

int main()
{
    Graph G = readFromTest();
    G.print();
    G.dfs(2);

    return 0;
}

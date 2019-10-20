#include <fstream>
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

Graph readFromFile(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".in");

    int V, E;
    fs >> V >> E;

    Graph G(V);
    int c1, c2;
    while (fs >> c1 >> c2) {
        G.addEdge(c1, c2);
    }

    return G;
}

Graph readFromTest()
{
    Graph G(6);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);

    return G;
}

int main()
{
    Graph G = readFromFile("small_4");
    G.print();
    G.dfs(2);

    return 0;
}

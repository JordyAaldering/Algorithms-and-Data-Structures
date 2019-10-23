#include <fstream>
#include "Graph.old.cpp"

graph readFromUser()
{
    int V, E, c1, c2;
    std::cin >> V >> E;

    graph G(V);
    for (int i = 0; i < E; i++) {
        std::cin >> c1 >> c2;
        G.addEdge(c1, c2);
    }

    return G;
}

graph createGraph(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".in");

    int V, E, c1, c2;
    fs >> V >> E;

    graph G(V);
    while (fs >> c1 >> c2) {
        G.addEdge(c1, c2);
    }

    return G;
}

int readExpected(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".out");

    int expected;
    fs >> expected;
    return expected;
}

int main()
{
    std::string filename = "big_1";

    std::cout << "Creating graph.old..." << std::endl;
    graph G = createGraph(filename);
    std::cout << "Calculating components..." << std::endl;
    G.calculateCCS();
    std::cout << "Calculating Roots..." << std::endl;
    G.calculateCCRoots();
    std::cout << "Calculating Depths..." << std::endl;
    G.calculateCCRootDepths();
    std::cout << "Extending graph.old..." << std::endl;
    G.extendGraph();

    std::cout << "Calculating Path..." << std::endl;
    int length = G.calculateLongestPath();
    int expected = readExpected(filename);

    //graph.old.print();
    std::cout << length << " " << expected << std::endl;

    return 0;
}

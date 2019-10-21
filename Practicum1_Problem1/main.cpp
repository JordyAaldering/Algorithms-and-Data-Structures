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

    fs.close();

    return G;
}

int readExpected(const std::string& filename)
{
    std::fstream fs("..\\samples\\" + filename + ".out");

    int expected;
    fs >> expected;
    fs.close();

    return expected;
}

void checkFile(const std::string& i)
{
    std::string filename = "big_" + i;

    std::cout << "Creating Graph..." << std::endl;
    Graph G = readFromFile(filename);

    std::cout << "Calculating CCS..." << std::endl;
    G.calculateCCS();

    std::cout << "Calculating Roots..." << std::endl;
    G.calculateCCRoots();

    std::cout << "Calculating Depths..." << std::endl;
    G.calculateCCRootDepths();

    std::cout << "Extending Graph..." << std::endl;
    G.extendGraph();

    std::cout << "Calculating Path..." << std::endl;
    int length = G.calculateLongestPath();

    //G.print();

    int expected = readExpected(filename);
    std::cout << i << ") " << length << "\t" << expected << std::endl;
}

int main()
{
    //std::string is[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    std::string is[1] = { "4" };

    std::cout << "Clcltd\tXpctd" << std::endl;
    for (const std::string& i : is) {
        checkFile(i);
    }

    return 0;
}

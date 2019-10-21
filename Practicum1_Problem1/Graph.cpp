#include <iostream>
#include <vector>

class Graph
{
private:
    int V; // amount of vertices
    std::vector<int>* G; // the graph
    bool *visited;

    int CCCount = 0; // amount of connected components
    std::vector<int>* CCS; // the connected components
    int* CCRoots; // cc vertices with most neighbors
    int* CCRootDepths; // maximum depth of each cc root

    int longestPath = 0;

    void ccsUtil(int i)
    {
        CCS[CCCount].push_back(i);

        visited[i] = true;
        std::vector<int>::iterator j;

        for (j = G[i].begin(); j != G[i].end(); j++) {
            if (!visited[*j]) {
                ccsUtil(*j);
            }
        }
    }

    int rootsUtil(int i, int depth = 0)
    {
        int newBestDepth = -1;

        visited[i] = true;
        std::vector<int>::iterator j;

        for (j = CCS[i].begin(); j != CCS[i].end(); j++) {
            if (!visited[*j]) {
                int nextDepth = depthUtil(*j, depth + 1);
                newBestDepth = std::max(newBestDepth, nextDepth);
            }
        }

        return std::max(depth, newBestDepth);
    }

    int depthUtil(int i, int depth = 0)
    {
        int newBestDepth = -1;

        visited[i] = true;
        std::vector<int>::iterator j;

        for (j = G[i].begin(); j != G[i].end(); j++) {
            if (!visited[*j]) {
                int nextDepth = depthUtil(*j, depth + 1);
                newBestDepth = std::max(newBestDepth, nextDepth);
            }
        }

        return std::max(depth, newBestDepth);
    }

public:
    explicit Graph(int v)
    {
        this->V = v;
        this->G = new std::vector<int>[v];
        this->CCS = new std::vector<int>[v];
        this->visited = new bool[V];
    }

    void addEdge(int a, int b)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void calculateCCS()
    {
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                ccsUtil(i);
                CCCount++;
            }
        }
    }

    void calculateCCRoots()
    {
        CCRoots = new int[CCCount];
        for (int i = 0; i < CCCount; i++) {
            int bestRootIndex = -1;
            int bestRootDepth = 1000000;

            for (int j : CCS[i]) {
                for (int k = 0; k < V; k++) {
                    visited[k] = false;
                }

                int depth = depthUtil(j);
                if (depth < bestRootDepth) {
                    bestRootIndex = j;
                    bestRootDepth = depth;
                }
            }

            CCRoots[i] = bestRootIndex;
        }
    }

    void calculateCCRootDepths()
    {
        CCRootDepths = new int[CCCount];

        for (int i = 0; i < CCCount; i++) {
            for (int j = 0; j < V; j++) {
                visited[j] = false;
            }

            CCRootDepths[i] = depthUtil(CCRoots[i]);
        }
    }

    void extendGraph()
    {
        int longestDepthIndex = -1;
        int longestDepthSize = -1;
        for (int i = 0; i < CCCount; i++) {
            if (CCRootDepths[i] > longestDepthSize) {
                longestDepthIndex = CCRoots[i];
                longestDepthSize = CCRootDepths[i];
            }
        }

        for (int i = 0; i < CCCount; i++) {
            if (CCRoots[i] != longestDepthIndex) {
                addEdge(CCRoots[i], longestDepthIndex);
            }
        }
    }

    int calculateLongestPath()
    {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                visited[j] = false;
            }

            for (int j : G[i])
            {
                int depth = depthUtil(j) - 1;
                longestPath = std::max(longestPath, depth);
            }
        }

        return longestPath;
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

        for (int i = 0; i < CCCount; i++) {
            std::cout << "CC depth " << i << ": " << CCRootDepths[i] << std::endl;
        }

        std::cout << "Longest path: " << longestPath << std::endl;
    }
};

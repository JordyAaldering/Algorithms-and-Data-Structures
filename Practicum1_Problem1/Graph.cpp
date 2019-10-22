#include <iostream>
#include <vector>
#include "Graph.h"

void Graph::resetVisited()
{
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
}

void Graph::ccsUtil(int i)
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

int Graph::depthUtil(int i, int depth)
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

Graph::Graph(int v)
{
    this->V = v;
    this->G = new std::vector<int>[v];
    this->CCS = new std::vector<int>[v];
    this->visited = new bool[V];
}

void Graph::addEdge(int a, int b)
{
    G[a].push_back(b);
    G[b].push_back(a);
}

void Graph::calculateCCS()
{
    resetVisited();

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            ccsUtil(i);
            CCCount++;
        }
    }
}

void Graph::calculateCCRoots()
{
    CCRoots = new int[CCCount];

    int bestRootIndex = -1;
    int bestRootDepth = 10E6;

    for (int i = 0; i < CCCount; i++) {
        resetVisited();

        int depth = depthUtil(i);
        if (depth < bestRootDepth) {
            bestRootIndex = i;
            bestRootDepth = depth;
        }

        CCRoots[i] = bestRootIndex;
    }
}

void Graph::calculateCCRootDepths()
{
    CCRootDepths = new int[CCCount];

    for (int i = 0; i < CCCount; i++) {
        resetVisited();
        CCRootDepths[i] = depthUtil(CCRoots[i]);
    }
}

void Graph::extendGraph()
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

int Graph::calculateLongestPath()
{
    int longestPath = 0;

    if (CCCount == 1) {
        return CCRootDepths[0];
    }

    for (int i = 0; i < CCCount - 1; i++) {
        for (int j = i + 1; j < CCCount; j++) {
            longestPath = std::max(longestPath, CCRootDepths[i] + CCRootDepths[j]);
        }
    }

    return longestPath;
}

void Graph::print()
{
    for (int i = 0; i < V; i++) {
        std::cout << "Adjacency list of " << i << ": head";
        for (int j : G[i]) {
            std::cout << " -> " << j;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < CCCount; i++) {
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
}

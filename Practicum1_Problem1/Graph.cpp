#include <iostream>
#include <vector>
#include <list>
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

std::pair<int, int> Graph::bfs(int s)
{
    short distances[V];
    std::list<int> queue;
    std::vector<int>::iterator i;

    distances[s] = 0;
    queue.push_back(s);

    while (!queue.empty()) {
        s = queue.front();
        queue.pop_front();

        for (i = G[s].begin(); i != G[s].end(); i++) {
            if (distances[*i] == 0) {
                distances[*i] = distances[s] + 1;
                queue.push_back(*i);
            }
        }
    }

    int nodeIndex = 0;
    int maxDistance = 0;

    for (int j = 0; j < V; j++) {
        if (distances[j] > maxDistance) {
            nodeIndex = j;
            maxDistance = distances[j];
        }
    }

    return std::make_pair(nodeIndex, maxDistance);
}

Graph::Graph(int v)
{
    this->V = v;
    this->G = new std::vector<int>[v];
    this->CCS = new std::vector<int>[v];
    this->visited = new bool[v];
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

    for (int i = 0; i < CCCount; i++) {
        int bestRootIndex = 0;
        int bestRootSize = 0;

        for (int j : CCS[i]) {
            if (G[j].size() >= bestRootSize) {
                bestRootIndex = j;
                bestRootSize = G[j].size();
            }
        }

        CCRoots[i] = bestRootIndex;
    }
}

void Graph::calculateCCRootDepths()
{
    CCRootDepths = new int[CCCount];

    resetVisited();
    for (int i = 0; i < CCCount; i++) {
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
    std::pair<int, int> from, to;
    from = bfs(0);
    to = bfs(from.first);

    return std::max(0, to.second - 1);
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

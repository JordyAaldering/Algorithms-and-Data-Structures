#include <vector>
#include<climits>

int minDistance(const int* distance, const bool* isSet, int size) {
    int minDistance = distance[0];
    int minIndex = 0;

    for (int v = 1; v < size; v++) {
        if (!isSet[v] && distance[v] < minDistance) {
            minDistance = distance[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void dijkstra(int** graph, int size, int src = 0)
{
    int distance[size];
    std::fill(distance, distance + size, INT_MAX);
    distance[src] = 0;

    bool isSet[size];
    std::fill(isSet, isSet + size, false);

    for (int step = 0; step < size - 1; step++) {
        int i = minDistance(distance, isSet, size);
        isSet[i] = true;

        for (int v = 0; v < size; v++) {
            if (!isSet[v] && graph[i][v] && distance[i] < INT_MAX) {
                int currentDistance = distance[i] + graph[i][v];

                if (currentDistance < distance[v]) {
                    distance[v] = currentDistance;
                }
            }
        }
    }
}

#include <queue>
#include <vector>
#include <climits>

bool hasAugmentingPath(int** residual, int size, int s, int t, int* parent) {
    bool visited[size];
    std::fill(visited, visited + size, false);
    visited[s] = true;

    parent[s] = -1;

    std::queue<int> queue;
    queue.push(s);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < size; v++) {
            if (!visited[v] && residual[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                queue.push(v);
            }
        }
    }

    return visited[t];
}

int fordFulkerson(int** graph, int size, int s, int t) {
    int u, v;

    int residual[size][size];
    for (u = 0; u < size; u++) {
        for (v = 0; v < size; v++) {
            residual[u][v] = graph[u][v];
        }
    }

    int parent[size];
    int max_flow = 0;

    while (hasAugmentingPath(residual, size, s, t, parent)) {
        int path_flow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

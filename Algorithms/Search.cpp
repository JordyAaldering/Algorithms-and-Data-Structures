#include <vector>
#include <queue>

void bfs(std::vector<int>* adj, int i) {
    int size = adj->size();

    bool visited[size];
    std::fill(visited, visited + size, false);
    visited[i] = true;

    std::queue<int> queue;
    queue.push(i);

    while(!queue.empty()) {
        i = queue.front();
        queue.pop();

        for (int v : adj[i]) {
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
}

void dfs(std::vector<int>* adj, int i, bool* visited) {
    visited[i] = true;

    for (int v : adj[i]) {
        if (!visited[v]) {
            dfs(adj, v, visited);
        }
    }
}

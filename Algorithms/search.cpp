#include <vector>
#include <queue>

void bfs(std::vector<int>* adj, int i = 0) {
    int size = adj->size();

    std::queue<int> queue;
    queue.push(i);

    bool visited[size];
    std::fill(visited, visited + size, false);
    visited[i] = true;

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

void dfs(std::vector<int>* adj, bool* visited, int i = 0) {
    visited[i] = true;

    for (int v : adj[i]) {
        if (!visited[v]) {
            dfs(adj, visited, v);
        }
    }
}

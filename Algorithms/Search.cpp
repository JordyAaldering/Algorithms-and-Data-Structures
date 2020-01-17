#include <vector>
#include <queue>

void bfs(std::vector<int>* adj, int i = 0)
{
    bool visited[adj->size()];
    std::fill(visited, visited + adj->size(), false);

    std::queue<int> queue;

    visited[i] = true;
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

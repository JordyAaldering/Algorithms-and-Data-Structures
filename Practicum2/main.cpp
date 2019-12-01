#include <iostream>
#include <vector>
#include <map>

using String = std::string;
using Vertex = std::vector<int>;
using Person = std::pair<String, std::pair<int, bool>>;

int vertexCount;
Vertex* graph;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void readStdIn() {
    int n, m;
    std::cin >> n >> m;
    vertexCount = n + n + 1;

    graph = new Vertex[vertexCount];
    std::map<String, Person> persons;

    // Keep track of actresses.
    for (int i = 0; i < n; i++) {
        String actress;
        std::cin >> actress;
        persons[actress] = std::make_pair(actress, std::make_pair(i, false));
    }

    // Keep track of actors.
    for (int i = 0; i < n; i++) {
        String actor;
        std::cin >> actor;
        persons[actor] = std::make_pair(actor, std::make_pair(n + i, true));
    }

    // Add casts of all movies.
    for (int i = 0; i < m; i++) {
        String movie;
        std::cin >> movie;

        int s;
        std::cin >> s;
        Person cast[s];

        // Add all stars of a movie.
        for (int j = 0; j < s; j++) {
            String name;
            std::cin >> name;

            Person star = persons[name];
            cast[j] = star;

            // Add connections with existing cast.
            for (int k = 0; k < j; k++) {
                Person costar = persons[cast[k].first];
                if (star.second.second != costar.second.second) {
                    addEdge(star.second.first, costar.second.first);
                }
            }
        }
    }

    // Add root edge to all actresses.
    for (int i = 0; i < n; i++) {
        addEdge(vertexCount - 1, i);
    }
}

bool minimax(int index, bool maximize, bool *visited) {
    visited[index] = true;

    // Check possible choices.
    for (int vertex : graph[index]) {
        if (!visited[vertex]) {
            if (minimax(vertex, !maximize, visited) == maximize) {
                // A winning path has been found.
                return maximize;
            }
        }
    }

    // This is a leaf or no solution was found.
    return !maximize;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);
    readStdIn();

    bool visited[vertexCount];
    std::fill(visited, visited + vertexCount, false);

    bool win = minimax(vertexCount - 1, true, visited);
    std::cout << (win ? "Veronique" : "Mark");

    return 0;
}

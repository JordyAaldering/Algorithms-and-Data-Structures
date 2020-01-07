#include <iostream>
#include <vector>
#include <map>

using String = std::string;
using Vertex = std::vector<short>;
using Person = std::pair<String, std::pair<short, bool>>;

short n, vertexCount;
Vertex* graph;

void addEdge(short a, short b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void readStdIn() {
    short m;
    std::cin >> n >> m;
    vertexCount = n + n;

    graph = new Vertex[vertexCount];
    std::map<String, Person> persons;

    // Keep track of actresses.
    for (short i = 0; i < n; i++) {
        String actress;
        std::cin >> actress;
        persons[actress] = std::make_pair(actress, std::make_pair(i, false));
    }

    // Keep track of actors.
    for (short i = 0; i < n; i++) {
        String actor;
        std::cin >> actor;
        persons[actor] = std::make_pair(actor, std::make_pair(n + i, true));
    }

    // Add casts of all movies.
    for (short i = 0; i < m; i++) {
        String movie;
        std::cin >> movie;

        short s;
        std::cin >> s;
        Person cast[s];

        // Add all stars of a movie.
        for (short j = 0; j < s; j++) {
            String name;
            std::cin >> name;

            Person star = persons[name];
            cast[j] = star;

            // Add connections with existing cast.
            for (short k = 0; k < j; k++) {
                Person costar = persons[cast[k].first];
                if (star.second.second != costar.second.second) {
                    addEdge(star.second.first, costar.second.first);
                }
            }
        }
    }
}

bool bpm(short index, bool* visited, short* assigned) {
    for (short vertex : graph[index]) {
        if (!visited[vertex]) {
            visited[vertex] = true;

            if (assigned[vertex] < 0 || bpm(assigned[vertex], visited, assigned)) {
                assigned[vertex] = index;
                return true;
            }
        }
    }

    return false;
}

short bpmMax() {
    bool visited[vertexCount];
    short assigned[vertexCount];
    std::fill(assigned, assigned + vertexCount, -1);

    short result = 0;
    for (short i = 0; i < n; i++) {
        std::fill(visited, visited + vertexCount, false);

        if (bpm(i, visited, assigned)) {
            result++;
        }
    }

    return result;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    readStdIn();
    std::cout << (bpmMax() == n ? "Mark" : "Veronique");

    return 0;
}

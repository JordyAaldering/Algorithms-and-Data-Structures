#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using String = std::string;
using Vertex = std::vector<int>;
using Person = std::pair<String, std::pair<int, bool>>;

int vertexCount;
Vertex* graph;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

String readStdIn(const String& filename) {
    std::fstream fs("..\\samples\\" + filename + ".in");

    int n, m;
    fs >> n >> m;
    vertexCount = n + n + 1;

    graph = new Vertex[vertexCount];
    std::map<String, Person> persons;

    // Keep track of actresses.
    for (int i = 0; i < n; i++) {
        String actress;
        fs >> actress;
        persons[actress] = std::make_pair(actress, std::make_pair(i, false));
    }

    // Keep track of actors.
    for (int i = 0; i < n; i++) {
        String actor;
        fs >> actor;
        persons[actor] = std::make_pair(actor, std::make_pair(n + i, true));
    }

    // Add casts of all movies.
    for (int i = 0; i < m; i++) {
        String movie;
        fs >> movie;

        int s;
        fs >> s;
        Person cast[s];

        // Add all stars of a movie.
        for (int j = 0; j < s; j++) {
            String name;
            fs >> name;

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
        graph[vertexCount - 1].push_back(i);
    }

    fs = std::fstream("..\\samples\\" + filename + ".out");
    String expected;
    fs >> expected;
    return expected;
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

void run(const String& filename) {
    std::cout << "Expecting " << readStdIn(filename) << " got ";

    bool visited[vertexCount];
    std::fill(visited, visited + vertexCount, false);

    bool win = minimax(vertexCount - 1, true, visited);
    std::cout << (win ? "Veronique" : "Mark") << std::endl;
}

int main() {
    std::iostream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    String a[] = { "a1", "a2" };
    String b[] = { "b1", "b2" };
    String v[] = { "v1", "v2", "v3", "v4" };
    String m[] = { "m1", "m2", "m3", "m4" };
    String r[] = { "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10" };
    String all[] = { "a1", "a2", "b1", "b2", "v1", "v2", "v3", "v4", "m1", "m2", "m3", "m4", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10" };

    for (const String& filename : all) {
        run(filename);
    }

    return 0;
}

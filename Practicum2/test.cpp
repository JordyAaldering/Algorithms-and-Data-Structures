#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using String = std::string;
using Vertex = std::vector<short>;
using Person = std::pair<String, std::pair<short, bool>>;

short n, vertexCount;
Vertex* graph;

void addEdge(short a, short b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

String readStdIn(const String& filename) {
    std::fstream fs("..\\samples\\" + filename + ".in");

    short m;
    fs >> n >> m;
    vertexCount = n + n;

    graph = new Vertex[vertexCount];
    std::map<String, Person> persons;

    // Keep track of actresses.
    for (short i = 0; i < n; i++) {
        String actress;
        fs >> actress;
        persons[actress] = std::make_pair(actress, std::make_pair(i, false));
    }

    // Keep track of actors.
    for (short i = 0; i < n; i++) {
        String actor;
        fs >> actor;
        persons[actor] = std::make_pair(actor, std::make_pair(n + i, true));
    }

    // Add casts of all movies.
    for (short i = 0; i < m; i++) {
        String movie;
        fs >> movie;

        short s;
        fs >> s;
        Person cast[s];

        // Add all stars of a movie.
        for (short j = 0; j < s; j++) {
            String name;
            fs >> name;

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

    fs = std::fstream("..\\samples\\" + filename + ".out");
    String expected;
    fs >> expected;
    return expected;
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

    String a[] = { "a1", "a2" };
    String b[] = { "b1", "b2" };
    String v[] = { "v1", "v2", "v3", "v4" };
    String m[] = { "m1", "m2", "m3", "m4" };
    String r[] = { "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10" };
    String all[] = { "a1", "a2", "b1", "b2", "v1", "v2", "v3", "v4", "m1", "m2", "m3", "m4", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10" };

    for (const String& filename : all) {
        std::cout << "Expecting " << readStdIn(filename) << " got ";
        std::cout << (bpmMax() == n ? "Mark" : "Veronique") << std::endl;
    }

    return 0;
}

#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

int vertexCount;
vector<int>* graph;

void addEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

struct Person {
    string name;
    int index;
    bool gender;

    Person() : name(""), index(0), gender(false) { }

    /// \param name The name of this person.
    /// \param index This person's index in the graph.
    /// \param gender This person's gender, where false = female.
    Person(string name, int index, bool gender) : name(move(name)), index(index), gender(gender) { }
};

void readStdIn() {
    int n, m;
    std::cin >> n >> m;
    vertexCount = n + n + 1;

    graph = new vector<int>[vertexCount];
    map<string, Person> persons;

    // Keep track of the names of all actresses.
    for (int i = 0; i < n; i++) {
        string actress;
        std::cin >> actress;
        persons[actress] = Person(actress, i, false);
    }

    // Keep track of the names of all actors.
    for (int i = 0; i < n; i++) {
        string actor;
        std::cin >> actor;
        persons[actor] = Person(actor, n + i, true);
    }

    // Add all casts.
    for (int i = 0; i < m; i++) {
        string movie;
        std::cin >> movie;

        int s;
        std::cin >> s;
        Person cast[s];

        // Add all stars of a movie.
        for (int j = 0; j < s; j++) {
            string name;
            std::cin >> name;

            Person star = persons[name];
            cast[j] = star;

            // Add connections with existing cast.
            for (int k = 0; k < j; k++) {
                Person costar = persons[cast[k].name];
                if (star.gender != costar.gender) {
                    addEdge(star.index, costar.index);
                }
            }
        }
    }

    // Add root edge to all actresses.
    for (int i = 0; i < n; i++) {
        addEdge(vertexCount - 1, i);
    }
}

bool dfs(int index, bool maximize, bool visits[]) {
    visits[index] = true;

    // Check possible choices.
    for (int vertex : graph[index]) {
        if (!visits[vertex]) {
            if (dfs(vertex, !maximize, visits) == maximize) {
                // A winning path has been found.
                return maximize;
            }
        }
    }

    // This is a leaf or no solution was found.
    return !maximize;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    readStdIn();

    bool visited[vertexCount];
    fill(visited, visited + vertexCount, false);

    bool win = dfs(vertexCount - 1, true, visited);
    cout << (win ? "Veronique" : "Mark");

    return 0;
}

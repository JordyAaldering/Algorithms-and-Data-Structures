#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <map>
#include <fstream>
#include <ctime>
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

void readStdIn(const string& filename) {
    // Replace fs with cin for use with the testing server.
    fstream fs("..\\samples\\" + filename + ".in");

    int n, m;
    fs >> n >> m;
    vertexCount = n + n;

    graph = new vector<int>[vertexCount];
    map<string, Person> persons;

    for (int i = 0; i < n; i++) {
        string actress;
        fs >> actress;
        persons[actress] = Person(actress, i, false);
    }

    for (int i = 0; i < n; i++) {
        string actor;
        fs >> actor;
        persons[actor] = Person(actor, n + i, true);
    }

    for (int i = 0; i < m; i++) {
        string movie;
        fs >> movie;

        int s;
        fs >> s;
        Person cast[s];

        for (int j = 0; j < s; j++) {
            string name;
            fs >> name;

            Person star = persons[name];
            cast[j] = star;

            for (int k = 0; k < j; k++) {
                Person costar = persons[cast[k].name];
                if (star.gender != costar.gender) {
                    addEdge(star.index, costar.index);
                }
            }
        }
    }
}

void printGraph() {
    for (int v = 0; v < vertexCount; v++) {
        cout << "Adjacency list of " << v << " head";
        for (int x : graph[v]) {
            cout << " -> " << x;
        }
        cout << endl;
    }
}

void run(const string& filename) {
    clock_t begin = clock();

    readStdIn(filename);
    // printGraph();

    clock_t end = clock();
    cout << filename << " done in " << double(end - begin) / CLOCKS_PER_SEC << " seconds" << endl;
}

int main() {
    string a[] = { "a1", "a2" };
    string v[] = { "v1", "v2", "v3", "v4" };
    string m[] = { "m1", "m2", "m3", "m4" };
    string r[] = { "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10" };

    for (const string& filename : v) {
        run(filename);
    }

    return 0;
}

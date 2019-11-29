#include <iostream>
using namespace std;

void readStdIn() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string actress;
        cin >> actress;
    }

    for (int i = 0; i < n; i++) {
        string actor;
        cin >> actor;
    }

    for (int i = 0; i < m; i++) {
        string movie;
        cin >> movie;

        int s;
        cin >> s;

        for (int j = 0; j < s; j++) {
            string name;
            cin >> name;
        }
    }
}

int main() {
    readStdIn();
    return 0;
}
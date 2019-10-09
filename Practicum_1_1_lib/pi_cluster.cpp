#include <iostream>
#include "pi_cluster.h"

void pi_cluster::read_connections(int& num_pis, int& num_connections, connection* connections)
{
    for (int i = 0; i < num_connections; i++) {
        int x, y;
        std::cin >> x >> y;
        connections[i].x = x;
        connections[i].y = y;
    }
}

int pi_cluster::main()
{
    int num_pis, num_connections;
    std::cin >> num_pis >> num_connections;

    connection connections [num_connections];
    read_connections(num_pis, num_connections, connections);

    return 0;
}

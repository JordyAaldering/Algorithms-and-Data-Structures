
#ifndef ALGORITHMS_AND_DATA_STRUCTURES_PI_CLUSTER_H
#define ALGORITHMS_AND_DATA_STRUCTURES_PI_CLUSTER_H


class pi_cluster
{
protected:
    struct connection { int x, y; };
    static void read_connections(int& num_pis, int& num_connections, connection* connections);
public:
    static int main();
};


#endif // ALGORITHMS_AND_DATA_STRUCTURES_PI_CLUSTER_H

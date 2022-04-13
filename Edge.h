#ifndef EDGE_H_
#define EDGE_H_

#include <string>

struct Edge
{
    int node_A_id = -1;

    int node_B_id = -1;

    Edge(int nodeA, int nodeB) : node_A_id(nodeA), node_B_id(nodeB) {};

};

#endif // !EDGE_H_
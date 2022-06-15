#ifndef PLAYER_GRAPH_H_
#define PLAYER_GRAPH_H_

#include <string>
#include <list>
#include "Node.h"
#include "Edge.h"

class PlayerGraph
{
public:
    std::string name_;

    char square_;

    std::list<Node> nodes_list_;

    std::list<Edge> edge_list_;

    PlayerGraph() {};

    PlayerGraph(std::string name, char square) :name_(name), square_(square) {};

};

#endif  //!PLAYER_GRAPH_H_
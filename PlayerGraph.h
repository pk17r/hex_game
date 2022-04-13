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

    std::list<Node> nodes_list_;

    std::list<Edge> edge_list_;

    char player_identifier;

    PlayerGraph() {};

    PlayerGraph(std::string name, char identifier) :name_(name), player_identifier(identifier) {};

};

#endif  //!PLAYER_GRAPH_H_
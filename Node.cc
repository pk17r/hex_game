#include"Node.h"

using namespace std;

//defining constructors here itself
Node::Node(int id)
{
    this->id = id;
    this->nearest_node_id = kNullId;
}

Node::Node(int row_index, int col_index, int board_size)
{
    this->id = row_index * board_size + col_index;
    this->nearest_node_id = kNullId;
}
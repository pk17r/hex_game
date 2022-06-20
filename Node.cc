#include"Node.h"

using namespace std;

Node::Node(int id)
{
    this->id = id;
}

Node::Node(int row_index, int col_index, int board_size)
{
    this->id = row_index * board_size + col_index;
}
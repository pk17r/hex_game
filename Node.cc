#include"Node.h"

using namespace std;

//defining constructors here itself
Node::Node(int id)
{
    this->id = id;
    this->nearest_node_id = kNullId;
}

//Node::Node(int id, int nearest_node_id)
//{
//    this->id = id;
//    this->nearest_node_id = nearest_node_id;
//}
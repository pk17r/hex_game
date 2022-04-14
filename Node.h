#ifndef NODE_H_
#define NODE_H_

struct Node
{
    //Node ids will be whole numbers
    static const int kNullId = -1;

    //an imaginary node id to start player's hex board graph from
    static const int graph_start_id = -2;
    
    //an imaginary node id to end player's hex board graph to
    static const int graph_end_id = -3;

    int id = kNullId;
    
    int nearest_node_id = kNullId;
    
    int distance = 1;

    Node(int id);
    
    //Node(int id, int nearest_node_id);

};

#endif // !NODE_H_
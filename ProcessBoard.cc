#include <cstdlib>
#include <ctime>
#include "Node.h"
#include "ProcessBoard.h"

using namespace std;

ProcessBoard::ProcessBoard(Square** hex_board_data, int board_size_data)
{
    this->board_size = board_size_data;

    //copy hex board
    hex_board = new Square * [board_size];
    for (int i = 0; i < board_size; i++)
    {
        hex_board[i] = new Square[board_size];
    }
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            hex_board[i][j] = hex_board_data[i][j];
        }
    }

    node_in_closed_set = new bool[board_size * board_size];

    open_set.capacity(board_size * board_size);
    closed_set.capacity(board_size * board_size);
    current_neighbor_nodes.capacity(max(board_size, 6));

    //setting seed for random number generator
    srand(static_cast<unsigned int>(time(0)));
}

void ProcessBoard::get_connected_nodes(int node_id, Square player)
{
    int row_index = node_id / board_size;
    int col_index = node_id % board_size;

    //list<Node> connected_nodes_list;
    current_neighbor_nodes.clear();
    if (node_id >= 0)
    {
        //connected nodes
        if (row_index > 0 && hex_board[row_index - 1][col_index] == player)
            current_neighbor_nodes.push(Node(row_index - 1, col_index, board_size));

        if (col_index > 0 && hex_board[row_index][col_index - 1] == player)
            current_neighbor_nodes.push(Node(row_index, col_index - 1, board_size));

        if (row_index < board_size - 1 && col_index > 0 && hex_board[row_index + 1][col_index - 1] == player)
            current_neighbor_nodes.push(Node(row_index + 1, col_index - 1, board_size));

        if (row_index < board_size - 1 && hex_board[row_index + 1][col_index] == player)
            current_neighbor_nodes.push(Node(row_index + 1, col_index, board_size));

        if (col_index < board_size - 1 && hex_board[row_index][col_index + 1] == player)
            current_neighbor_nodes.push(Node(row_index, col_index + 1, board_size));

        if (row_index > 0 && col_index < board_size - 1 && hex_board[row_index - 1][col_index + 1] == player)
            current_neighbor_nodes.push(Node(row_index - 1, col_index + 1, board_size));

        //get connection to imaginary start and end nodes
        if (player == Square::PlayerA)
        {
            if (row_index == 0)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (row_index == board_size - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
        else if (player == Square::PlayerB)
        {
            if (col_index == 0)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (col_index == board_size - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
    }
    else
    {//imaginary start or end node
        if (player == Square::PlayerA)
        {
            if (node_id == Node::graph_start_id)
                for (int j = 0; j < board_size; j++)
                    if (hex_board[0][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(0, j, board_size);
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int j = 0; j < board_size; j++)
                    if (hex_board[board_size - 1][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(board_size - 1, j, board_size);
                        current_neighbor_nodes.push(connected_node);
                    }
        }
        else if (player == Square::PlayerB)
        {
            if (node_id == Node::graph_start_id)
                for (int i = 0; i < board_size; i++)
                    if (hex_board[i][0] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, 0, board_size);
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int i = 0; i < board_size; i++)
                    if (hex_board[i][board_size - 1] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, board_size - 1, board_size);
                        current_neighbor_nodes.push(connected_node);
                    }
        }
    }
    //return current_neighbor_nodes;
}

bool ProcessBoard::game_won_check(Square player)
{
    //DijkstrasAlgorithmImplementation

    //openset and closed set defined in ProcessBoard.h class
    //define open set. Defining my own priority queue list to learn how to use it
    //MyPriorityQueue open_set;

    //define closed set
    //MyPriorityQueue closed_set;
    for (int i = 0; i < board_size * board_size; i++)
    {
        node_in_closed_set[i] = false;
    }
    open_set.clear();
    closed_set.clear();

    //Step 1: add imaginary start node to closed set
    closed_set.push(Node(Node::graph_start_id));

    //Step 2: add neighbors of start node to open set
    //list<Node> current_neighbors = get_connected_nodes(Node::graph_start_id, player);
    get_connected_nodes(Node::graph_start_id, player);


    for (int i = 0; i < current_neighbor_nodes.size(); i++)
    {
        current_neighbor_nodes.my_vec_[i].nearest_node_id = Node::graph_start_id;
        open_set.push(current_neighbor_nodes.my_vec_[i]);
    }

    //loop over open set until it is empty
    while (open_set.size() > 0)
    {
        //Step 3: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Node current_node = open_set.get_and_pop_top();

        closed_set.push(current_node);
        if (current_node.id >= 0)
        {
            node_in_closed_set[current_node.id] = true;
        }

        //Step 4: for each neighbor city of current city which is not in closed set
        //current_neighbors = get_connected_nodes(current_node.id, player);
        get_connected_nodes(current_node.id, player);

        for (int i = 0; i < current_neighbor_nodes.size(); i++)
        {
            Node neighbor_node = current_neighbor_nodes.my_vec_[i];

            if (neighbor_node.id == Node::graph_end_id) //found connection to end node
                return true;

            if (!node_in_closed_set[neighbor_node.id])
            {
                //Step 4a: if neighbor node is in open set and its distance to start node through current node is lower than its current distance to start node, then update its distance to start node and nearest neighbor id in open set
                if (open_set.contains_id(neighbor_node.id))
                {
                    Node* open_set_node_ptr = open_set.member_with_id(neighbor_node.id);
                    if (current_node.distance + 1 < open_set_node_ptr->distance)
                    {
                        open_set_node_ptr->distance = current_node.distance + 1;
                        open_set_node_ptr->nearest_node_id = current_node.id;
                        //open_set.sort();
                    }
                }
                else   //Step 4b: if did not find neighbor node in open set then add it to open set with nearest neighbor id as current node id
                {
                    neighbor_node.nearest_node_id = current_node.id;
                    neighbor_node.distance += current_node.distance;
                    open_set.push(neighbor_node);
                }
                //open_set.print();
            }
        }
        open_set.sort();
    }
    //dijkstras algoritm completed without finding a path to end node
    open_set.clear();
    closed_set.clear();
    return false;
}

// return randomly filled up board
void ProcessBoard::fill_board_randomly(Square player, int node_id_as_next_move, std::vector<int> &empty_squares_vector)
{
    int row, col;
    for (int i = 0; i < empty_squares_vector.size(); i++)
    {
        row = empty_squares_vector[i] / board_size;
        col = empty_squares_vector[i] % board_size;
        if (empty_squares_vector[i] != node_id_as_next_move)
            hex_board[row][col] = (rand() % 2 == 0 ? Square::PlayerA : Square::PlayerB);
        else
            hex_board[row][col] = player;
    }
}

ProcessBoard::~ProcessBoard()
{
    for (int i = 0; i < board_size; i++)
    {
        delete[] hex_board[i];
    }
    delete[] hex_board;

    delete node_in_closed_set;
}

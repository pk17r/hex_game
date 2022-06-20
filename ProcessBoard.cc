#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Node.h"
#include "ProcessBoard.h"

using namespace std;

ProcessBoard::ProcessBoard(Square** hex_board_data, int board_size_data, int empty_squares_vector_size_for_simulations)
{
    this->board_size = board_size_data;

    //copy hex board
    hex_board = new Square * [board_size];
    hex_board_visited = new bool* [board_size];
    for (int i = 0; i < board_size; i++)
    {
        hex_board[i] = new Square[board_size];
        hex_board_visited[i] = new bool[board_size];
    }
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            hex_board[i][j] = hex_board_data[i][j];
            hex_board_visited[i][j] = false;
        }
    }

    node_in_closed_set = new bool[board_size * board_size];

    open_set.capacity(board_size * board_size);
    closed_set.capacity(board_size * board_size);
    //current_neighbor_nodes.capacity(max(board_size, 6));

    //if (empty_squares_vector_size_for_simulations > 0)
    //{
    //    //setting seed for random number generator engine
    //    unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
    //    myRandomEngine = default_random_engine(seed);
    //
    //    empty_squares_to_fill_randomly.reserve(empty_squares_vector_size_for_simulations - 1);
    //}
}

ProcessBoard::~ProcessBoard()
{
    for (int i = 0; i < board_size; i++)
    {
        delete[] hex_board[i];
        delete[] hex_board_visited[i];
    }
    delete[] hex_board;
    delete[] hex_board_visited;

    delete node_in_closed_set;
}

void ProcessBoard::check_and_add_nodes_to_current_neighbor_nodes(int& row_index, int& col_index, Square& player, bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes)
{
    if (row_index >= 0 && row_index < board_size && col_index >= 0 && col_index < board_size && hex_board[row_index][col_index] == player)
        if (!unvisited_only || !hex_board_visited[row_index][col_index])
            current_neighbor_nodes.push(Node(row_index, col_index, board_size));
}

//only dfs algorithm uses unvisited_only
MyPriorityQueue ProcessBoard::get_connected_nodes(int node_id, Square player, bool unvisited_only)
{
    int row_index = node_id / board_size;
    int col_index = node_id % board_size;
    int row_index_neighbor, col_index_neighbor;

    MyPriorityQueue current_neighbor_nodes;
    current_neighbor_nodes.clear();
    if (node_id >= 0)
    {
        //connected nodes
        row_index_neighbor = row_index - 1;
        col_index_neighbor = col_index;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);
        
        row_index_neighbor = row_index;
        col_index_neighbor = col_index - 1;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);

        row_index_neighbor = row_index + 1;
        col_index_neighbor = col_index - 1;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);

        row_index_neighbor = row_index + 1;
        col_index_neighbor = col_index;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);

        row_index_neighbor = row_index;
        col_index_neighbor = col_index + 1;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);

        row_index_neighbor = row_index - 1;
        col_index_neighbor = col_index + 1;
        check_and_add_nodes_to_current_neighbor_nodes(row_index_neighbor, col_index_neighbor, player, unvisited_only, current_neighbor_nodes);

        //get connection to imaginary start and end nodes
        if (player == Square::PlayerA)
        {
            //dont add start node if asking for unvisited only as start node is always visited initially by dfs algorithm
            if (row_index == 0 && !unvisited_only)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (row_index == board_size - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
        else if (player == Square::PlayerB)
        {
            //dont add start node if asking for unvisited only as start node is always visited initially by dfs algorithm
            if (col_index == 0 && !unvisited_only)
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
    return current_neighbor_nodes;
}

bool ProcessBoard::game_won_check_aStar(Square player)
{
    //AStarAlgorithmImplementation

    //openset and closed set defined in ProcessBoard.h class

    //define open set. Defining my own priority queue list to learn how to use it
    //MyPriorityQueue open_set;

    //define closed set
    //MyPriorityQueue closed_set;

    //reset open_set, closed_set and node_in_closed_set
    open_set.clear();
    closed_set.clear();
    for (int i = 0; i < board_size * board_size; i++)
    {
        node_in_closed_set[i] = false;
    }
    
    //Step 1: add imaginary start node to closed set
    closed_set.push(Node(Node::graph_start_id));

    //Step 2: add neighbors of start node to open set
    //list<Node> current_neighbors = get_connected_nodes(Node::graph_start_id, player);
    MyPriorityQueue current_neighbor_nodes = get_connected_nodes(Node::graph_start_id, player, false);

    for (int i = 0; i < current_neighbor_nodes.size(); i++)
    {
        current_neighbor_nodes.my_vec_[i].nearest_node_id = Node::graph_start_id;
        int heuristic_distance;
        if (player == Square::PlayerA)
            heuristic_distance = board_size - current_neighbor_nodes.my_vec_[i].id / board_size;
        else
            heuristic_distance = board_size - current_neighbor_nodes.my_vec_[i].id % board_size;
        current_neighbor_nodes.my_vec_[i].distance += heuristic_distance;
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
        current_neighbor_nodes = get_connected_nodes(current_node.id, player, false);

        for (int i = 0; i < current_neighbor_nodes.size(); i++)
        {
            Node neighbor_node = current_neighbor_nodes.my_vec_[i];

            if (neighbor_node.id == Node::graph_end_id) //found connection to end node
                return true;

            if (!node_in_closed_set[neighbor_node.id])
            {
                int heuristic_distance;
                if (player == Square::PlayerA)
                    heuristic_distance = board_size - neighbor_node.id / board_size;
                else
                    heuristic_distance = board_size - neighbor_node.id % board_size;
                
                //Step 4a: if neighbor node is in open set and its distance to start node through current node is lower than its current distance to start node, then update its distance to start node and nearest neighbor id in open set
                if (open_set.contains_id(neighbor_node.id))
                {
                    Node* open_set_node_ptr = open_set.member_with_id(neighbor_node.id);
                    if (current_node.distance + 1 + heuristic_distance < open_set_node_ptr->distance)
                    {
                        open_set_node_ptr->distance = current_node.distance + 1 + heuristic_distance;
                        open_set_node_ptr->nearest_node_id = current_node.id;
                        //open_set.sort();
                    }
                }
                else   //Step 4b: if did not find neighbor node in open set then add it to open set with nearest neighbor id as current node id
                {
                    neighbor_node.nearest_node_id = current_node.id;
                    neighbor_node.distance += current_node.distance + heuristic_distance;
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
void ProcessBoard::fill_board_randomly(Square player, int node_id_as_next_move, std::vector<int> &empty_squares_vector_filled_randomly)
{
    int turns_by_player_A = 0, turns_by_player_B = 0;

    //current move
    hex_board[node_id_as_next_move / board_size][node_id_as_next_move % board_size] = player;

    if (player == Square::PlayerA)
        turns_by_player_A++;
    else
        turns_by_player_B++;

    for (unsigned int i = 0; i < empty_squares_vector_filled_randomly.size(); i++)
    {
        if (empty_squares_vector_filled_randomly[i] == node_id_as_next_move)
        {
            cout << "\n\n\nERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR \n\n" << endl;
            cout << "empty_squares_to_fill_randomly[i] == node_id_as_next_move" << endl;
            exit(0);
        }

        player = (player == Square::PlayerA ? Square::PlayerB : Square::PlayerA);

        hex_board[empty_squares_vector_filled_randomly[i] / board_size][empty_squares_vector_filled_randomly[i] % board_size] = player;

        if (player == Square::PlayerA)
            turns_by_player_A++;
        else
            turns_by_player_B++;
    }

    //printf("\rturns_by_player_A %d, turns_by_player_B %d", turns_by_player_A, turns_by_player_B);

}

bool ProcessBoard::dfs_search(int node_id, Square& player)
{
    //mark node as visited
    if(node_id >= 0)
        hex_board_visited[node_id / board_size][node_id % board_size] = true;

    //get connected nodes
    MyPriorityQueue current_neighbor_nodes = get_connected_nodes(node_id, player, true);

    // recursively process all the adjacent vertices of the node 
    for (int i = 0; i < current_neighbor_nodes.size(); i++)
    {
        int visiting_node_id = current_neighbor_nodes.my_vec_[i].id;
        
        if (visiting_node_id == Node::graph_end_id)  //connection found to end node
            return true;

        if (!hex_board_visited[visiting_node_id / board_size][visiting_node_id % board_size])
            if(dfs_search(visiting_node_id, player))    //if recursive dfs_search returned true, end now and return true upwards
                return true;
    }
    //connection not found to end node
    return false;
}

bool ProcessBoard::game_won_check_dfs(Square player)
{
    //make visited nodes false
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            hex_board_visited[i][j] = false;
        }
    }

    return dfs_search(Node::graph_start_id, player);
}

#include <iostream>
#include "Node.h"
#include "ProcessHexBoardClass.h"

using namespace std;

ProcessHexBoardClass::ProcessHexBoardClass()
{
    //board_size_ = PlayHexGameClass::board_size_;

    //copy hex board
    hex_board_copy_ = new Square * [board_size_];
    hex_board_visited_ = new bool* [board_size_];
    for (int i = 0; i < board_size_; i++)
    {
        hex_board_copy_[i] = new Square[board_size_];
        hex_board_visited_[i] = new bool[board_size_];
    }
}

ProcessHexBoardClass::~ProcessHexBoardClass()
{
    for (int i = 0; i < board_size_; i++)
    {
        delete[] hex_board_copy_[i];
        delete[] hex_board_visited_[i];
    }
    delete[] hex_board_copy_;
    delete[] hex_board_visited_;

}

void ProcessHexBoardClass::CopyHexBoard(Square** hex_board_data)
{
    for (int i = 0; i < board_size_; i++)
    {
        for (int j = 0; j < board_size_; j++)
        {
            hex_board_copy_[i][j] = hex_board_data[i][j];
        }
    }
}

bool ProcessHexBoardClass::BoundsCheck(const int row_index, const int col_index)
{
    if (row_index >= board_size_ || col_index >= board_size_ || row_index < 0 || col_index < 0)
        return false;
    return true;
}

void ProcessHexBoardClass::AddNeighborNodes(const int row_index, const int col_index, const Square& player, const bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes)
{
    if (BoundsCheck(row_index, col_index) && hex_board_copy_[row_index][col_index] == player)
        if (!unvisited_only || !hex_board_visited_[row_index][col_index])
            current_neighbor_nodes.push(Node(row_index, col_index, board_size_));

    //if (row_index >= 0 && row_index < board_size_ && col_index >= 0 && col_index < board_size_ && hex_board_[row_index][col_index] == player)
    //    if (!unvisited_only || !hex_board_visited_[row_index][col_index])
    //        current_neighbor_nodes.push(Node(row_index, col_index, board_size_));
}

MyPriorityQueue ProcessHexBoardClass::GetNeighborNodes(int node_id, Square player, bool unvisited_only)
{
    int row_index = node_id / board_size_;
    int col_index = node_id % board_size_;
    
    MyPriorityQueue current_neighbor_nodes;
    current_neighbor_nodes.clear();
    if (node_id >= 0)
    {
        //connected nodes
        AddNeighborNodes(row_index - 1, col_index, player, unvisited_only, current_neighbor_nodes);
        AddNeighborNodes(row_index, col_index - 1, player, unvisited_only, current_neighbor_nodes);
        AddNeighborNodes(row_index + 1, col_index - 1, player, unvisited_only, current_neighbor_nodes);
        AddNeighborNodes(row_index + 1, col_index, player, unvisited_only, current_neighbor_nodes);
        AddNeighborNodes(row_index, col_index + 1, player, unvisited_only, current_neighbor_nodes);
        AddNeighborNodes(row_index - 1, col_index + 1, player, unvisited_only, current_neighbor_nodes);

        //get connection to imaginary start and end nodes
        if (player == Square::PlayerA)
        {
            //dont add start node if asking for unvisited only as start node is always visited initially by dfs algorithm
            if (row_index == 0 && !unvisited_only)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (row_index == board_size_ - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
        else if (player == Square::PlayerB)
        {
            //dont add start node if asking for unvisited only as start node is always visited initially by dfs algorithm
            if (col_index == 0 && !unvisited_only)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (col_index == board_size_ - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
    }
    else
    {//imaginary start or end node
        if (player == Square::PlayerA)
        {
            if (node_id == Node::graph_start_id)
                for (int j = 0; j < board_size_; j++)
                    if (hex_board_copy_[0][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(0, j, board_size_);
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int j = 0; j < board_size_; j++)
                    if (hex_board_copy_[board_size_ - 1][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(board_size_ - 1, j, board_size_);
                        current_neighbor_nodes.push(connected_node);
                    }
        }
        else if (player == Square::PlayerB)
        {
            if (node_id == Node::graph_start_id)
                for (int i = 0; i < board_size_; i++)
                    if (hex_board_copy_[i][0] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, 0, board_size_);
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int i = 0; i < board_size_; i++)
                    if (hex_board_copy_[i][board_size_ - 1] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, board_size_ - 1, board_size_);
                        current_neighbor_nodes.push(connected_node);
                    }
        }
    }
    //return current_neighbor_nodes;
    return current_neighbor_nodes;
}

void ProcessHexBoardClass::FillBoardRandomly(Square player, int node_id_as_next_move, std::vector<int> &empty_squares_vector_filled_randomly)
{
    int turns_by_player_A = 0, turns_by_player_B = 0;

    //current move
    hex_board_copy_[node_id_as_next_move / board_size_][node_id_as_next_move % board_size_] = player;

    if (player == Square::PlayerA)
        turns_by_player_A++;
    else
        turns_by_player_B++;

    for (unsigned int i = 0; i < empty_squares_vector_filled_randomly.size(); i++)
    {
        if (empty_squares_vector_filled_randomly[i] == node_id_as_next_move)
        {
            printf("\n\n\nERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR \n\n");
            printf("empty_squares_to_fill_randomly[i] == node_id_as_next_move");
            exit(0);
        }

        player = (player == Square::PlayerA ? Square::PlayerB : Square::PlayerA);

        hex_board_copy_[empty_squares_vector_filled_randomly[i] / board_size_][empty_squares_vector_filled_randomly[i] % board_size_] = player;

        if (player == Square::PlayerA)
            turns_by_player_A++;
        else
            turns_by_player_B++;
    }

    //printf("\rturns_by_player_A %d, turns_by_player_B %d", turns_by_player_A, turns_by_player_B);
}

bool ProcessHexBoardClass::DfsSearch(int node_id, Square& player)
{
    //mark node as visited
    if(node_id >= 0)
        hex_board_visited_[node_id / board_size_][node_id % board_size_] = true;

    //get connected nodes
    MyPriorityQueue current_neighbor_nodes = move(GetNeighborNodes(node_id, player, true));

    // recursively process all the adjacent vertices of the node 
    for (int i = 0; i < current_neighbor_nodes.size(); i++)
    {
        int visiting_node_id = current_neighbor_nodes.my_vec_[i].id;
        
        if (visiting_node_id == Node::graph_end_id)  //connection found to end node
            return true;

        if (!hex_board_visited_[visiting_node_id / board_size_][visiting_node_id % board_size_])
            if(DfsSearch(visiting_node_id, player))    //if recursive DfsSearch returned true, end now and return true upwards
                return true;
    }
    //connection not found to end node
    return false;
}

bool ProcessHexBoardClass::GameWonCheckDfs(Square player)
{
    //make visited nodes false
    for (int i = 0; i < board_size_; i++)
    {
        for (int j = 0; j < board_size_; j++)
        {
            hex_board_visited_[i][j] = false;
        }
    }

    //recursively search for connection to end node on hex board
    return DfsSearch(Node::graph_start_id, player);
}

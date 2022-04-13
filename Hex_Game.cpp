// Hex_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <tuple>
#include <vector>
#include "My_Priority_Queue.h"
#include "Node.h"
#include "Edge.h"
#include "PlayerGraph.h"

using namespace std;

//Function declerations
void InitializeHexBoard(int hex_board_size, string& player_A_name, string& player_B_name);
void PrintHexBoard();

//program variables
int hex_board_size = -1;
PlayerGraph player_A;
PlayerGraph player_B;
vector<char> hex_board;

int main()
{
    hex_board_size = 11;
    string player_A_name = "Prashant";
    string player_B_name = "Computer";
    InitializeHexBoard(hex_board_size, player_A_name, player_B_name);
    PrintHexBoard();
}

int get_node_id(int row_index, int col_index)
{
    return row_index * hex_board_size + col_index;
}

tuple<int, int> get_node_indices(int node_id)
{
    return make_tuple(node_id / hex_board_size, node_id % hex_board_size);
}

void InitializeHexBoard(int hex_board_size, string& player_A_name, string& player_B_name)
{
    player_A = PlayerGraph(player_A_name, 'X');
    player_B = PlayerGraph(player_B_name, 'O');
    //player A will make graph in vertical direction
    //player B will make graph in horizontal direction
    
    //we will add two imaginary nodes - graph start and end nodes, to players graphs
    //we will use dijkstra's algorithm to find shortest path between these imaginary nodes
    //we will use the case of finding a solvable path between these two imaginary nodes as reaching the game's end
    //we will connect a player's side edge nodes to these imaginary nodes at start of game

    player_A.nodes_list_.push_back(Node(Node::graph_start_id, Node::kNullId));
    player_A.nodes_list_.push_back(Node(Node::graph_end_id, Node::kNullId));
    player_B.nodes_list_.push_back(Node(Node::graph_start_id, Node::kNullId));
    player_B.nodes_list_.push_back(Node(Node::graph_end_id, Node::kNullId));
    for (int i = 0; i < hex_board_size; i++)
    {
        player_A.edge_list_.push_back(Edge(get_node_id(0, i), Node::graph_start_id));
        player_A.edge_list_.push_back(Edge(get_node_id(hex_board_size - 1, i), Node::graph_end_id));
        player_B.edge_list_.push_back(Edge(get_node_id(i, 0), Node::graph_start_id));
        player_B.edge_list_.push_back(Edge(get_node_id(i, hex_board_size - 1), Node::graph_end_id));
    }
    for (int id = 0; id < hex_board_size*hex_board_size; id++)
        hex_board.push_back('.');
}

void PrintHexBoard()
{
    cout << '\n';
    cout << "\t\t\tHex Game" << '\n' << '\n';
    cout << "\t\t" << player_A.player_identifier << " : " << player_A.name_ << "  |  "
        << player_B.player_identifier << " : " << player_B.name_ << '\n';
    cout << '\n';
    for (int i = 0; i < hex_board_size; i++)
    {
        cout << '\t';
        for (int print_blank = 0; print_blank < i; print_blank++)
            cout << "  ";
        for (int j = 0; j < hex_board_size; j++)
        {
            cout << hex_board[get_node_id(i,j)];
            if ((j + 1) % hex_board_size != 0)
                cout << " - ";
            else
                cout << '\n';
        }
        if ((i + 1) % hex_board_size != 0)
        {
            cout << '\t';
            for (int print_blank = 0; print_blank < i; print_blank++)
                cout << "  ";
            for (int j = 0; j < 2 * hex_board_size - 1; j++)
            {
                if(j % 2 == 0)
                    cout << " \\";
                else
                    cout << " /";
            }
            cout << '\n';
        }
    }
    cout << endl;
}

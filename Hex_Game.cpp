// Hex_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <limits>
#include <list>
#include <tuple>
#include <array>
#include "My_Priority_Queue.h"
#include "Node.h"
#include "Edge.h"
#include "PlayerGraph.h"

using namespace std;

//Function declerations
void initialize(int size_hex_board, string& player_A_name, string& player_B_name);
void print_hex_board();
void RunGame();

enum class Square : char
{
    PlayerA = 'X',
    PlayerB = 'O',
    Empty = '.',
};

//program variables
int size_hex_board = -1;
PlayerGraph player_A;
PlayerGraph player_B;
Square** hex_board;


int main()
{
    //disable automatic cout flush to terminal
    ios::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
    
    //cout << "input hex board size:";
    //cin >> size_hex_board;
    //cout << "player A name:";
    //string player_A_name;
    //cin >> player_A_name;
    size_hex_board = 7;
    string player_A_name = "Prashant";
    string player_B_name = "Computer";
    initialize(size_hex_board, player_A_name, player_B_name);
    print_hex_board();
    RunGame();
}

int get_node_id(int row_index, int col_index)
{
    return row_index * size_hex_board + col_index;
}

tuple<int, int> get_node_indices(int node_id)
{
    return make_tuple(node_id / size_hex_board, node_id % size_hex_board);
}

void initialize(int size_hex_board, string& player_A_name, string& player_B_name)
{
    player_A = PlayerGraph(player_A_name);
    player_B = PlayerGraph(player_B_name);
    //player A will make graph in vertical direction
    //player B will make graph in horizontal direction
    
    //we will add two imaginary nodes - graph start and end nodes, to players graphs
    //we will use dijkstra's algorithm to find shortest path between these imaginary nodes
    //we will use the case of finding a solvable path between these two imaginary nodes as reaching the game's end
    //we will connect a player's side edge nodes to these imaginary nodes at start of game

    for (int i = 0; i < size_hex_board; i++)
    {
        player_A.edge_list_.push_back(Edge(get_node_id(0, i), Node::graph_start_id));
        player_A.edge_list_.push_back(Edge(get_node_id(size_hex_board - 1, i), Node::graph_end_id));
        player_B.edge_list_.push_back(Edge(get_node_id(i, 0), Node::graph_start_id));
        player_B.edge_list_.push_back(Edge(get_node_id(i, size_hex_board - 1), Node::graph_end_id));
    }
    hex_board = new Square* [size_hex_board];
    for (int i = 0; i < size_hex_board; i++)
        hex_board[i] = new Square[size_hex_board];
    for (int i = 0; i < size_hex_board; i++)
    {
        for (int j = 0; j < size_hex_board; j++)
        {
            hex_board[i][j] = Square::Empty;
        }
    }
}

void print_hex_board()
{
    cout << '\n' << '\n';
    cout << "\t\t\tHex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << " : " << player_A.name_ << "  |  "
        << static_cast<char>(Square::PlayerB) << " : " << player_B.name_ << '\n';
    cout << '\n' << '\n' << '\t' << "      ";
    for (int i = 0; i < size_hex_board; i++)
        cout << static_cast<char>(Square::PlayerA) << "   ";
    cout << '\n' << '\n';
    for (int i = 0; i < size_hex_board; i++)
    {
        cout << '\t';
        for (int print_blank = 0; print_blank < i; print_blank++)
            cout << "  ";
        cout << static_cast<char>(Square::PlayerB) << "       ";
        for (int j = 0; j < size_hex_board; j++)
        {
            cout << static_cast<char>(hex_board[i][j]);
            if (j < size_hex_board - 1)
                cout << " - ";
        }
        cout << "       " << static_cast<char>(Square::PlayerB) << '\n';
        if ((i + 1) % size_hex_board != 0)
        {
            cout << '\t' << '\t';
            for (int print_blank = 0; print_blank < i; print_blank++)
                cout << "  ";
            for (int j = 0; j < 2 * size_hex_board - 1; j++)
            {
                if(j % 2 == 0)
                    cout << " \\";
                else
                    cout << " /";
            }
            cout << '\n';
        }
    }
    cout << '\n' << '\n' << '\t' << '\t';
    for (int print_blank = 0; print_blank < size_hex_board; print_blank++)
        cout << "  ";
    for (int i = 0; i < size_hex_board; i++)
        cout << static_cast<char>(Square::PlayerA) << "   ";
    cout << '\n' << '\n';
    cout << endl;
}

list<Node> get_connected_nodes(int node_id)
{
    list<Node> connected_nodes_list;
    int i, j;
    tie(i, j) = get_node_indices(node_id);
    if (i > 0 && hex_board[i - 1][j] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i - 1, j));
    if (j > 0 && hex_board[i][j - 1] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i, j - 1));
    if (i < size_hex_board - 1 && hex_board[i + 1][j] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i + 1, j));
    if (j < size_hex_board - 1 && hex_board[i][j + 1] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i, j + 1));
    if(i > 0 && j < size_hex_board - 1 && hex_board[i - 1][j + 1] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i -1, j + 1));
    if (i < size_hex_board - 1 && j > 0 && hex_board[i + 1][j - 1] == hex_board[i][j])
        connected_nodes_list.push_back(Node(i + 1, j - 1));
    return connected_nodes_list;
}

void get_user_input(Square user)
{
    int i = -1, j = -1;
    while (true)
    {
        if (user == Square::PlayerA)
            cout << player_A.name_ << " enter next move:";
        else
            cout << player_B.name_ << " enter next move:";
        if (cin >> i >> j)
        {
            if (i >= 0 && j >= 0 && i < size_hex_board && j < size_hex_board)
            {
                if (hex_board[i][j] == Square::Empty)
                    break;
                else
                    cout << "Square already taken." << endl;
            }
            else
                cout << "Out of bounds input." << endl;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        i = -1, j = -1;
    }
    if (user == Square::PlayerA)
        hex_board[i][j] = Square::PlayerA;
    else
        hex_board[i][j] = Square::PlayerB;
}

void RunGame()
{
    bool game_won = false;
    int moves = 0;
    while (!game_won)
    {
        get_user_input(Square::PlayerA);
        get_user_input(Square::PlayerB);
        print_hex_board();
        moves++;
        if (moves == 10)
            game_won = true;
    }
}

// Hex_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <limits>
#include <list>
#include <tuple>
#include <vector>
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
    
    cout << "input hex board size:";
    cin >> size_hex_board;
    cout << "player A name:";
    string player_A_name;
    cin >> player_A_name;
    //size_hex_board = 3;
    //string player_A_name = "Prashant";
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
        cout << static_cast<char>(Square::PlayerA) << i << "  ";
    cout << '\n' << '\n';
    for (int i = 0; i < size_hex_board; i++)
    {
        cout << '\t';
        for (int print_blank = 0; print_blank < i; print_blank++)
            cout << "  ";
        cout << static_cast<char>(Square::PlayerB) << i << "      ";
        for (int j = 0; j < size_hex_board; j++)
        {
            cout << static_cast<char>(hex_board[i][j]);
            if (j < size_hex_board - 1)
                cout << " - ";
        }
        cout << "       " << static_cast<char>(Square::PlayerB) << i << '\n';
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
        cout << static_cast<char>(Square::PlayerA) << i << "  ";
    cout << '\n' << '\n';
    cout << endl;
}

list<Node> get_connected_nodes(int node_id, Square player)
{
    list<Node> connected_nodes_list;
    if (node_id >= 0)
    {
        int i, j;
        tie(i, j) = get_node_indices(node_id);
        if (i > 0 && hex_board[i - 1][j] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i - 1, j)));
        if (j > 0 && hex_board[i][j - 1] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i, j - 1)));
        if (i < size_hex_board - 1 && hex_board[i + 1][j] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i + 1, j)));
        if (j < size_hex_board - 1 && hex_board[i][j + 1] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i, j + 1)));
        if (i > 0 && j < size_hex_board - 1 && hex_board[i - 1][j + 1] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i - 1, j + 1)));
        if (i < size_hex_board - 1 && j > 0 && hex_board[i + 1][j - 1] == hex_board[i][j])
            connected_nodes_list.push_back(Node(get_node_id(i + 1, j - 1)));
        //get connection to imaginary start and end nodes
        if (player == Square::PlayerA)
        {
            if (i == 0)
                connected_nodes_list.push_back(Node(Node::graph_start_id));
            if (i == size_hex_board - 1)
                connected_nodes_list.push_back(Node(Node::graph_end_id));
        }
        else if (player == Square::PlayerB)
        {
            if (j == 0)
                connected_nodes_list.push_back(Node(Node::graph_start_id));
            if (j == size_hex_board - 1)
                connected_nodes_list.push_back(Node(Node::graph_end_id));
        }
    }
    else
    {//imaginary start or end node
        if (player == Square::PlayerA)
        {
            if (node_id == Node::graph_start_id)
                for (int j = 0; j < size_hex_board; j++)
                    if (hex_board[0][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(get_node_id(0, j));
                        connected_nodes_list.push_back(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int j = 0; j < size_hex_board; j++)
                    if (hex_board[size_hex_board - 1][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(get_node_id(size_hex_board - 1, j));
                        connected_nodes_list.push_back(connected_node);
                    }
        }
        else if (player == Square::PlayerB)
        {
            if (node_id == Node::graph_start_id)
                for (int i = 0; i < size_hex_board; i++)
                    if (hex_board[i][0] == Square::PlayerB)
                    {
                        Node connected_node = Node(get_node_id(i, 0));
                        connected_nodes_list.push_back(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int i = 0; i < size_hex_board; i++)
                    if (hex_board[i][size_hex_board - 1] == Square::PlayerB)
                    {
                        Node connected_node = Node(get_node_id(i, size_hex_board - 1));
                        connected_nodes_list.push_back(connected_node);
                    }
        }
    }
    return connected_nodes_list;
}


bool game_won_check(Square player)
{
    //DijkstrasAlgorithmImplementation

    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    MyPriorityQueue closed_set;

    //Step 1: add imaginary start node to closed set
    closed_set.push(Node(Node::graph_start_id));
    
    //Step 2: add neighbors of start node to open set
    list<Node> current_neighbors = get_connected_nodes(Node::graph_start_id, player);
    for (Node& node : current_neighbors)
    {
        node.nearest_node_id = Node::graph_start_id;
        open_set.push(node);
    }

    //loop over open set until it is empty
    while (open_set.size() > 0)
    {
        //Step 3: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Node current_node = open_set.get_and_pop_top();

        closed_set.push(current_node);
        
        //Step 4: for each neighbor city of current city which is not in closed set
        current_neighbors = get_connected_nodes(current_node.id, player);

        for (Node neighbor_node : current_neighbors)
        {
            if (!closed_set.contains_id(neighbor_node.id))
            {
                //Step 4a: if neighbor node is in open set and its distance to start node through current node is lower than its current distance to start node, then update its distance to start node and nearest neighbor id in open set
                if (open_set.contains_id(neighbor_node.id))
                {
                    Node* open_set_node_ptr = open_set.member_with_id(neighbor_node.id);
                    if (current_node.distance + 1 < open_set_node_ptr->distance)
                    {
                        open_set_node_ptr->distance = current_node.distance + 1;
                        open_set_node_ptr->nearest_node_id = current_node.id;
                        open_set.sort();
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
    }
    //dijkstras algoritm completed

    //find a path between start and end city
    if(closed_set.contains_id(Node::graph_end_id))
    {
        Node* graph_end_node_ptr = closed_set.member_with_id(Node::graph_end_id);
        return true;
    }
    return false;
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
    {
        hex_board[i][j] = Square::PlayerA;
        player_A.nodes_list_.push_back(Node(get_node_id(i, j)));
    }
    else
    {
        hex_board[i][j] = Square::PlayerB;
        player_B.nodes_list_.push_back(Node(get_node_id(i, j)));
    }
}

void RunGame()
{
    int moves = 0;
    int player_won = 0;
    while (player_won == 0)
    {
        moves++;
        get_user_input(Square::PlayerA);
        //check game won by player A
        if (game_won_check(Square::PlayerA))
        {
            player_won = 1;
            break;
        }
        get_user_input(Square::PlayerB);
        //check game won by player B
        if (game_won_check(Square::PlayerB))
        {
            player_won = 2;
            break;
        }
        print_hex_board();
    }
    print_hex_board();
    cout << '\n' << (player_won == 1 ? player_A.name_ : player_B.name_) << " won!!!" << '\n' << endl;
    cout << "Game won in " << moves << " moves!" << endl;
    
}

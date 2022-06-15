// Hex_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Author: Prashant Kumar
// 
// Date April 14th 2022
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
void initialize_players();
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
char player_square = 'X', computer_square;

int main()
{
    //disable automatic cout flush to terminal, this helps in printing hex board quickly to terminal.
    ios::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
    
    size_hex_board = 5;
 
    initialize_players();
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

void initialize_players()
{
    cout << '\n' << '\n';
    cout << "\t\t\t  Hex Game\n\n";
    cout << "Player v/s Computer\n\n";
    cout << "X goes first and takes vertical direction, O goes second and takes horizontal direction.\n\n";
    cout << "Player, pick X or O:";

    while (1)
    {
        string user_choice;
        getline(cin, user_choice);
        if (user_choice == "X")
        {
            player_square = static_cast<char>(Square::PlayerA);
            computer_square = static_cast<char>(Square::PlayerB);
            break;
        }
        else if (user_choice == "O")
        {
            player_square = static_cast<char>(Square::PlayerB);
            computer_square = static_cast<char>(Square::PlayerA);
            break;
        }
        else
        {
            cout << "\nIncorrect input.\nPlayer, pick X or O:";
        }
    }


    //cout << "input hex board size:";
    //cin >> size_hex_board;
    cout << "Player Name:";
    string player_name;
    getline(cin, player_name);
    //string player_name = "Prashant";
    string computer_name = "Computer";

    if (player_square == 'X')
    {
        player_A = PlayerGraph(player_name, player_square);
        player_B = PlayerGraph(computer_name, computer_square);
    }
    else
    {
        player_A = PlayerGraph(computer_name, computer_square);
        player_B = PlayerGraph(player_name, player_square);
    }
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
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << " : " << player_A.name_ << "  |  top-to-bottom" << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << " : " << player_B.name_ << "  |  left-to-right" << '\n';
    cout << '\n';
    
    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= size_hex_board; i++)
        printf("%2d  ", i);
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < size_hex_board; i++)
    {
        //row initial blank spaces
        cout << '\t';
        for (int print_blank = 0; print_blank < i; print_blank++)
            cout << " ";
        
        //row label left
        //cout << static_cast<char>(Square::PlayerB) << letter << "      ";
        cout << letter << "  \\  ";

        //board
        for (int j = 0; j < size_hex_board; j++)
        {
            cout << static_cast<char>(hex_board[i][j]);
            if (j < size_hex_board - 1)
                cout << "   ";
        }

        //row label right
        cout << "  \\  " << letter++ << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < size_hex_board - 3; print_blank++)
        cout << " ";
    
    //footer row
    for (int i = 1; i <= size_hex_board; i++)
        printf("%2d  ", i);

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

void read_input(int& i, int& j)
{
    char letter = '?';
    int number = -1;
    while (number == -1)
    {
        string input;
        getline(cin, input);

        int letter_value = tolower(input.at(0));
        if (letter_value >= 97 && letter_value <= 122)
        {
            letter = letter_value;
            number = stoi(input.substr(1, input.size() - 1));
        }
        else if (letter_value >= 48 && letter_value <= 57)
        {
            letter = tolower(input.at(input.size() - 1));
            number = stoi(input.substr(0, input.size() - 1));
        }
        else
        {
            cout << "Invalid input!\n";
        }
    }
    i = letter - 97;
    j = number - 1;
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

        read_input(i, j);

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

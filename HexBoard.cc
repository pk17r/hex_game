#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <type_traits>
#include "Node.h"
#include "HexBoard.h"

using namespace std;

std::ostream& operator << (std::ostream& os, const Square& obj)
{
    os << static_cast<std::underlying_type<Square>::type>(obj);
    return os;
}

void HexBoard::HexBoardInitialize()
{
    //create hex board memory space
    //create memory space for visited flag for dfs algo
    hex_board_ = new Square * [get_board_size_()];
    hex_board_visited_ = new bool* [get_board_size_()];
    for (int i = 0; i < get_board_size_(); i++)
    {
        hex_board_[i] = new Square[get_board_size_()];
        hex_board_visited_[i] = new bool[get_board_size_()];
    }
    for (int node_id = 0; node_id < get_board_size_() * get_board_size_(); node_id++)
    {
        set_hex_board_ownership_(node_id, Square::Empty);
    }
}

HexBoard::~HexBoard()
{
    for (int i = 0; i < get_board_size_(); i++)
    {
        delete[] hex_board_[i];
        delete[] hex_board_visited_[i];
    }
    delete[] hex_board_;
    delete[] hex_board_visited_;
    cout << "~HexBoard() owner: " << HexBoardOwnerClass << endl;
}

const int HexBoard::get_board_size_()
{
    return board_size_;
}

const bool HexBoard::BoundsCheck(const int row_index, const int col_index)
{
    if (row_index >= board_size_ || col_index >= board_size_ || row_index < 0 || col_index < 0)
        return false;
    return true;
}

const int HexBoard::get_row_index_(const int node_id)
{
    return node_id / board_size_;
}

const int HexBoard::get_col_index_(const int node_id)
{
    return node_id % board_size_;
}

const int HexBoard::get_node_id_(const int row_index, const int col_index)
{
    return row_index * board_size_ + col_index;
}

const char HexBoard::get_row_char_(const int node_id)
{
    return 'a' + get_row_index_(node_id);
}

const int HexBoard::get_col_number_(const int node_id)
{
    return get_col_index_(node_id) + 1;
}

bool HexBoard::is_node_visited_(const int node_id)
{
    return hex_board_visited_[get_row_index_(node_id)][get_col_index_(node_id)];
}

void HexBoard::set_node_as_visited_(const int node_id)
{
    hex_board_visited_[get_row_index_(node_id)][get_col_index_(node_id)] = true;
}

void HexBoard::AddNeighborNodes(const int row_index, const int col_index, const Square& player, const bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes)
{
    if (BoundsCheck(row_index, col_index) && hex_board_[row_index][col_index] == player)
        if (!unvisited_only || !hex_board_visited_[row_index][col_index])
            current_neighbor_nodes.push(Node(row_index, col_index, get_board_size_()));
}

MyPriorityQueue HexBoard::GetNeighborNodes(const int node_id, const Square player, const bool unvisited_only)
{
    int row_index = get_row_index_(node_id);
    int col_index = get_col_index_(node_id);
    
    MyPriorityQueue current_neighbor_nodes;

    if (node_id >= 0)   //hex board nodes
    {
        //connected hex board nodes
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
            else if (row_index == get_board_size_() - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
        else if (player == Square::PlayerB)
        {
            //dont add start node if asking for unvisited only as start node is always visited initially by dfs algorithm
            if (col_index == 0 && !unvisited_only)
                current_neighbor_nodes.push(Node(Node::graph_start_id));
            else if (col_index == get_board_size_() - 1)
                current_neighbor_nodes.push(Node(Node::graph_end_id));
        }
    }
    else    //imaginary start or end node
    {
        if (player == Square::PlayerA)
        {
            if (node_id == Node::graph_start_id)
                for (int j = 0; j < get_board_size_(); j++)
                    if (hex_board_[0][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(0, j, get_board_size_());
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int j = 0; j < get_board_size_(); j++)
                    if (hex_board_[get_board_size_() - 1][j] == Square::PlayerA)
                    {
                        Node connected_node = Node(get_board_size_() - 1, j, get_board_size_());
                        current_neighbor_nodes.push(connected_node);
                    }
        }
        else if (player == Square::PlayerB)
        {
            if (node_id == Node::graph_start_id)
                for (int i = 0; i < get_board_size_(); i++)
                    if (hex_board_[i][0] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, 0, get_board_size_());
                        current_neighbor_nodes.push(connected_node);
                    }
            if (node_id == Node::graph_end_id)
                for (int i = 0; i < get_board_size_(); i++)
                    if (hex_board_[i][get_board_size_() - 1] == Square::PlayerB)
                    {
                        Node connected_node = Node(i, get_board_size_() - 1, get_board_size_());
                        current_neighbor_nodes.push(connected_node);
                    }
        }
    }
    
    return current_neighbor_nodes;
}

bool HexBoard::DfsSearch(int node_id, Square& player)
{
    //mark node as visited
    if (node_id >= 0)
        set_node_as_visited_(node_id);

    //get connected nodes
    MyPriorityQueue current_neighbor_nodes = GetNeighborNodes(node_id, player, true);

    // recursively process all the adjacent vertices of the node 
    for (int i = 0; i < current_neighbor_nodes.size(); i++)
    {
        int visiting_node_id = current_neighbor_nodes.my_vec_[i].id;
        
        if (visiting_node_id == Node::graph_end_id)  //connection found to end node
            return true;

        if (!is_node_visited_(visiting_node_id))
            if(DfsSearch(visiting_node_id, player))    //if recursive DfsSearch returned true, end now and return true upwards
                return true;
    }
    //connection not found to end node
    return false;
}

bool HexBoard::GameWonCheckDfsAlgo(Square player)
{
    //make visited nodes false
    for (int i = 0; i < get_board_size_(); i++)
    {
        for (int j = 0; j < get_board_size_(); j++)
        {
            hex_board_visited_[i][j] = false;
        }
    }

    //recursively search for connection to end node on hex board
    return DfsSearch(Node::graph_start_id, player);
}

void HexBoard::set_hex_board_ownership_(const int node_id, const Square player)
{
    hex_board_[get_row_index_(node_id)][get_col_index_(node_id)] = player;
}

void HexBoard::PrintHexBoard()
{
    cout << '\n';
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << "  |  top-to-bottom  | " << playerA_name_ << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << "  |  left-to-right  | " << playerB_name_ << '\n';
    cout << '\n' << '\n';

    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("%3d  ", i);
    cout << '\n';

    cout << '\t' << "     ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf(" --  ");
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < 2 * get_board_size_() - 1; i++)
    {
        if (i % 2 == 0)
        {
            //row initial blank spaces
            cout << '\t';
            for (int print_blank = 0; print_blank < i + i / 2; print_blank++)
                cout << " ";

            //row label left
            cout << letter << "  \\   ";

            //board
            for (int j = 0; j < get_board_size_(); j++)
            {
                cout << static_cast<char>(hex_board_[i / 2][j]);
                if (j < get_board_size_() - 1)
                    cout << "    ";
            }

            //row label right
            cout << "   \\  " << letter++;
        }

        cout << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < 2 * get_board_size_() - 4 + get_board_size_(); print_blank++)
        cout << " ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("--   ");

    //footer row
    cout << '\n' << '\t' << '\t' << " ";
    for (int print_blank = 0; print_blank < 2 * get_board_size_() - 5 + get_board_size_(); print_blank++)
        cout << " ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("%3d  ", i);

    cout << '\n' << '\n';

    PrintOwnershipCountReturnEmptySquares(true);

    cout << endl;
}

unsigned int HexBoard::PrintOwnershipCountReturnEmptySquares(bool print)
{
    unsigned int empty = 0, playerA = 0, playerB = 0, other = 0;
    for (int i = 0; i < get_board_size_(); i++)
    {
        for (int j = 0; j < get_board_size_(); j++)
        {
            switch (hex_board_[i][j])
            {
            case Square::Empty:
                empty++;
                break;
            case Square::PlayerA:
                playerA++;
                break;
            case Square::PlayerB:
                playerB++;
                break;
            default:
                other++;
            }
        }
    }
    if(print)
        cout << "SQUARES OWNERSHIP empty:" << empty << ", playerA:" << playerA << ", playerB:" << playerB << ", other:" << other << endl;
    
    assert(other == 0);
    assert(std::abs(static_cast<int>(playerA) - static_cast<int>(playerB)) <= 1);

    return empty;
}

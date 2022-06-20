#include <algorithm>
#include <chrono>
#include <iostream>
#include <type_traits>
#include "Node.h"
#include "ProcessHexBoardClass.h"

using namespace std;

std::ostream& operator << (std::ostream& os, const Square& obj)
{
    os << static_cast<std::underlying_type<Square>::type>(obj);
    return os;
}

void ProcessHexBoardClass::ProcessHexBoardClassInitialize()
{
    //create ProcessHexBoardClass hex board memory space
    //create memory space for visited flag for dfs algo
    hex_board_ = new Square * [get_board_size_()];
    hex_board_visited_ = new bool* [get_board_size_()];
    for (int i = 0; i < get_board_size_(); i++)
    {
        hex_board_[i] = new Square[get_board_size_()];
        hex_board_visited_[i] = new bool[get_board_size_()];
    }

    //setting seed for random number generator engine
    unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
    my_random_engine_ = default_random_engine(seed);
}

ProcessHexBoardClass::~ProcessHexBoardClass()
{
    for (int i = 0; i < get_board_size_(); i++)
    {
        delete[] hex_board_[i];
        delete[] hex_board_visited_[i];
    }
    delete[] hex_board_;
    delete[] hex_board_visited_;
}

void ProcessHexBoardClass::CopyHexBoardToProcessHexBoardClass(Square** hex_board_)
{
    for (int i = 0; i < get_board_size_(); i++)
    {
        for (int j = 0; j < get_board_size_(); j++)
        {
            this->hex_board_[i][j] = hex_board_[i][j];
        }
    }
}

const int ProcessHexBoardClass::get_board_size_()
{
    return board_size_;
}

const bool ProcessHexBoardClass::BoundsCheck(const int row_index, const int col_index)
{
    if (row_index >= board_size_ || col_index >= board_size_ || row_index < 0 || col_index < 0)
        return false;
    return true;
}

const int ProcessHexBoardClass::get_row_index_(const int node_id)
{
    return node_id / board_size_;
}

const int ProcessHexBoardClass::get_col_index_(const int node_id)
{
    return node_id % board_size_;
}

const int ProcessHexBoardClass::get_node_id_(const int row_index, const int col_index)
{
    return row_index * board_size_ + col_index;
}

const char ProcessHexBoardClass::get_row_char_(const int node_id)
{
    return 'a' + get_row_index_(node_id);
}

const int ProcessHexBoardClass::get_col_number_(const int node_id)
{
    return get_col_index_(node_id) + 1;
}

bool ProcessHexBoardClass::is_node_visited_(const int node_id)
{
    return hex_board_visited_[get_row_index_(node_id)][get_col_index_(node_id)];
}

void ProcessHexBoardClass::set_node_as_visited_(const int node_id)
{
    hex_board_visited_[get_row_index_(node_id)][get_col_index_(node_id)] = true;
}

void ProcessHexBoardClass::AddNeighborNodes(const int row_index, const int col_index, const Square& player, const bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes)
{
    if (BoundsCheck(row_index, col_index) && hex_board_[row_index][col_index] == player)
        if (!unvisited_only || !hex_board_visited_[row_index][col_index])
            current_neighbor_nodes.push(Node(row_index, col_index, get_board_size_()));
}

MyPriorityQueue ProcessHexBoardClass::GetNeighborNodes(const int node_id, const Square player, const bool unvisited_only)
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

void ProcessHexBoardClass::FillBoardRandomly(Square player, const int& node_id_as_next_move, std::vector<int> &empty_squares_vector_filled_randomly)
{
    //int turns_by_player_A = 0, turns_by_player_B = 0;

    //make current move on hex board
    hex_board_[get_row_index_(node_id_as_next_move)][get_col_index_(node_id_as_next_move)] = player;

    //if (player == Square::PlayerA)
    //    turns_by_player_A++;
    //else
    //    turns_by_player_B++;

    for (unsigned int i = 0; i < empty_squares_vector_filled_randomly.size(); i++)
    {
        if (empty_squares_vector_filled_randomly[i] == node_id_as_next_move)
        {
            printf("\n\n\nERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR \n\n");
            printf("empty_squares_to_fill_randomly[i] == node_id_as_next_move");
            exit(0);
        }

        player = (player == Square::PlayerA ? Square::PlayerB : Square::PlayerA);

        hex_board_[get_row_index_(empty_squares_vector_filled_randomly[i])][get_col_index_(empty_squares_vector_filled_randomly[i])] = player;

        //if (player == Square::PlayerA)
        //    turns_by_player_A++;
        //else
        //    turns_by_player_B++;
    }

    //printf("\rturns_by_player_A %d, turns_by_player_B %d", turns_by_player_A, turns_by_player_B);
}

bool ProcessHexBoardClass::DfsSearch(int node_id, Square& player)
{
    //mark node as visited
    if (node_id >= 0)
        set_node_as_visited_(node_id);

    //get connected nodes
    MyPriorityQueue current_neighbor_nodes = move(GetNeighborNodes(node_id, player, true));

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

bool ProcessHexBoardClass::GameWonCheckDfsAlgo(Square player)
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

int ProcessHexBoardClass::MonteCarloSimulationsToFindBestNextMove(const Square player, const std::vector<int>& empty_squares_vector_)
{
    /*
    -For each entry of empty squares run a simulation 1000 times

        - Fill all squares randomly

        - Check who won the game

        - Note win or loss for this simulation

        - Assign the entry with win / loss ratio

        - Return the entry with best win / loss ratio
    */

    //TIME NOTING START
    auto start = chrono::high_resolution_clock::now();
    //Simulation loop time clocks
    static std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1, t2;
    //time duration counters
    std::chrono::microseconds duration_shuffle_and_fill_up_board = static_cast<std::chrono::microseconds>(0),
        duration_who_won_using_dfs_algo = static_cast<std::chrono::microseconds>(0);

    //variables to track best win loss ratio move
    double best_win_loss_ratio = 0;
    int best_win_loss_ratio_node_id = -1;

    cout << "Running " << empty_squares_vector_.size() << "x" << num_of_simulations_ << " simulated trials" << endl;

    //initialize vector to shuffle empty squares
    std::vector<int> empty_squares_shuffle_vector;
    empty_squares_shuffle_vector.reserve(empty_squares_vector_.size() - 1);

    for (unsigned int i = 0; i < empty_squares_vector_.size(); i++)
    {
        int node_id_as_next_move = empty_squares_vector_[i];
        unsigned int wins = 0, losses = 0;

        for (unsigned int j = 0; j < empty_squares_vector_.size(); j++)
            if (empty_squares_vector_[j] != node_id_as_next_move)
                empty_squares_shuffle_vector.emplace_back(empty_squares_vector_[j]);

        if (!debug_mode_)
            printf("\rSimulation trial %6u of %6u", ((i + 1) * num_of_simulations_), (empty_squares_vector_.size() * num_of_simulations_));
        else
            printf("Simulation trial %6u of %6u, (%c)'s node_id_as_next_move %2d ", ((i + 1) * num_of_simulations_), (empty_squares_vector_.size() * num_of_simulations_), static_cast<char>(player), node_id_as_next_move);

        //run simulated trial runs, record win loss
        for (unsigned int simulation_number = 0; simulation_number < num_of_simulations_; simulation_number++)
        {
            //SHUFFLE AND FILL BOARD TIME START
            t0 = chrono::high_resolution_clock::now();

            //shuffle empty_squares_shuffle_vector vector
            shuffle(empty_squares_shuffle_vector.begin(), empty_squares_shuffle_vector.end(), my_random_engine_);

            //fill up board
            FillBoardRandomly(player, node_id_as_next_move, empty_squares_shuffle_vector);

            //SHUFFLE AND FILL BOARD TIME END
            t1 = chrono::high_resolution_clock::now();
            //WHO WON DFS ALGO TIME START

            bool playerWon = GameWonCheckDfsAlgo(player);

            //WHO WON DFS ALGO TIME END
            t2 = chrono::high_resolution_clock::now();

            if (playerWon)
                wins++;
            else
                losses++;

            duration_shuffle_and_fill_up_board += chrono::duration_cast<chrono::microseconds>(t1 - t0);
            duration_who_won_using_dfs_algo += chrono::duration_cast<chrono::microseconds>(t2 - t1);
        }

        //clear shuffle vector
        empty_squares_shuffle_vector.clear();

        double win_loss_ratio = 1.0 * wins / losses;
        if (debug_mode_)
            cout << " win_loss_ratio for square " << get_row_char_(node_id_as_next_move) << get_col_number_(node_id_as_next_move) << " is " << win_loss_ratio << endl;
        
        if (win_loss_ratio > best_win_loss_ratio)
        {
            best_win_loss_ratio = win_loss_ratio;
            best_win_loss_ratio_node_id = node_id_as_next_move;
        }
    }

    //print best found next move
    cout << "\n\n(" << player << ") picks " << get_row_char_(best_win_loss_ratio_node_id) << get_col_number_(best_win_loss_ratio_node_id) << endl;
    
    //TIME NOTING STOP
    auto stop = chrono::high_resolution_clock::now();
    auto duration_total = chrono::duration_cast<chrono::milliseconds>(stop - start);

    unsigned int time_total = static_cast<unsigned int>(duration_total.count());
    unsigned int time_shuffle_and_fill_up_board = static_cast<unsigned int>(duration_shuffle_and_fill_up_board.count() / 1000);
    unsigned int time_who_won_using_dfs_algo = static_cast<unsigned int>(duration_who_won_using_dfs_algo.count() / 1000);

    printf("Total Time taken               : %7u ms\n", time_total);
    printf("time_shuffle_and_fill_up_board : %7u ms  %3.2f%%\n", time_shuffle_and_fill_up_board, 1.0 * time_shuffle_and_fill_up_board / time_total * 100);
    printf("time_who_won_using_dfs_algo    : %7u ms  %3.2f%%\n", time_who_won_using_dfs_algo, 1.0 * time_who_won_using_dfs_algo / time_total * 100);
    printf("time_tot - shuffle - pathalgos : %7u ms  %3.2f%%\n", time_total - time_shuffle_and_fill_up_board - time_who_won_using_dfs_algo, 1.0 * (time_total - time_shuffle_and_fill_up_board - time_who_won_using_dfs_algo) / time_total * 100);

    return best_win_loss_ratio_node_id;
}

#ifndef PROCESS_HEX_BOARD_CLASS_H_
#define PROCESS_HEX_BOARD_CLASS_H_

#include <random>
#include <vector>
#include "My_Priority_Queue.h"
#include "Square.h"

class ProcessHexBoardClass
{
public:
    void ProcessHexBoardClassInitialize();

    ~ProcessHexBoardClass();

    //copy game play hex board to process board's hex board before running simulations or checking who won
    void CopyHexBoardToProcessHexBoardClass(Square** hex_board_);

    bool GameWonCheckDfsAlgo(Square player);

    //fills process hex board class's hex board randomly to each player turn by turn
    void FillBoardRandomly(Square player, const int& node_id_as_next_move, std::vector<int>& empty_squares_vector_filled_randomly);

    //static variables and functions
    static bool debug_mode_;
    static unsigned int num_of_simulations_;
    static const int get_board_size_();
    static void set_board_size_(int board_size) { board_size_ = board_size; };
    static const bool BoundsCheck(const int row_index, const int col_index);
    static const int get_row_index_(const int node_id);
    static const int get_col_index_(const int node_id);
    static const int get_node_id_(const int row_index, const int col_index);
    static const char get_row_char_(const int node_id);
    static const int get_col_number_(const int node_id);

    //Monte Carlo Simulator to find Best Next Move
    //returns node_id for Best Next Move
    int MonteCarloSimulationsToFindBestNextMove(const Square player, const std::vector<int>& empty_squares_vector_);

private:
    //static variable hex board size
    static int board_size_;
    
    //process hex board class's hex board - pointer to pointer of Square - '.', 'X' or 'O'
    Square** hex_board_ = nullptr;

    //hex board visited flag to note which nodes have been visited by dfs algorithm
    bool** hex_board_visited_ = nullptr;
    bool is_node_visited_(const int node_id);
    void set_node_as_visited_(const int node_id);

    //function to create neighbor nodes vector
    MyPriorityQueue GetNeighborNodes(const int node_id, const Square player, const bool unvisited_only);

    //adds neighbors to GetNeighborNodes vector
    void AddNeighborNodes(const int row_index, const int col_index, const Square& player, const bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes);

    //recursively calls itself until it finds end node
    bool DfsSearch(int node_id, Square& player);

    //random engine for shuffle algorithm to shuffle empty available hex board squares
    std::default_random_engine my_random_engine_;
};

#endif  //!PROCESS_HEX_BOARD_CLASS_H_
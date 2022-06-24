#ifndef HEX_BOARD_H_
#define HEX_BOARD_H_

#include <random>
#include <vector>
#include "My_Priority_Queue.h"
#include "PlayerType.h"
#include "Square.h"

class HexBoard
{
public:
    void HexBoardInitialize();

    ~HexBoard();
    std::string HexBoardOwnerClass;

    //hex board - pointer to pointer of Square - '.', 'X' or 'O'
    Square** hex_board_ = nullptr;
    //prints ownership count and returns empty squares
    unsigned int PrintOwnershipCountReturnEmptySquares(bool print);

    //all squares have an id, we maintain an empty square node ids vector of GamePlayClass's Hex Board. This will be used to randomly fill Simulation Hex Boards
    static std::vector<int> empty_squares_vector_;

    bool GameWonCheckDfsAlgo(Square player);

    void PrintHexBoard();

    void set_hex_board_ownership_(const int node_id, const Square player);

    //player details
    static PlayerType playerA_type_;        // 0 – human / 1 - computer
    static PlayerType playerB_type_;        // 0 – human / 1 – computer
    static std::string playerA_name_;
    static std::string playerB_name_;

    //static variables and functions
    static bool debug_mode_;
    static const int get_board_size_();
    static void set_board_size_(int board_size) { board_size_ = board_size; };
    static const bool BoundsCheck(const int row_index, const int col_index);
    static const int get_row_index_(const int node_id);
    static const int get_col_index_(const int node_id);
    static const int get_node_id_(const int row_index, const int col_index);
    static const char get_row_char_(const int node_id);
    static const int get_col_number_(const int node_id);
    static unsigned int num_of_simulations_;

private:
    //static variable hex board size
    static int board_size_;

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
};

#endif  //!HEX_BOARD_H_
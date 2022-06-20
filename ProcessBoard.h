#ifndef PROCESS_BOARD_H_
#define PROCESS_BOARD_H_

#include <vector>
#include "GameClass.h"
#include "My_Priority_Queue.h"

class ProcessBoard
{
public:
    Square** hex_board = nullptr;

    int board_size = 0;

    ProcessBoard(Square** hex_board_data, int board_size_data, int empty_squares_vector_size_for_simulations);

    ~ProcessBoard();

    bool game_won_check_aStar(Square player);    // (using Dijkstra’s for now, A star later), return -1 for none, 0 for PlayerA, 1 for PlayerB

    bool game_won_check_dfs(Square player);

    void fill_board_randomly(Square player, int node_id_as_next_move, std::vector<int>& empty_squares_vector_filled_randomly);    // return randomly filled up board

    //std::vector<int> empty_squares_to_fill_randomly;

    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    MyPriorityQueue closed_set;

    //MyPriorityQueue current_neighbor_nodes;

    void check_and_add_nodes_to_current_neighbor_nodes(int& row_index, int& col_index, Square& player, bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes);

    MyPriorityQueue get_connected_nodes(int node_id, Square player, bool unvisited_only);

    bool* node_in_closed_set = nullptr;

    bool** hex_board_visited = nullptr;

    bool dfs_search(int node_id, Square& player);


};

#endif  //!PROCESS_BOARD_H_#pragma once

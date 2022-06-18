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

    ProcessBoard(Square** hex_board_data, int board_size_data);

    ~ProcessBoard();

    void get_connected_nodes(int node_id, Square player);

    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    MyPriorityQueue closed_set;

    MyPriorityQueue current_neighbor_nodes;

    bool game_won_check_aStar(Square player);    // (using Dijkstra’s for now, A star later), return -1 for none, 0 for PlayerA, 1 for PlayerB

    bool* node_in_closed_set = nullptr;

    void fill_board_randomly(Square player, int node_id_as_next_move, std::vector<int> &empty_squares_vector);    // return randomly filled up board

};

#endif  //!PROCESS_BOARD_H_#pragma once

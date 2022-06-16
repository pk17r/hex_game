#ifndef PROCESS_BOARD_H_
#define PROCESS_BOARD_H_

#include <list>
#include <vector>
#include "Node.h"
#include "GameClass.h"

class ProcessBoard
{
public:
    Square** hex_board = nullptr;

    int board_size = 0;

    ProcessBoard(Square** hex_board_data, int board_size_data);

    std::list<Node> get_connected_nodes(int node_id, Square player);

    bool game_won_check(Square player);    // (using Dijkstra’s for now, A star later), return -1 for none, 0 for PlayerA, 1 for PlayerB

};

#endif  //!PROCESS_BOARD_H_#pragma once

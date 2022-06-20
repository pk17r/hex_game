#ifndef PROCESS_BOARD_H_
#define PROCESS_BOARD_H_

#include <vector>
#include "My_Priority_Queue.h"
#include "Square.h"

class ProcessBoard
{
public:
    ProcessBoard();

    ~ProcessBoard();

    void CopyHexBoard(Square** hex_board_data);

    bool GameWonCheckDfs(Square player);

    void FillBoardRandomly(Square player, int node_id_as_next_move, std::vector<int>& empty_squares_vector_filled_randomly);    // return randomly filled up board

private:
    Square** hex_board_ = nullptr;

    bool** hex_board_visited_ = nullptr;     //hex board to note which nodes have been visited by dfs algorithm

    int board_size_ = 0;

    void AddNeighborNodes(int& row_index, int& col_index, Square& player, bool& unvisited_only, MyPriorityQueue& current_neighbor_nodes);

    MyPriorityQueue GetNeighborNodes(int node_id, Square player, bool unvisited_only);

    bool DfsSearch(int node_id, Square& player);

};

#endif  //!PROCESS_BOARD_H_
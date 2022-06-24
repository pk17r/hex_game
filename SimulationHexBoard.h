#ifndef SIMULATED_HEX_BOARD_H_
#define SIMULATED_HEX_BOARD_H_

#include <random>
#include <vector>
#include "BestWinLossRatio.h"
#include "HexBoard.h"
#include "My_Priority_Queue.h"
#include "Square.h"

class SimulationHexBoard : public HexBoard
{
public:
    SimulationHexBoard();
    ~SimulationHexBoard();

    //fills process hex board class's hex board randomly to each player turn by turn
    void FillBoardRandomly(Square player, const int& node_id_as_next_move, std::vector<int>& empty_squares_vector_filled_randomly);

    //Monte Carlo Simulator to find Best Next Move
    //returns node_id for Best Next Move
    BestWinLossRatio MonteCarloSimulationsToFindBestNextMove(Square player, unsigned int from_index, unsigned int to_index);

private:
    //random engine for shuffle algorithm to shuffle empty available hex board squares
    std::default_random_engine my_random_engine_;

    std::vector<int> empty_squares_shuffle_vector_;
};

#endif  //!SIMULATED_HEX_BOARD_H_
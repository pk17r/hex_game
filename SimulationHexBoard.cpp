#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include "Node.h"
#include "SimulationHexBoard.h"

using namespace std;

SimulationHexBoard::SimulationHexBoard()
{
    //initialize hex board
    HexBoardInitialize();
    HexBoardOwnerClass = "SimulationHexBoard()";

    empty_squares_shuffle_vector_.reserve(empty_squares_vector_.size() - 1);
    
    //setting seed for random number generator engine
    unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
    my_random_engine_ = default_random_engine(seed);

}

SimulationHexBoard::~SimulationHexBoard()
{
    empty_squares_shuffle_vector_.clear();
    cout << "~SimulationHexBoard()" << endl;
}

void SimulationHexBoard::FillBoardRandomly(Square player, const int& node_id_as_next_move, std::vector<int>& empty_squares_vector_filled_randomly)
{
    int turns_by_player_A = 0, turns_by_player_B = 0;

    //make current move on hex board
    set_hex_board_ownership_(node_id_as_next_move, player);

    if (player == Square::PlayerA)
        turns_by_player_A++;
    else
        turns_by_player_B++;

    for (unsigned int i = 0; i < empty_squares_vector_filled_randomly.size(); i++)
    {
        assert(empty_squares_vector_filled_randomly[i] != node_id_as_next_move);

        player = (player == Square::PlayerA ? Square::PlayerB : Square::PlayerA);

        set_hex_board_ownership_(empty_squares_vector_filled_randomly[i], player);

        if (player == Square::PlayerA)
            turns_by_player_A++;
        else
            turns_by_player_B++;
    }

    assert(abs(turns_by_player_A - turns_by_player_B) <= 1);
}

BestWinLossRatio SimulationHexBoard::MonteCarloSimulationsToFindBestNextMove(Square player, unsigned int from_index, unsigned int to_index)
{
    /*
    -For each entry of empty squares run a simulation 1000 times

        - Fill all squares randomly

        - Check who won the game

        - Note win or loss for this simulation

        - Assign the entry with win / loss ratio

        - Return the entry with best win / loss ratio
    */

    //Simulation loop time clocks
    static std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1, t2;
    //time duration counters
    std::chrono::nanoseconds duration_shuffle_and_fill_up_board = static_cast<std::chrono::nanoseconds>(0),
        duration_who_won_using_dfs_algo = static_cast<std::chrono::nanoseconds>(0);

    //variable to track best win loss ratio move
    BestWinLossRatio best_win_loss_ratio_data;

    assert(empty_squares_shuffle_vector_.size() == 0);

    for (unsigned int i = from_index; i < std::min(to_index, static_cast<unsigned int>(empty_squares_vector_.size())); i++)
    {
        int node_id_as_next_move = empty_squares_vector_.at(i);
        unsigned int wins = 0, losses = 0;

        for (unsigned int j = 0; j < empty_squares_vector_.size(); j++)
            if (empty_squares_vector_.at(j) != node_id_as_next_move)
                empty_squares_shuffle_vector_.emplace_back(empty_squares_vector_.at(j));

        if (!debug_mode_)
            printf(".");
        else
            printf("Simulation trial %6u of %6u, (%c)'s node_id_as_next_move %2d ", ((i + 1) * num_of_simulations_), (empty_squares_vector_.size() * num_of_simulations_), static_cast<char>(player), node_id_as_next_move);

        //run simulated trial runs, record win loss
        for (unsigned int simulation_number = 0; simulation_number < num_of_simulations_; simulation_number++)
        {
            //SHUFFLE AND FILL BOARD TIME START
            t0 = chrono::high_resolution_clock::now();

            //shuffle empty_squares_shuffle_vector vector
            shuffle(empty_squares_shuffle_vector_.begin(), empty_squares_shuffle_vector_.end(), my_random_engine_);

            //fill up board
            FillBoardRandomly(player, node_id_as_next_move, empty_squares_shuffle_vector_);

            //SHUFFLE AND FILL BOARD TIME END
            t1 = chrono::high_resolution_clock::now();
            //WHO WON DFS ALGO TIME START

            //assert(PrintOwnershipCountReturnEmptySquares(false) == 0);

            bool playerWon = GameWonCheckDfsAlgo(player);

            //WHO WON DFS ALGO TIME END
            t2 = chrono::high_resolution_clock::now();

            if (playerWon)
                wins++;
            else
                losses++;

            duration_who_won_using_dfs_algo += chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
            duration_shuffle_and_fill_up_board += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);
        }

        //clear shuffle vector
        empty_squares_shuffle_vector_.clear();

        double win_loss_ratio = 1.0 * wins / losses;
        if (debug_mode_)
            cout << " win_loss_ratio for square " << get_row_char_(node_id_as_next_move) << get_col_number_(node_id_as_next_move) << " is " << win_loss_ratio << endl;

        if (win_loss_ratio > best_win_loss_ratio_data.best_win_loss_ratio)
        {
            best_win_loss_ratio_data.best_win_loss_ratio = win_loss_ratio;
            best_win_loss_ratio_data.best_win_loss_ratio_node_id = node_id_as_next_move;
        }
    }

    best_win_loss_ratio_data.time_shuffle_and_fill_up_board += static_cast<unsigned int>(duration_shuffle_and_fill_up_board.count() / 1000000);
    best_win_loss_ratio_data.time_who_won_using_dfs_algo += static_cast<unsigned int>(duration_who_won_using_dfs_algo.count() / 1000000);

    return best_win_loss_ratio_data;
}

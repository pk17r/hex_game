#ifndef GAME_PLAY_CLASS_H_
#define GAME_PLAY_CLASS_H_

#include <memory>
#include <string>
#include <vector>
#include "BestWinLossRatio.h"
#include "HexBoard.h"
#include "SimulationHexBoard.h"

class GamePlayClass : public HexBoard
{
public:
    GamePlayClass();    // constructor to initialize hex game

    ~GamePlayClass();

    void RunGame();    // run game here

    void CreateSimulationHexBoards();

    static void RunSim(int sim_index, Square player, unsigned int from_index, unsigned int to_index);

private:

    //to test out Print Hex Board function
    static bool test_print_hex_board_;
    
    //Get user next move input
    int GetUserNextMove(Square player);                 //returns node_id

    //Run simulations in ProcessHexBoardClass to find out next best move for computer
    BestWinLossRatio FindBestNextMove(Square player, bool give_hint_to_user);                //returns node_id

    //get game parameters like player types and hex board size input from user
    void GetGameParametersInput();

    //all simulated hex boards for multi-threaded computational processing
    static std::vector<std::shared_ptr<SimulationHexBoard>> simulation_hex_boards_ptr_vector_;

    //variables to track best win loss ratio move
    static std::vector<BestWinLossRatio> best_win_loss_ratio_vector;
};

#endif  //!GAME_PLAY_CLASS_H_
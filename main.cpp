// Hex Game
// 
// Read READ_ME file for details about this game.
// 
// To change board size to 5, update board_size_ = 5
// To play computer vs computer, make both players computer
// To play human vs computer or computer vs human, select accordingly on cmd
// Play to win!
// 
// GamePlayClass.h - where hex game is played
// ProcessHexBoardClass.h - where game won check or simulations to find next best move happen
// 
// Author: Prashant Kumar
// 
// Date June 16th 2022
//

#include <memory>
#include <vector>
#include "BestWinLossRatio.h"
#include "HexBoard.h"
#include "GamePlayClass.h"
#include "PlayerType.h"
#include "SimulationHexBoard.h"

//hex game program parameters
int HexBoard::board_size_ = 11;
bool HexBoard::debug_mode_ = false;            //when true, simulation win-loss-ratio will be printed, it can also be enabled at runtime by inputting board size with a suffix 'd'
unsigned int HexBoard::num_of_simulations_ = 10000;
bool GamePlayClass::test_print_hex_board_ = false;          //make this true to test Print Hex Board function
PlayerType HexBoard::playerA_type_ = PlayerType::Human;       // 0 – human / 1 - computer
PlayerType HexBoard::playerB_type_ = PlayerType::Computer;    // 0 – human / 1 – computer
std::string HexBoard::playerA_name_ = "Test Player";
std::string HexBoard::playerB_name_ = "Computer";
std::vector<int> HexBoard::empty_squares_vector_;
std::vector<std::shared_ptr<SimulationHexBoard>> GamePlayClass::simulation_hex_boards_ptr_vector_;
std::vector<BestWinLossRatio> GamePlayClass::best_win_loss_ratio_vector;

int main()
{
    //initialize hex game
    GamePlayClass hex_game_object;

    //play hex game
    hex_game_object.RunGame();

    return 0;
}

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

#include "GamePlayClass.h"
#include "ProcessHexBoardClass.h"

//hex game program parameters
int ProcessHexBoardClass::board_size_ = 11;
bool ProcessHexBoardClass::debug_mode_ = false;            //when true, simulation win-loss-ratio will be printed, it can also be enabled at runtime by inputting board size with a suffix 'd'
unsigned int ProcessHexBoardClass::num_of_simulations_ = 1000;
bool GamePlayClass::test_print_hex_board_ = false;          //make this true to test Print Hex Board function

int main()
{
    //initialize hex game
    GamePlayClass hex_game_object;

    //play hex game
    hex_game_object.RunGame();

    return 0;
}

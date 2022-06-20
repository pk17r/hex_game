// Hex Game
// 
// Read READ_ME file for details about this game.
// 
// To change board size to 5, update board_size_ = 5
// To play computer vs computer, make both players computer
// To play human vs computer or computer vs human, select accordingly on cmd
// Play to win!
// 
// Author: Prashant Kumar
// 
// Date June 16th 2022
//

#include "PlayHexGameClass.h"
#include "ProcessHexBoardClass.h"

//main hex game program parameters
bool PlayHexGameClass::play_game_ = true;              //make this true to only test print hex board function
int ProcessHexBoardClass::board_size_ = 11;                 // 5 for testing, 11 for production
unsigned int ProcessHexBoardClass::num_of_simulations_ = 1000;
bool PlayHexGameClass::debug_mode_ = false;            //when true, simulation win-loss-ratio will be printed, can be enabled at runtime by inputting board size with a suffix 'd'

int main()
{
    //initialize hex game
    PlayHexGameClass hex_game_object;

    //play hex game or test print hex board
    if (PlayHexGameClass::play_game_)
        hex_game_object.RunGame();
    else
        hex_game_object.PrintHexBoard();

    return 0;
}

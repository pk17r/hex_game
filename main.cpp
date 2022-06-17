// Hex Game
// 
// Read READ_ME file for details about this game.
// 
// To change board size to 5, update board_size = 5
// To play computer vs computer, make both players computer
// To play human vs computer or computer vs human, select accordingly on cmd
// Play to win!
// 
// Author: Prashant Kumar
// 
// Date June 16th 2022
//

#include <iostream>
#include "GameClass.h"

int main()
{
    int board_size = 11;
    bool test_printout_run = false;

    //initialize hex game
    GameClass hex_game_object(board_size, test_printout_run);

    if (!test_printout_run)
    {
        //run hex game
        hex_game_object.RunGame();
    }
    else
    {
        hex_game_object.print_hex_board();
    }

    return 0;
}


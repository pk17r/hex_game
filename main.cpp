// Hex Game
// 
// Read READ_ME file for details about this game.
// 
// Author: Prashant Kumar
// 
// Date June 16th 2022
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GameClass.h"

int main()
{
    //disable automatic cout flush to terminal, this helps in printing hex board quickly to terminal.
    std::ios::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
    
    int board_size = 5;

    //initialize hex game
    GameClass hex_game_object(board_size);

    //run hex game
    hex_game_object.RunGame();

    return 0;
}


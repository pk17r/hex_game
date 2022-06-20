#ifndef GAME_PLAY_CLASS_H_
#define GAME_PLAY_CLASS_H_

#include <string>
#include <vector>
#include "PlayerType.h"
#include "ProcessHexBoardClass.h"
#include "Square.h"

class GamePlayClass : ProcessHexBoardClass
{
public:
    GamePlayClass();    // constructor to initialize hex game

    ~GamePlayClass();

    void RunGame();    // run game here

    void PrintHexBoard();

private:
    //game play hex board - pointer to pointer of Square - '.', 'X' or 'O'
    Square** hex_board_ = nullptr;

    //to test out Print Hex Board function
    static bool test_print_hex_board_;

    //all squares have an id, we maintain an empty square ids vector to shuffle random fill from
    std::vector<int> empty_squares_vector_;

    //Get user next move input
    int GetUserNextMove(Square player);                 //returns node_id

    //Run simulations in ProcessHexBoardClass to find out next best move for computer
    int FindBestNextMove(Square player);                //returns node_id

    //get game parameters like player types and hex board size input from user
    void GetGameParametersInput();

    //player details
    PlayerType playerA_type_ = PlayerType::Human;       // 0 – human / 1 - computer
    PlayerType playerB_type_ = PlayerType::Computer;    // 0 – human / 1 – computer
    std::string playerA_name_ = "Test Player";
    std::string playerB_name_ = "Computer";
};

#endif  //!GAME_PLAY_CLASS_H_
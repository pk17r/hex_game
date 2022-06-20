#ifndef GAME_CLASS_H_
#define GAME_CLASS_H_

#include <list>
#include <random>
#include <string>
#include <vector>
#include "PlayerType.h"
#include "ProcessBoard.h"
#include "Square.h"

class GameClass
{
public:
    PlayerType playerA_type_ = PlayerType::Human;    // 0 � human / 1 - computer

    PlayerType playerB_type_ = PlayerType::Computer;    // 0 � human / 1 � computer

    std::string playerA_name_;

    std::string playerB_name_;

    void PrintHexBoard();
    
    GameClass();    // constructor to initialize game and take inputs

    ~GameClass();

    void RunGame();    // run game here

    //static variables
    static bool play_game_;

    static int board_size_;

    static bool debug_mode_;

    static unsigned int num_of_simulations_;

private:
    Square** hex_board_ = nullptr;    // pointer to pointer of Square

    std::vector<int> empty_squares_vector_;    // all squares have an id, we maintain an empty ids vector to pick from

    std::default_random_engine my_random_engine_;

    int GetUserNextMove(Square player);    // return node_id

    int FindBestNextMove(Square player, ProcessBoard& processBoard);    // return node_id

};

#endif  //!GAME_CLASS_H_
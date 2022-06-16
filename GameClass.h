#ifndef GAME_CLASS_H_
#define GAME_CLASS_H_

#include <string>
#include <vector>
#include "Square.h"
#include "PlayerType.h"

class GameClass
{
public:
    PlayerType playerA_type = PlayerType::Human;    // 0 – human / 1 - computer

    PlayerType playerB_type = PlayerType::Computer;    // 0 – human / 1 – computer

    std::string playerA_name;

    std::string playerB_name;

    int board_size = 5;    // 5 for testing, 11 for production

    Square** hex_board = nullptr;    // pointer to pointer of Square

    std::vector<int> empty_squares_vector;    // all squares have an id, we maintain an empty ids list to pick from

    GameClass(int board_size);    // constructor to initialize game and take inputs

    void RunGame();    // run game here

    Square** fill_board_randomly(Square turn_of_player);    // return randomly filled up board

    int take_user_input(Square player);    // return node_id

    int best_next_move(Square player);    // return node_id

    void print_hex_board();

};

#endif  //!GAME_CLASS_H_
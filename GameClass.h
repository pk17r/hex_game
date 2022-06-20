#ifndef GAME_CLASS_H_
#define GAME_CLASS_H_

#include <list>
#include <random>
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

    void print_hex_board();
    
    GameClass(int board_size, bool test_print_hex_board);    // constructor to initialize game and take inputs

    ~GameClass();

    void RunGame();    // run game here

    bool debug_mode_ = false;
    
private:
    int member_value = 1;
    
    Square** hex_board = nullptr;    // pointer to pointer of Square

    std::vector<int> empty_squares_vector;    // all squares have an id, we maintain an empty ids vector to pick from

    const int num_of_simulations = 1000;
    
    std::default_random_engine myRandomEngine;

    int take_user_input(Square player);    // return node_id

    int best_next_move(Square player);    // return node_id


};

#endif  //!GAME_CLASS_H_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameClass.h"
#include "ProcessBoard.h"

using namespace std;

GameClass::GameClass(int board_size)
{
    cout << '\n' << '\n';
    cout << "\t\t\t  Hex Game\n\n";
    cout << "Player v/s Computer\n\n";
    cout << "X goes first and takes vertical direction, O goes second and takes horizontal direction.\n\n";
    
    string user_choice;
    cout << "Enter PlayerA Type, 0 for human or 1 computer:";
    getline(cin, user_choice);
    if (user_choice == "0")
    {
        playerA_type = PlayerType::Human;
        cout << "\nPlayerA Name:";
        getline(cin, playerA_name);
    }
    else
    {
        playerA_type = PlayerType::Computer;
        playerA_name = "Computer";
    }
    cout << "\nPlayerA is " << playerA_name << '\n';
    
    cout << "Enter PlayerB Type, 0 for human or 1 computer:";
    getline(cin, user_choice);
    if (user_choice == "0")
    {
        playerB_type = PlayerType::Human;
        cout << "\nPlayerB Name:";
        getline(cin, playerB_name);
    }
    else
    {
        playerB_type = PlayerType::Computer;
        playerB_name = "Computer";
    }
    cout << "\nPlayerB is " << playerB_name << '\n';

    //playerA will make graph in vertical direction
    //playerB will make graph in horizontal direction

    this->board_size = board_size;

    //we will add two imaginary nodes - graph start and end nodes, to players graphs
    //we will use dijkstra's algorithm to find shortest path between these imaginary nodes
    //we will use the case of finding a solvable path between these two imaginary nodes as reaching the game's end
    //we will connect a player's side edge nodes to these imaginary nodes at start of game

    //initialize hex board
    hex_board = new Square * [board_size];
    for (int i = 0; i < board_size; i++)
    {
        hex_board[i] = new Square[board_size];
    }
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            hex_board[i][j] = Square::Empty;
        }
    }
}

void GameClass::RunGame()
{
    print_hex_board();

    int moves = 0;

    bool player_won = false;

    //first turn is of PlayerA
    Square current_player = Square::PlayerA;
    PlayerType current_player_type = playerA_type;

    while (!player_won)
    {
        moves++;
        //take player input
        int chosen_node_id;
        if (current_player_type == PlayerType::Human)
            chosen_node_id = take_user_input(current_player);
        else
            chosen_node_id = best_next_move(current_player);
        int row_index = chosen_node_id / board_size;
        int col_index = chosen_node_id % board_size;
        hex_board[row_index][col_index] = current_player;
        
        //check game won by current player
        ProcessBoard processBoard(hex_board, board_size);
        player_won = processBoard.game_won_check(current_player);

        if (!player_won)
        {//change player
            if (current_player == Square::PlayerA)
            {
                current_player = Square::PlayerB;
                current_player_type = playerB_type;
            }
            else
            {
                current_player = Square::PlayerA;
                current_player_type = playerA_type;
            }
        }

        cout << "Hex Board after " << moves << " moves:\n";

        print_hex_board();
    }
    
    cout << '\n' << (current_player == Square::PlayerA ? playerA_name : playerB_name) << " won!!!" << '\n' << endl;
    cout << "Game won in " << moves << " moves!" << endl;
}

// return randomly filled up board
Square** GameClass::fill_board_randomly(Square turn_of_player)
{
    //write this code
    return nullptr;
}

// return node_id
int GameClass::take_user_input(Square player)
{
    int row_index = -1, col_index = -1;
    while (true)
    {
        cout << (player == Square::PlayerA ? playerA_name : playerB_name) << " enter next move:";

        char letter = '?';
        int number = -1;
        while (number == -1)
        {
            string input;
            getline(cin, input);

            int letter_value = tolower(input.at(0));
            if (letter_value >= 97 && letter_value <= 122)
            {
                letter = letter_value;
                number = stoi(input.substr(1, input.size() - 1));
            }
            else if (letter_value >= 48 && letter_value <= 57)
            {
                letter = tolower(input.at(input.size() - 1));
                number = stoi(input.substr(0, input.size() - 1));
            }
            else
            {
                cout << "Invalid input!\n";
            }
        }
        row_index = letter - 97;
        col_index = number - 1;

        if (row_index >= 0 && col_index >= 0 && row_index < board_size && col_index < board_size)
        {
            if (hex_board[row_index][col_index] == Square::Empty)
                break;
            else
                cout << "Square already taken." << endl;
        }
        else
            cout << "Out of bounds input." << endl;
    }

    return row_index * board_size + col_index;
}

// return node_id
int GameClass::best_next_move(Square player)
{
    //write this code
    return 0;
}

void GameClass::print_hex_board()
{
    cout << '\n' << '\n';
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << " : " << playerA_name << "  |  top-to-bottom" << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << " : " << playerB_name << "  |  left-to-right" << '\n';
    cout << '\n';

    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= board_size; i++)
        printf("%2d  ", i);
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < board_size; i++)
    {
        //row initial blank spaces
        cout << '\t';
        for (int print_blank = 0; print_blank < i; print_blank++)
            cout << " ";

        //row label left
        //cout << static_cast<char>(Square::PlayerB) << letter << "      ";
        cout << letter << "  \\  ";

        //board
        for (int j = 0; j < board_size; j++)
        {
            cout << static_cast<char>(hex_board[i][j]);
            if (j < board_size - 1)
                cout << "   ";
        }

        //row label right
        cout << "  \\  " << letter++ << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < board_size - 3; print_blank++)
        cout << " ";

    //footer row
    for (int i = 1; i <= board_size; i++)
        printf("%2d  ", i);

    cout << '\n' << '\n';
    cout << endl;
}
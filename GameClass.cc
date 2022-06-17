#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameClass.h"
#include "ProcessBoard.h"

using namespace std;

GameClass::GameClass(int board_size, bool test_printout_run)
{
    cout << '\n' << '\n';
    cout << "\t\t\t  Hex Game\n\n";
    cout << "Player v/s Computer\n\n";
    cout << "X goes first and takes vertical direction, O goes second and takes horizontal direction.\n\n";
    
    if (!test_printout_run)
    {
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
        cout << "PlayerA is " << playerA_name << '\n';

        cout << "\nEnter PlayerB Type, 0 for human or 1 computer:";
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
        cout << "PlayerB is " << playerB_name << '\n';
    }
    else
    {
        playerA_type = PlayerType::Human;
        playerA_name = "Test Player";
        playerB_type = PlayerType::Computer;
        playerB_name = "Computer";
    }

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

    //update empty_squares_list with all nodes
    for (int i = 0; i < board_size * board_size; i++)
    {
        empty_squares_list.push_back(i);
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
        empty_squares_list.remove(chosen_node_id);

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

        cout << '\n' << "Hex Board after " << moves << " moves:" << '\n';

        print_hex_board();
    }
    
    cout << '\n' << (current_player == Square::PlayerA ? "Player A, " : "Player B, ") << (current_player == Square::PlayerA ? playerA_name : playerB_name) << " Won!!!" << '\n' << endl;
    cout << "Game won in " << moves << " moves!" << endl;
}

// return node_id
int GameClass::take_user_input(Square player)
{
    int row_index = -1, col_index = -1;
    while (true)
    {
        cout << (player == Square::PlayerA ? playerA_name : playerB_name) << ", win by making a connected path from " << (player == Square::PlayerA ? "Top-to-Bottom" : "Left-to-Right") << '\n';
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
    /*
    -For each entry of list of empty squares run a simulation 1000 times

        - Fill all squares randomly

        - Check who won the game

        - Note win or loss for this simulation

        - Assign the entry with win / loss ratio

        - Return the entry with best win / loss ratio
    */
    
    double best_win_loss_ratio = 0;
    int best_win_loss_ratio_node_id = -1;

    cout << "Running " << num_of_simulations << " x " << empty_squares_list.size() << " simulated trials" << flush;

    for (auto empty_squares_list_iterator = empty_squares_list.cbegin(); empty_squares_list_iterator != empty_squares_list.cend(); empty_squares_list_iterator++)
    {
        int node_id_as_next_move = *empty_squares_list_iterator;
        int wins = 0, losses = 0;

        ProcessBoard processBoard(hex_board, board_size);

        for (int simulation_number = 0; simulation_number < num_of_simulations; simulation_number++)
        {
            processBoard.fill_board_randomly(player, node_id_as_next_move, empty_squares_list);
            bool playerWon = processBoard.game_won_check(player);
            if (playerWon)
                wins++;
            else
                losses++;
        }
        
        double win_loss_ratio = 1.0 * wins / losses;
        //char row_char = 'a' + node_id_as_next_move / board_size;
        //int col_num = node_id_as_next_move % board_size + 1;
        //cout << "win_loss_ratio for square " << row_char << col_num << " is " << win_loss_ratio << endl;
        cout << "." << flush;

        if (win_loss_ratio > best_win_loss_ratio)
        {
            best_win_loss_ratio = win_loss_ratio;
            best_win_loss_ratio_node_id = node_id_as_next_move;
        }
    }

    char row_char = 'a' + best_win_loss_ratio_node_id / board_size;
    int col_num = best_win_loss_ratio_node_id % board_size + 1;
    cout << '\n' << '\n' << (player == Square::PlayerA ? "Player A," : "Player B,") << "Computer picks " << row_char << col_num << flush;
    cout << '\n';

    return best_win_loss_ratio_node_id;
}

void GameClass::print_hex_board()
{
    cout << '\n' << '\n';
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << "  |  top-to-bottom  | " << playerA_name  << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << "  |  left-to-right  | " << playerB_name << '\n';
    cout << '\n' << '\n';

    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= board_size; i++)
        printf("%3d  ", i);
    cout << '\n';

    cout << '\t' << "     ";
    for (int i = 1; i <= board_size; i++)
        printf(" --  ");
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < 2 * board_size; i++)
    {
        if (i % 2 == 0)
        {
            //row initial blank spaces
            cout << '\t';
            for (int print_blank = 0; print_blank < i + i / 2; print_blank++)
                cout << " ";

            //row label left
            cout << letter << "  \\   ";

            //board
            for (int j = 0; j < board_size; j++)
            {
                cout << static_cast<char>(hex_board[i / 2][j]);
                if (j < board_size - 1)
                    cout << "    ";
            }

            //row label right
            cout << "   \\  " << letter++;
        }
        
        cout << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < 2 * board_size - 2 + board_size; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size; i++)
        printf("--   ");

    //footer row
    cout << '\n' << '\t' << '\t' << " ";
    for (int print_blank = 0; print_blank < 2 * board_size - 3 + board_size; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size; i++)
        printf("%3d  ", i);

    cout << '\n' << '\n' << endl;
}
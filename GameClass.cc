#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameClass.h"
#include "ProcessBoard.h"

using namespace std;

GameClass::GameClass(int board_size, bool test_printout_run)
{
    cout << "\n\n\n\t\t\t\tHex Game\n\n\n";
    cout << "                       1    2    3    4    5\n";
    cout << "                       --   --   --   --   --\n";
    cout << "                  a  \\   .    .    .    X    O   \\  a\n";
    cout << "\n";         
    cout << "                    b  \\   .    .    O    X    .   \\  b\n";
    cout << "\n";         
    cout << "                      c  \\   .    .    X    O    .   \\  c\n";
    cout << "\n";         
    cout << "                        d  \\   .    X    .    .    .   \\  d\n";
    cout << "\n";         
    cout << "                          e  \\   O    X    .    .    .   \\  e\n";
    cout << "                                 --   --   --   --   --\n";
    cout << "                                  1    2    3    4    5\n";
    cout << "\n\n";
    cout << "Program to Play Human vs Human or vs Computer or Computer vs Computer\n\n";
    cout << "X goes first and takes vertical direction, O goes second and takes horizontal direction." << '\n' << endl;
    cout << "To play computer vs computer, make both players computer" << endl;
    cout << "To play human vs computer or computer vs human, select accordingly on cmd" << endl;
    cout << "\nPlay to win!" << '\n' << endl;

    if (!test_printout_run)
    {
        string user_choice;
        cout << "Enter board size (default 11): ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            board_size = stoi(user_choice);
        }
        cout << "board size = " << board_size << '\n' << endl;

        cout << "Enter Player A (" << static_cast<char>(Square::PlayerA) << ") name if human or press enter to make it computer: ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            playerA_type = PlayerType::Human;
            playerA_name = user_choice;
        }
        else
        {
            playerA_type = PlayerType::Computer;
            playerA_name = "Computer";
        }
        cout << "Player A (" << static_cast<char>(Square::PlayerA) << ") is " << playerA_name << '\n';

        cout << "\nEnter Player B (" << static_cast<char>(Square::PlayerB) << ") name if human or press enter to make it computer: ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            playerB_type = PlayerType::Human;
            playerB_name = user_choice;
        }
        else
        {
            playerB_type = PlayerType::Computer;
            playerB_name = "Computer";
        }
        cout << "Player B (" << static_cast<char>(Square::PlayerB) << ") is " << playerB_name << '\n';
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
    empty_squares_vector = vector<int>(board_size * board_size, 0);
    for (int i = 0; i < board_size * board_size; i++)
    {
        empty_squares_vector[i] = i;
    }
}

GameClass::~GameClass()
{
    for (int i = 0; i < board_size; i++)
    {
        delete hex_board[i];
    }
    delete hex_board;
}

void GameClass::RunGame()
{
    print_hex_board();

    int moves = 0;

    bool player_won = false;

    //first turn is of PlayerA
    Square current_player = Square::PlayerA;
    PlayerType current_player_type = playerA_type;
    int chosen_node_id = -1;

    while (!player_won)
    {
        moves++;
        
        if (chosen_node_id != -1)
        {
            char row_char = 'a' + chosen_node_id / board_size;
            int col_num = chosen_node_id % board_size + 1;
            if(current_player == Square::PlayerA)
                cout << playerB_name << " (" << static_cast<char>(Square::PlayerB) << ") entered last move as : " << row_char << col_num << endl;
            else
                cout << playerA_name << " (" << static_cast<char>(Square::PlayerA) << ") entered last move as: " << row_char << col_num << endl;
        }

        //take player input
        if (current_player_type == PlayerType::Human)
            chosen_node_id = take_user_input(current_player);
        else
            chosen_node_id = best_next_move(current_player);
        int row_index = chosen_node_id / board_size;
        int col_index = chosen_node_id % board_size;
        hex_board[row_index][col_index] = current_player;
        //empty_squares_vector.remove(empty_squares_vector.begin(), empty_squares_vector.end(), chosen_node_id);
        for (auto iterator = empty_squares_vector.begin(); iterator != empty_squares_vector.end(); iterator++)
        {
            if (*iterator == chosen_node_id)
            {
                empty_squares_vector.erase(iterator);
                break;
            }
        }

        //check game won by current player
        ProcessBoard processBoard(hex_board, board_size);
        player_won = processBoard.game_won_check_aStar(current_player);

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
    
    cout << '\n';
    if (current_player == Square::PlayerA)
        cout << playerA_name << " (" << static_cast<char>(Square::PlayerA) << ") Won!!!" << '\n' << endl;
    else
        cout << playerB_name << " (" << static_cast<char>(Square::PlayerB) << ") Won!!!" << '\n' << endl;
    cout << "Game won in " << moves << " moves!" << endl;
}

// return node_id
int GameClass::take_user_input(Square player)
{
    int row_index = -1, col_index = -1;
    if (player == Square::PlayerA)
        cout << playerA_name << " (" << static_cast<char>(Square::PlayerA) << ") win by making a connected path from Top-to-Bottom" << '\n';
    else
        cout << playerB_name << " (" << static_cast<char>(Square::PlayerB) << ") win by making a connected path from Left-to-Right" << '\n';
    
    while (true)
    {
        if (player == Square::PlayerA)
            cout << playerA_name << " (" << static_cast<char>(Square::PlayerA) << ") enter next move (e.g. x1): ";
        else
            cout << playerB_name << " (" << static_cast<char>(Square::PlayerB) << ") enter next move (e.g. x1): ";
    
        string input;
        getline(cin, input);

        bool invalid_input = false;
        char letter_input = '?';
        int number_input = -1;

        //input has to be as 'a1' or 'a10'
        if (input.size() < 2 || input.size() > 3)
            invalid_input = true;

        if (!invalid_input)
        {
            //a is 97, z is 122
            //0 is 48, 9 is 57
            //tolower returns 97 for a and A
            if (tolower(input.at(0)) < 97 || tolower(input.at(0)) > 122)
                invalid_input = true;
            if (tolower(input.at(1)) < 48 || tolower(input.at(1)) > 57)
                invalid_input = true;
            if (input.size() == 3)
                if (tolower(input.at(2)) < 48 || tolower(input.at(2)) > 57)
                    invalid_input = true;

            if (!invalid_input)
            {
                int letter_value = tolower(input.at(0));
                letter_input = letter_value;
                number_input = stoi(input.substr(1, input.size() - 1));
            }
        }

        if(!invalid_input)
        {
            row_index = letter_input - 97;
            col_index = number_input - 1;

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
        else
        {
            cout << "Invalid input." << endl;
        }
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

    cout << "Running " << num_of_simulations << " x " << empty_squares_vector.size() << " simulated trials" << endl;
    auto start = chrono::high_resolution_clock::now();
    static std::chrono::time_point<std::chrono::high_resolution_clock> t0, t2, t3;
    std::chrono::microseconds duration_fillUpBoardRandomly =  static_cast<std::chrono::microseconds>(0), 
        duration_pathAlgo_dfs = static_cast<std::chrono::microseconds>(0);
    //static std::chrono::time_point<std::chrono::high_resolution_clock> t1;
    //std::chrono::microseconds duration_pathAlgo_aStar = static_cast<std::chrono::microseconds>(0);

    int counter = 1;

    //initialize process board class object with copied hex board
    ProcessBoard processBoard(hex_board, board_size);

    for (unsigned int i = 0; i < empty_squares_vector.size(); i++)
    {
        int node_id_as_next_move = empty_squares_vector[i];
        int wins = 0, losses = 0;

        //cout << "." << flush;
        printf("\rSimulation trial %3d of %3d", counter,static_cast<int>(empty_squares_vector.size()));
        fflush(stdout);

        for (int simulation_number = 0; simulation_number < num_of_simulations; simulation_number++)
        {
            t0 = chrono::high_resolution_clock::now();

            processBoard.fill_board_randomly(player, node_id_as_next_move, empty_squares_vector);

            //t1 = chrono::high_resolution_clock::now();

            //bool playerWon2 = processBoard.game_won_check_aStar(player);

            t2 = chrono::high_resolution_clock::now();

            bool playerWon = processBoard.game_won_check_dfs(player);

            t3 = chrono::high_resolution_clock::now();

            //if (playerWon != playerWon2)
            //{
            //    cout << "\n\n\n\n\nERROR ERROR ERROR ERROR ERROR ERROR ERROR\n\n\n" << endl;
            //    exit(0);
            //}

            if (playerWon)
                wins++;
            else
                losses++;

            duration_fillUpBoardRandomly += chrono::duration_cast<chrono::microseconds>(t2 - t0);
            //duration_pathAlgo_aStar += chrono::duration_cast<chrono::microseconds>(t2 - t1);
            duration_pathAlgo_dfs += chrono::duration_cast<chrono::microseconds>(t3 - t2);
        }

        double win_loss_ratio = 1.0 * wins / losses;
        //char row_char = 'a' + node_id_as_next_move / board_size;
        //int col_num = node_id_as_next_move % board_size + 1;
        //cout << "win_loss_ratio for square " << row_char << col_num << " is " << win_loss_ratio << endl;
        counter++;

        if (win_loss_ratio > best_win_loss_ratio)
        {
            best_win_loss_ratio = win_loss_ratio;
            best_win_loss_ratio_node_id = node_id_as_next_move;
        }
    }

    char row_char = 'a' + best_win_loss_ratio_node_id / board_size;
    int col_num = best_win_loss_ratio_node_id % board_size + 1;
    cout << '\n' << '\n';
    if (player == Square::PlayerA)
        cout << playerA_name << " (" << static_cast<char>(Square::PlayerA) << ") picks " << row_char << col_num << endl;
    else
        cout << playerB_name << " (" << static_cast<char>(Square::PlayerB) << ") picks " << row_char << col_num << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration_total = chrono::duration_cast<chrono::milliseconds>(stop - start);
    unsigned int time_total = static_cast<unsigned int>(duration_total.count());
    unsigned int time_fillUpBoardRandomly = static_cast<unsigned int>(duration_fillUpBoardRandomly.count() / 1000);
    //unsigned int time_pathAlgo_aStar = static_cast<unsigned int>(duration_pathAlgo_aStar.count() / 1000);
    unsigned int time_pathAlgo_dfs = static_cast<unsigned int>(duration_pathAlgo_dfs.count() / 1000);
    printf("Total Time taken            : %7u ms\n", time_total);
    printf("time_fillUpBoardRandomly    : %7u ms  %3.2f%%\n", time_fillUpBoardRandomly, 1.0 * time_fillUpBoardRandomly / time_total * 100);
    //printf("time_pathAlgo_aStar         : %7u ms  %3.2f%%\n", time_pathAlgo_aStar, 1.0 * time_pathAlgo_aStar / time_total * 100);
    printf("time_pathAlgo_dfs           : %7u ms  %3.2f%%\n", time_pathAlgo_dfs, 1.0 * time_pathAlgo_dfs / time_total * 100);
    printf("time_tot - rand - pathalgos : %7u ms  %3.2f%%\n", time_total - time_fillUpBoardRandomly - time_pathAlgo_dfs, 1.0 * (time_total - time_fillUpBoardRandomly - time_pathAlgo_dfs) / time_total * 100);

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
    for (int i = 0; i < 2 * board_size - 1; i++)
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
    for (int print_blank = 0; print_blank < 2 * board_size - 4 + board_size; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size; i++)
        printf("--   ");

    //footer row
    cout << '\n' << '\t' << '\t' << " ";
    for (int print_blank = 0; print_blank < 2 * board_size - 5 + board_size; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size; i++)
        printf("%3d  ", i);

    cout << '\n' << '\n' << endl;
}

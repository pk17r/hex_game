#include <algorithm>
#include <chrono>
#include <iostream>
#include "PlayHexGameClass.h"

using namespace std;

PlayHexGameClass::PlayHexGameClass()
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

    if (play_game_)
    {
        string user_choice;
        cout << "Enter board size (default 11) (suffix with 'd' for debug mode): ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            if (user_choice.at(user_choice.size() - 1) == 'd')
            {
                debug_mode_ = true;
                user_choice = user_choice.substr(0, user_choice.size() - 1);
                cout << "Debug Mode ON" << endl;
            }
            board_size_ = stoi(user_choice);
        }
        cout << "board size = " << board_size_ << '\n' << endl;

        cout << "Enter Player A (" << static_cast<char>(Square::PlayerA) << ") name if human or press enter to make it computer: ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            playerA_type_ = PlayerType::Human;
            playerA_name_ = user_choice;
        }
        else
        {
            playerA_type_ = PlayerType::Computer;
            playerA_name_ = "Computer";
        }
        cout << "Player A (" << static_cast<char>(Square::PlayerA) << ") is " << playerA_name_ << '\n';

        cout << "\nEnter Player B (" << static_cast<char>(Square::PlayerB) << ") name if human or press enter to make it computer: ";
        getline(cin, user_choice);
        if (user_choice != "")
        {
            playerB_type_ = PlayerType::Human;
            playerB_name_ = user_choice;
        }
        else
        {
            playerB_type_ = PlayerType::Computer;
            playerB_name_ = "Computer";
        }
        cout << "Player B (" << static_cast<char>(Square::PlayerB) << ") is " << playerB_name_ << '\n';
    }
    else
    {
        playerA_type_ = PlayerType::Human;
        playerA_name_ = "Test Player";
        playerB_type_ = PlayerType::Computer;
        playerB_name_ = "Computer";
    }

    //playerA will make graph in vertical direction
    //playerB will make graph in horizontal direction

    //we will add two imaginary nodes - graph start and end nodes, to players graphs
    //we will use depth first search algorithm to find connecting path between these imaginary nodes
    //we will use the case of finding a solvable path between these two imaginary nodes as reaching the game's end
    //we connect a player's side nodes to these imaginary nodes to process whether game has been won

    //initialize hex board
    hex_board_ = new Square * [board_size_];
    for (int i = 0; i < board_size_; i++)
    {
        hex_board_[i] = new Square[board_size_];
    }
    for (int i = 0; i < board_size_; i++)
    {
        for (int j = 0; j < board_size_; j++)
        {
            hex_board_[i][j] = Square::Empty;
        }
    }

    //update empty_squares_list with all nodes
    empty_squares_vector_ = vector<int>(board_size_ * board_size_, 0);
    for (int i = 0; i < board_size_ * board_size_; i++)
    {
        empty_squares_vector_[i] = i;
    }

    //setting seed for random number generator engine
    unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
    my_random_engine_ = default_random_engine(seed);
}

PlayHexGameClass::~PlayHexGameClass()
{
    for (int i = 0; i < board_size_; i++)
    {
        delete hex_board_[i];
    }
    delete hex_board_;
}

void PlayHexGameClass::RunGame()
{
    PrintHexBoard();

    int moves = 0;

    bool player_won = false;

    //first turn is of PlayerA
    Square current_player = Square::PlayerA;
    PlayerType current_player_type = playerA_type_;
    int chosen_node_id = -1;

    //create object of ProcessHexBoardClass where game won check algo is implemented
    ProcessHexBoardClass processBoard;

    while (!player_won)
    {
        moves++;
        
        if (chosen_node_id >= 0)
        {
            char row_char = 'a' + chosen_node_id / board_size_;
            int col_num = chosen_node_id % board_size_ + 1;
            if(current_player == Square::PlayerA)
                cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") entered last move as : " << row_char << col_num << endl;
            else
                cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") entered last move as: " << row_char << col_num << endl;
        }

        //get player input
        if (current_player_type == PlayerType::Human)
            chosen_node_id = GetUserNextMove(current_player);
        else
            chosen_node_id = FindBestNextMove(current_player, processBoard);
        
        //fill hex board
        hex_board_[chosen_node_id / board_size_][chosen_node_id % board_size_] = current_player;

        //remove chosen_node_id from empty_squares_vector_
        for (auto iterator = empty_squares_vector_.begin(); iterator != empty_squares_vector_.end(); iterator++)
        {
            if (*iterator == chosen_node_id)
            {
                empty_squares_vector_.erase(iterator);
                break;
            }
        }

        //check game won by current player
        processBoard.CopyHexBoard(hex_board_);
        player_won = processBoard.GameWonCheckDfs(current_player);

        //if no one won, change player and continue to run game
        if (!player_won)
        {
            if (current_player == Square::PlayerA)
            {
                current_player = Square::PlayerB;
                current_player_type = playerB_type_;
            }
            else
            {
                current_player = Square::PlayerA;
                current_player_type = playerA_type_;
            }
        }

        //print hex board
        cout << '\n' << "Hex Board after " << moves << " moves:" << '\n';
        PrintHexBoard();
    }
    
    cout << '\n';
    if (current_player == Square::PlayerA)
        cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") Won!!!" << '\n' << endl;
    else
        cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") Won!!!" << '\n' << endl;
    cout << "Game won in " << moves << " moves!" << endl;
}

// return node_id
int PlayHexGameClass::GetUserNextMove(Square player)
{
    int row_index = -1, col_index = -1;
    if (player == Square::PlayerA)
        cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") win by making a connected path from Top-to-Bottom" << '\n';
    else
        cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") win by making a connected path from Left-to-Right" << '\n';
    
    while (true)
    {
        if (player == Square::PlayerA)
            cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") enter next move (e.g. x1): ";
        else
            cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") enter next move (e.g. x1): ";
    
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

            if (row_index >= 0 && col_index >= 0 && row_index < board_size_ && col_index < board_size_)
            {
                if (hex_board_[row_index][col_index] == Square::Empty)
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

    return row_index * board_size_ + col_index;
}

// return node_id
int PlayHexGameClass::FindBestNextMove(Square player, ProcessHexBoardClass& processBoard)
{
    /*
    -For each entry of list of empty squares run a simulation 1000 times

        - Fill all squares randomly

        - Check who won the game

        - Note win or loss for this simulation

        - Assign the entry with win / loss ratio

        - Return the entry with best win / loss ratio
    */

    //TIME NOTING START
    auto start = chrono::high_resolution_clock::now();
    //Simulation loop time clocks
    static std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1, t2;
    //time duration counters
    std::chrono::microseconds duration_shuffle_and_fill_up_board = static_cast<std::chrono::microseconds>(0),
        duration_who_won_using_dfs_algo = static_cast<std::chrono::microseconds>(0);

    //variables to track best win loss ratio move
    double best_win_loss_ratio = 0;
    int best_win_loss_ratio_node_id = -1;

    cout << "Running " << empty_squares_vector_.size() << "x" << num_of_simulations_ << " simulated trials" << endl;
    
    //copy hex board to ProcessHexBoardClass's hex board
    processBoard.CopyHexBoard(hex_board_);
    
    //initialize vector to shuffle empty squares
    std::vector<int> empty_squares_shuffle_vector;
    empty_squares_shuffle_vector.reserve(empty_squares_vector_.size() - 1);

    for (unsigned int i = 0; i < empty_squares_vector_.size(); i++)
    {
        int node_id_as_next_move = empty_squares_vector_[i];
        unsigned int wins = 0, losses = 0;

        for (unsigned int j = 0; j < empty_squares_vector_.size(); j++)
            if (empty_squares_vector_[j] != node_id_as_next_move)
                empty_squares_shuffle_vector.emplace_back(empty_squares_vector_[j]);

        if (!debug_mode_)
            printf("\rSimulation trial %6u of %6u", ((i + 1) * num_of_simulations_), (empty_squares_vector_.size() * num_of_simulations_));
        else
            printf("Simulation trial %6u of %6u, (%c)'s node_id_as_next_move %2d ", ((i + 1) * num_of_simulations_), (empty_squares_vector_.size() * num_of_simulations_), static_cast<char>(player), node_id_as_next_move);

        //run simulated trial runs, record win loss
        for (unsigned int simulation_number = 0; simulation_number < num_of_simulations_; simulation_number++)
        {
            //SHUFFLE AND FILL BOARD TIME START
            t0 = chrono::high_resolution_clock::now();

            //shuffle empty_squares_shuffle_vector vector
            shuffle(empty_squares_shuffle_vector.begin(), empty_squares_shuffle_vector.end(), my_random_engine_);

            //fill up board
            processBoard.FillBoardRandomly(player, node_id_as_next_move, empty_squares_shuffle_vector);

            //SHUFFLE AND FILL BOARD TIME END
            t1 = chrono::high_resolution_clock::now();
            //WHO WON DFS ALGO TIME START

            bool playerWon = processBoard.GameWonCheckDfs(player);

            //WHO WON DFS ALGO TIME END
            t2 = chrono::high_resolution_clock::now();

            if (playerWon)
                wins++;
            else
                losses++;

            duration_shuffle_and_fill_up_board += chrono::duration_cast<chrono::microseconds>(t1 - t0);
            duration_who_won_using_dfs_algo += chrono::duration_cast<chrono::microseconds>(t2 - t1);
        }

        //clear shuffle vector
        empty_squares_shuffle_vector.clear();

        double win_loss_ratio = 1.0 * wins / losses;
        if (debug_mode_)
        {
            char row_char = 'a' + node_id_as_next_move / board_size_;
            int col_num = node_id_as_next_move % board_size_ + 1;
            cout << " win_loss_ratio for square " << row_char << col_num << " is " << win_loss_ratio << endl;
        }
        
        if (win_loss_ratio > best_win_loss_ratio)
        {
            best_win_loss_ratio = win_loss_ratio;
            best_win_loss_ratio_node_id = node_id_as_next_move;
        }
    }

    //print best found next move
    cout << '\n' << '\n';
    char row_char = 'a' + best_win_loss_ratio_node_id / board_size_;
    int col_num = best_win_loss_ratio_node_id % board_size_ + 1;
    if (player == Square::PlayerA)
        cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") picks " << row_char << col_num << endl;
    else
        cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") picks " << row_char << col_num << endl;

    //TIME NOTING STOP
    auto stop = chrono::high_resolution_clock::now();
    auto duration_total = chrono::duration_cast<chrono::milliseconds>(stop - start);

    unsigned int time_total = static_cast<unsigned int>(duration_total.count());
    unsigned int time_shuffle_and_fill_up_board = static_cast<unsigned int>(duration_shuffle_and_fill_up_board.count() / 1000);
    unsigned int time_who_won_using_dfs_algo = static_cast<unsigned int>(duration_who_won_using_dfs_algo.count() / 1000);

    printf("Total Time taken               : %7u ms\n", time_total);
    printf("time_shuffle_and_fill_up_board : %7u ms  %3.2f%%\n", time_shuffle_and_fill_up_board, 1.0 * time_shuffle_and_fill_up_board / time_total * 100);
    printf("time_who_won_using_dfs_algo    : %7u ms  %3.2f%%\n", time_who_won_using_dfs_algo, 1.0 * time_who_won_using_dfs_algo / time_total * 100);
    printf("time_tot - shuffle - pathalgos : %7u ms  %3.2f%%\n", time_total - time_shuffle_and_fill_up_board - time_who_won_using_dfs_algo, 1.0 * (time_total - time_shuffle_and_fill_up_board - time_who_won_using_dfs_algo) / time_total * 100);

    return best_win_loss_ratio_node_id;
}

void PlayHexGameClass::PrintHexBoard()
{
    cout << '\n';
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << "  |  top-to-bottom  | " << playerA_name_  << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << "  |  left-to-right  | " << playerB_name_ << '\n';
    cout << '\n' << '\n';

    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= board_size_; i++)
        printf("%3d  ", i);
    cout << '\n';

    cout << '\t' << "     ";
    for (int i = 1; i <= board_size_; i++)
        printf(" --  ");
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < 2 * board_size_ - 1; i++)
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
            for (int j = 0; j < board_size_; j++)
            {
                cout << static_cast<char>(hex_board_[i / 2][j]);
                if (j < board_size_ - 1)
                    cout << "    ";
            }

            //row label right
            cout << "   \\  " << letter++;
        }
        
        cout << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < 2 * board_size_ - 4 + board_size_; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size_; i++)
        printf("--   ");

    //footer row
    cout << '\n' << '\t' << '\t' << " ";
    for (int print_blank = 0; print_blank < 2 * board_size_ - 5 + board_size_; print_blank++)
        cout << " ";
    for (int i = 1; i <= board_size_; i++)
        printf("%3d  ", i);

    cout << '\n' << '\n' << endl;
}

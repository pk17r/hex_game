#include <cassert>
#include <cstring>
#include <future>
#include <iostream>
#include "GamePlayClass.h"
#include <thread>

using namespace std;

GamePlayClass::GamePlayClass()
{
    
    if (!test_print_hex_board_)
        GetGameParametersInput();

    //playerA will make graph in vertical direction
    //playerB will make graph in horizontal direction

    //we will add two imaginary nodes - graph start and end nodes, to players graphs
    //we will use depth first search algorithm to find connecting path between these imaginary nodes
    //we will use the case of finding a solvable path between these two imaginary nodes as reaching the game's end
    //we connect a player's side nodes to these imaginary nodes to process whether game has been won

    //initialize hex board
    HexBoardInitialize();
    HexBoardOwnerClass = "GamePlayClass()";

    //update empty_squares_vector_ with all nodes
    empty_squares_vector_ = vector<int>(get_board_size_() * get_board_size_(), 0);
    for (int i = 0; i < get_board_size_() * get_board_size_(); i++)
    {
        empty_squares_vector_[i] = i;
    }

    //initialize simulation hex boards if either player is a computer
    if (playerA_type_ == PlayerType::Computer || playerB_type_ == PlayerType::Computer)
        CreateSimulationHexBoards();
}

GamePlayClass::~GamePlayClass()
{
    cout << "\n\nCalling destructors..." << endl;
    simulation_hex_boards_ptr_vector_.clear();
    cout << "~GamePlayClass()" << endl;
}

void GamePlayClass::RunGame()
{
    PrintHexBoard();

    if (test_print_hex_board_)
        return;

    int moves = 0;

    bool player_won = false;

    //first turn is of PlayerA
    Square current_player = Square::PlayerA;
    PlayerType current_player_type = playerA_type_;
    int next_move_node_id = -1;
    BestWinLossRatio bestWinLossRatio;

    while (!player_won)
    {
        moves++;
        
        if (next_move_node_id >= 0)
        {
            if (current_player == Square::PlayerA)
                cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB);
            else
                cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA);
            cout << ") entered last move as (" << get_row_char_(next_move_node_id) << get_col_number_(next_move_node_id) << ")";
            if (bestWinLossRatio.best_win_loss_ratio_node_id != -1)
            {
                cout << " with a win_loss_ratio of " << bestWinLossRatio.best_win_loss_ratio;
                bestWinLossRatio.best_win_loss_ratio_node_id = -1;
            }
            cout << endl;
        }

        //get or find next move
        if (current_player_type == PlayerType::Human)
            next_move_node_id = GetUserNextMove(current_player);
        else
        {
            bestWinLossRatio = FindBestNextMove(current_player, false);
            next_move_node_id = bestWinLossRatio.best_win_loss_ratio_node_id;
        }
        
        //fill hex board with next move
        set_hex_board_ownership_(next_move_node_id, current_player);

        //remove next_move_node_id from empty_squares_vector_
        for (auto iterator = empty_squares_vector_.begin(); iterator != empty_squares_vector_.end(); iterator++)
        {
            if (*iterator == next_move_node_id)
            {
                empty_squares_vector_.erase(iterator);
                break;
            }
        }

        //check game won by current player
        player_won = GameWonCheckDfsAlgo(current_player);

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

void GamePlayClass::RunSim(int sim_index, Square player, unsigned int from_index, unsigned int to_index)
{
    best_win_loss_ratio_vector.push_back((simulation_hex_boards_ptr_vector_.at(sim_index))->MonteCarloSimulationsToFindBestNextMove(player, from_index, to_index));
}

BestWinLossRatio GamePlayClass::FindBestNextMove(Square player, bool give_hint_to_user)
{
    /*
    -For each entry of empty squares run a simulation 1000 times

        - Fill all squares randomly

        - Check who won the game

        - Note win or loss for this simulation

        - Assign the entry with win / loss ratio

        - Return the entry with best win / loss ratio
    */

    //TIME NOTING START
    auto start = chrono::high_resolution_clock::now();
    
    cout << "Running " << empty_squares_vector_.size() * num_of_simulations_ << " simulated trials" << (give_hint_to_user ? " for hint to user" : "") << endl;

    //copy hex board to simulation hex boards and run simulations
    //unsigned int hex_board_memory_space = sizeof(Square) * get_board_size_() * get_board_size_();

    unsigned int indices_to_simulate_by_every_simulator = static_cast<unsigned int>(ceil(1.0 * empty_squares_vector_.size() / simulation_hex_boards_ptr_vector_.size()));
    unsigned int last_to_index = 0;

    vector<thread> ThreadVector;

    //Simulation loop time clocks
    static std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1;
    std::chrono::nanoseconds duration_copy_hex_board_to_simulation = static_cast<std::chrono::nanoseconds>(0);

    unsigned int sim_i = 0;
    while(sim_i < simulation_hex_boards_ptr_vector_.size())
    {
        if (last_to_index >= empty_squares_vector_.size())
            break;

        //COPY HEX BOARD TIME START
        t0 = chrono::high_resolution_clock::now();

        //fill simulation hex boards with game play hex board
        for (int i = 0; i < get_board_size_(); i++)
        {
            for (int j = 0; j < get_board_size_(); j++)
            {
                simulation_hex_boards_ptr_vector_.at(sim_i)->hex_board_[i][j] = hex_board_[i][j];
            }
        }
        //memcpy(simulation_hex_boards_ptr_vector_.at(sim_i)->hex_board_, this->hex_board_, hex_board_memory_space);

        //COPY HEX BOARD TIME STOP
        t1 = chrono::high_resolution_clock::now();
        duration_copy_hex_board_to_simulation += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);

        //create simulation threads
        ThreadVector.emplace_back(thread (&GamePlayClass::RunSim, sim_i, player, last_to_index, last_to_index + indices_to_simulate_by_every_simulator));

        last_to_index += indices_to_simulate_by_every_simulator;
        sim_i++;
    }

    //wait for completion of simulation threads
    for(auto t_ptr = ThreadVector.begin(); t_ptr != ThreadVector.end(); t_ptr++)
    {
        t_ptr->join();
    }

    //collate simulation data to find out best next move node id
    BestWinLossRatio bestWinLossRatio;
    unsigned int time_shuffle_and_fill_up_board = 0;
    unsigned int time_who_won_using_dfs_algo = 0;
    for (int i = 0; i < static_cast<int>(best_win_loss_ratio_vector.size()); i++)
    {
        time_shuffle_and_fill_up_board += best_win_loss_ratio_vector.at(i).time_shuffle_and_fill_up_board;
        time_who_won_using_dfs_algo += best_win_loss_ratio_vector.at(i).time_who_won_using_dfs_algo;
        if (best_win_loss_ratio_vector.at(i).best_win_loss_ratio > bestWinLossRatio.best_win_loss_ratio)
        {
            //update best next move node id according to best win loss ratio
            bestWinLossRatio.best_win_loss_ratio_node_id = best_win_loss_ratio_vector.at(i).best_win_loss_ratio_node_id;
            bestWinLossRatio.best_win_loss_ratio = best_win_loss_ratio_vector.at(i).best_win_loss_ratio;
        }
    }
    //clear simulation results
    best_win_loss_ratio_vector.clear();

    //print best found next move
    if(!give_hint_to_user)
        cout << "\n\n(" << static_cast<char>(player) << ") picks (" << get_row_char_(bestWinLossRatio.best_win_loss_ratio_node_id) << get_col_number_(bestWinLossRatio.best_win_loss_ratio_node_id) << ") with win_loss_ratio of " << bestWinLossRatio.best_win_loss_ratio << endl;
    else
        cout << "\n\nBest suggested move is (" << get_row_char_(bestWinLossRatio.best_win_loss_ratio_node_id) << get_col_number_(bestWinLossRatio.best_win_loss_ratio_node_id) << ") with a win_loss_ratio of " << bestWinLossRatio.best_win_loss_ratio << '\n' << endl;

    //TIME NOTING STOP
    auto stop = chrono::high_resolution_clock::now();
    auto duration_total = chrono::duration_cast<chrono::milliseconds>(stop - start);
    unsigned int time_total = static_cast<unsigned int>(duration_total.count());
    unsigned int time_copy_hex_board_to_simulation = static_cast<unsigned int>(duration_copy_hex_board_to_simulation.count() / 1000);

    if (!give_hint_to_user)
    {
        printf("Total Time taken                              : %7u ms\n", time_total);
        printf("time_copy_hex_board_to_simulation             : %7u us  %3.2f%%\n", time_copy_hex_board_to_simulation, 1.0 * time_copy_hex_board_to_simulation / time_total * 100);
        printf("Multi-threaded time_shuffle_and_fill_up_board : %7u ms  %3.2f%%\n", time_shuffle_and_fill_up_board, 1.0 * time_shuffle_and_fill_up_board / time_total * 100);
        printf("Multi-threaded time_who_won_using_dfs_algo    : %7u ms  %3.2f%%\n", time_who_won_using_dfs_algo, 1.0 * time_who_won_using_dfs_algo / time_total * 100);
        printf("Threads used  : %u\n", sim_i);
    }
    return bestWinLossRatio;
}

int GamePlayClass::GetUserNextMove(Square player)
{
    FindBestNextMove(player, true);

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

            if (BoundsCheck(row_index, col_index))
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

    return get_node_id_(row_index, col_index);
}

void GamePlayClass::GetGameParametersInput()
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
        set_board_size_(stoi(user_choice));
    }
    cout << "board size = " << get_board_size_() << '\n' << endl;

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

void GamePlayClass::CreateSimulationHexBoards()
{
    unsigned int nthreads = std::thread::hardware_concurrency();
    cout << "nthreads = " << nthreads << endl;

    for (unsigned int i = 0; i < nthreads; i++)
    {
        shared_ptr<SimulationHexBoard> p = make_shared<SimulationHexBoard>();
        simulation_hex_boards_ptr_vector_.emplace_back(p);
    }
}

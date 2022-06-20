#include <iostream>
#include "GamePlayClass.h"

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
    hex_board_ = new Square * [get_board_size_()];
    for (int i = 0; i < get_board_size_(); i++)
    {
        hex_board_[i] = new Square[get_board_size_()];
    }
    for (int i = 0; i < get_board_size_(); i++)
    {
        for (int j = 0; j < get_board_size_(); j++)
        {
            hex_board_[i][j] = Square::Empty;
        }
    }

    //initialize hex board of ProcessHexBoardClass
    ProcessHexBoardClassInitialize();

    //update empty_squares_vector_ with all nodes
    empty_squares_vector_ = vector<int>(get_board_size_() * get_board_size_(), 0);
    for (int i = 0; i < get_board_size_() * get_board_size_(); i++)
    {
        empty_squares_vector_[i] = i;
    }
}

GamePlayClass::~GamePlayClass()
{
    for (int i = 0; i < get_board_size_(); i++)
    {
        delete hex_board_[i];
    }
    delete hex_board_;
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

    while (!player_won)
    {
        moves++;
        
        if (next_move_node_id >= 0)
        {
            char row_char = 'a' + get_row_index_(next_move_node_id);
            int col_num = get_col_index_(next_move_node_id) + 1;
            if(current_player == Square::PlayerA)
                cout << playerB_name_ << " (" << static_cast<char>(Square::PlayerB) << ") entered last move as : " << row_char << col_num << endl;
            else
                cout << playerA_name_ << " (" << static_cast<char>(Square::PlayerA) << ") entered last move as: " << row_char << col_num << endl;
        }

        //get or find next move
        if (current_player_type == PlayerType::Human)
            next_move_node_id = GetUserNextMove(current_player);
        else
            next_move_node_id = FindBestNextMove(current_player);
        
        //fill hex board with next move
        hex_board_[get_row_index_(next_move_node_id)][get_col_index_(next_move_node_id)] = current_player;

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
        CopyHexBoardToProcessHexBoardClass(hex_board_);
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

int GamePlayClass::FindBestNextMove(Square player)
{
    //copy hex board to ProcessHexBoardClass's hex board
    CopyHexBoardToProcessHexBoardClass(hex_board_);

    return MonteCarloSimulationsToFindBestNextMove(player, empty_squares_vector_);
}

int GamePlayClass::GetUserNextMove(Square player)
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

void GamePlayClass::PrintHexBoard()
{
    cout << '\n';
    cout << "\t\t\t  Hex Game" << '\n' << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerA) << "  |  top-to-bottom  | " << playerA_name_  << '\n';
    cout << "\t\t" << static_cast<char>(Square::PlayerB) << "  |  left-to-right  | " << playerB_name_ << '\n';
    cout << '\n' << '\n';

    //header row
    cout << '\t' << "    ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("%3d  ", i);
    cout << '\n';

    cout << '\t' << "     ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf(" --  ");
    cout << '\n';

    char letter = 'a';

    //board body
    for (int i = 0; i < 2 * get_board_size_() - 1; i++)
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
            for (int j = 0; j < get_board_size_(); j++)
            {
                cout << static_cast<char>(hex_board_[i / 2][j]);
                if (j < get_board_size_() - 1)
                    cout << "    ";
            }

            //row label right
            cout << "   \\  " << letter++;
        }
        
        cout << '\n';
    }

    cout << '\t' << '\t';
    for (int print_blank = 0; print_blank < 2 * get_board_size_() - 4 + get_board_size_(); print_blank++)
        cout << " ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("--   ");

    //footer row
    cout << '\n' << '\t' << '\t' << " ";
    for (int print_blank = 0; print_blank < 2 * get_board_size_() - 5 + get_board_size_(); print_blank++)
        cout << " ";
    for (int i = 1; i <= get_board_size_(); i++)
        printf("%3d  ", i);

    cout << '\n' << '\n' << endl;
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

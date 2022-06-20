# Hex Game

Author: Prashant Kumar

Date: June 16th 2022

Program to Play Human vs Human or vs Computer or Computer vs Computer

Compile using:

g++ -Wall -g main.cpp *.cc -o main.exe

Run main.exe

-------

## Representation:

A size 5 hex board has 5x5 squares.

Squares have 3 types – PlayerA, PlayerB or Empty.

Every Square acts as a node for path algorithms. Nodes have sequential ids from 0 to n x n - 1. For path algorithm purpose, an imaginary start and end node is created. Start and end nodes have the same id for PlayerA and PlayerB. Start node is given id -2 and end node -3. Nodes from one side are connected to start node and other side to end node as shown in representation below.


![Screenshot](Representation.png)

-------

## Program Structure

1. Game Constants

   - Player A is X (top to bottom), Player B is O (left to right)

   - Player Types – Human/Computer

   - Board Size

2. Functions

   - Check game won by a player (using Depth First Search)

   - Randomly Fill up Whole Board

   - Take User Input Move

   - Print Hex Board

3. Game Play

   - Hex Board with Current Positions

   - Best_next_move() Trial function to try out all legal moves 1000 times and classify each move with win loss ratio – return move with best win loss ratio

     - Vector of empty squares

     - For every square 1000 trials of randomly filling up board, noting who won and adding it to PlayerA or PlayerB

     - Returning best next move for PlayerA or PlayerB


-------

## Class Structure

1. Square: char

   - playerA = 'X',

   - playerB = 'O',

   - empty = '.',

2. Node

   - int id = kNullId;

   - int nearest_node_id = kNullId;

   - int distance = 1;    //distance to every node is 1 for hex game

   - static const int kNullId = -1;    //Node ids will be whole numbers

   - static const int graph_start_id = -2;    //an imaginary node id to start player's hex board graph from

   - static const int graph_end_id = -3;    //an imaginary node id to end player's hex board graph to

3. enum class PlayerType

   - Human = 0,

   - Computer = 1,

4. enum class Square : char

   - PlayerA = 'X',

   - PlayerB = 'O',

   - Empty = '.',

5. GameClass

   - playerA_type 0 – human /1 - computer

   - playerB_type 0 – human /1 – computer

   - playerA_name

   - playerB_name

   - board_size – 5 for testing, 11 for production

   - hex_board – pointer to pointer of Square

   - empty_squares_list – all squares have an id, we maintain an empty ids list to pick from

   - Functions:
   
     - GameClass(), constructor to initialize class object

     - take_user_input(Square player), return node_id
	 
	 - RunGame()

     - best_next_move(Square player), return node_id

     - print_hex_board()

6. ProcessBoard Class

   - Functions:
   
     - ProcessBoard(Square** hex_board_data, int board_size_data), constructor to create a copy of hex board and run simulation trials on it

     - bool game_won_check(Square player), (using Depth First Search), return 0 for game not won, 1 for game won

     - void fill_board_randomly(Square player, int node_id_as_next_move, std::list<int> empty_squares_list)


-------

## Pseudo Code

1. Load Game Constants

2. RunGame

   - If player == human

     - Take user input

   - Else player == computer

     - For each entry of list of empty squares run a simulation 1000 times

       - Fill all squares randomly

       - Check who won the game

       - Note win or loss for this simulation

       - Assign the entry with win/loss ratio

     - Return the entry with best win/loss ratio

   - Check if game is won, if yes then break else run the above for the other player

-------

## Game Runtime Output
    C:\Programming\3.C++forCProgrammers\Hex_Game>g++ -Wall -g main.cpp *.cc -o main.exe
    
    C:\Programming\3.C++forCProgrammers\Hex_Game>main.exe
    
    
    
                                    Hex Game
    
    
                           1    2    3    4    5
                           --   --   --   --   --
                      a  \   .    .    .    X    O   \  a
    
                        b  \   .    .    O    X    .   \  b
    
                          c  \   .    .    X    O    .   \  c
    
                            d  \   .    X    .    .    .   \  d
    
                              e  \   O    X    .    .    .   \  e
                                     --   --   --   --   --
                                      1    2    3    4    5
    
    
    Program to Play Human vs Human or vs Computer or Computer vs Computer
    
    X goes first and takes vertical direction, O goes second and takes horizontal direction.
    
    To play computer vs computer, make both players computer
    To play human vs computer or computer vs human, select accordingly on cmd
    
    Play to win!
    
    Enter board size (default 11) (suffix with 'd' for debug mode):
    board size = 11
    
    Enter Player A (X) name if human or press enter to make it computer:
    Player A (X) is Computer
    
    Enter Player B (O) name if human or press enter to make it computer:
    Player B (O) is Computer
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    .    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Running 121x1000 simulated trials
    Simulation trial 121000 of 121000
    
    Computer (X) picks f8
    Total Time taken            :    4438 ms
    time_fillUpBoardRandomly    :     991 ms  22.33%
    time_dfs_Algo               :    3358 ms  75.66%
    time_tot - rand - pathalgos :      89 ms  2.01%
    
    Hex Board after 1 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    .    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: f8
    Running 120x1000 simulated trials
    Simulation trial 120000 of 120000
    
    Computer (O) picks h6
    Total Time taken            :    3449 ms
    time_fillUpBoardRandomly    :     988 ms  28.65%
    time_dfs_Algo               :    2394 ms  69.41%
    time_tot - rand - pathalgos :      67 ms  1.94%
    
    Hex Board after 2 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    .    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    .    O    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : h6
    Running 119x1000 simulated trials
    Simulation trial 119000 of 119000
    
    Computer (X) picks c7
    Total Time taken            :    4185 ms
    time_fillUpBoardRandomly    :     988 ms  23.61%
    time_dfs_Algo               :    2976 ms  71.11%
    time_tot - rand - pathalgos :     221 ms  5.28%
    
    Hex Board after 3 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    .    O    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: c7
    Running 118x1000 simulated trials
    Simulation trial 118000 of 118000
    
    Computer (O) picks h5
    Total Time taken            :    3514 ms
    time_fillUpBoardRandomly    :     966 ms  27.49%
    time_dfs_Algo               :    2458 ms  69.95%
    time_tot - rand - pathalgos :      90 ms  2.56%
    
    Hex Board after 4 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : h5
    Running 117x1000 simulated trials
    Simulation trial 117000 of 117000
    
    Computer (X) picks g8
    Total Time taken            :    4144 ms
    time_fillUpBoardRandomly    :    1000 ms  24.13%
    time_dfs_Algo               :    3026 ms  73.02%
    time_tot - rand - pathalgos :     118 ms  2.85%
    
    Hex Board after 5 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: g8
    Running 116x1000 simulated trials
    Simulation trial 116000 of 116000
    
    Computer (O) picks h7
    Total Time taken            :    3571 ms
    time_fillUpBoardRandomly    :     940 ms  26.32%
    time_dfs_Algo               :    2515 ms  70.43%
    time_tot - rand - pathalgos :     116 ms  3.25%
    
    Hex Board after 6 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : h7
    Running 115x1000 simulated trials
    Simulation trial 115000 of 115000
    
    Computer (X) picks h8
    Total Time taken            :    4105 ms
    time_fillUpBoardRandomly    :     940 ms  22.90%
    time_dfs_Algo               :    3077 ms  74.96%
    time_tot - rand - pathalgos :      88 ms  2.14%
    
    Hex Board after 7 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    .    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: h8
    Running 114x1000 simulated trials
    Simulation trial 114000 of 114000
    
    Computer (O) picks j7
    Total Time taken            :    3506 ms
    time_fillUpBoardRandomly    :     877 ms  25.01%
    time_dfs_Algo               :    2526 ms  72.05%
    time_tot - rand - pathalgos :     103 ms  2.94%
    
    Hex Board after 8 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    .    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : j7
    Running 113x1000 simulated trials
    Simulation trial 113000 of 113000
    
    Computer (X) picks j8
    Total Time taken            :    4011 ms
    time_fillUpBoardRandomly    :     915 ms  22.81%
    time_dfs_Algo               :    2993 ms  74.62%
    time_tot - rand - pathalgos :     103 ms  2.57%
    
    Hex Board after 9 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: j8
    Running 112x1000 simulated trials
    Simulation trial 112000 of 112000
    
    Computer (O) picks d8
    Total Time taken            :    3427 ms
    time_fillUpBoardRandomly    :     879 ms  25.65%
    time_dfs_Algo               :    2460 ms  71.78%
    time_tot - rand - pathalgos :      88 ms  2.57%
    
    Hex Board after 10 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    O    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : d8
    Running 111x1000 simulated trials
    Simulation trial 111000 of 111000
    
    Computer (X) picks i8
    Total Time taken            :    3776 ms
    time_fillUpBoardRandomly    :     874 ms  23.15%
    time_dfs_Algo               :    2824 ms  74.79%
    time_tot - rand - pathalgos :      78 ms  2.07%
    
    Hex Board after 11 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    O    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: i8
    Running 110x1000 simulated trials
    Simulation trial 110000 of 110000
    
    Computer (O) picks d9
    Total Time taken            :    3325 ms
    time_fillUpBoardRandomly    :     886 ms  26.65%
    time_dfs_Algo               :    2333 ms  70.17%
    time_tot - rand - pathalgos :     106 ms  3.19%
    
    Hex Board after 12 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : d9
    Running 109x1000 simulated trials
    Simulation trial 109000 of 109000
    
    Computer (X) picks e7
    Total Time taken            :    3622 ms
    time_fillUpBoardRandomly    :     843 ms  23.27%
    time_dfs_Algo               :    2689 ms  74.24%
    time_tot - rand - pathalgos :      90 ms  2.48%
    
    Hex Board after 13 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    .    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: e7
    Running 108x1000 simulated trials
    Simulation trial 108000 of 108000
    
    Computer (O) picks d7
    Total Time taken            :    3205 ms
    time_fillUpBoardRandomly    :     854 ms  26.65%
    time_dfs_Algo               :    2248 ms  70.14%
    time_tot - rand - pathalgos :     103 ms  3.21%
    
    Hex Board after 14 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    O    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    .    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : d7
    Running 107x1000 simulated trials
    Simulation trial 107000 of 107000
    
    Computer (X) picks d6
    Total Time taken            :    3383 ms
    time_fillUpBoardRandomly    :     820 ms  24.24%
    time_dfs_Algo               :    2483 ms  73.40%
    time_tot - rand - pathalgos :      80 ms  2.36%
    
    Hex Board after 15 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    .    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: d6
    Running 106x1000 simulated trials
    Simulation trial 106000 of 106000
    
    Computer (O) picks e6
    Total Time taken            :    3077 ms
    time_fillUpBoardRandomly    :     785 ms  25.51%
    time_dfs_Algo               :    2202 ms  71.56%
    time_tot - rand - pathalgos :      90 ms  2.92%
    
    Hex Board after 16 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : e6
    Running 105x1000 simulated trials
    Simulation trial 105000 of 105000
    
    Computer (X) picks f5
    Total Time taken            :    3217 ms
    time_fillUpBoardRandomly    :     774 ms  24.06%
    time_dfs_Algo               :    2368 ms  73.61%
    time_tot - rand - pathalgos :      75 ms  2.33%
    
    Hex Board after 17 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    .    .    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: f5
    Running 104x1000 simulated trials
    Simulation trial 104000 of 104000
    
    Computer (O) picks e5
    Total Time taken            :    2983 ms
    time_fillUpBoardRandomly    :     757 ms  25.38%
    time_dfs_Algo               :    2139 ms  71.71%
    time_tot - rand - pathalgos :      87 ms  2.92%
    
    Hex Board after 18 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    .    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : e5
    Running 103x1000 simulated trials
    Simulation trial 103000 of 103000
    
    Computer (X) picks e4
    Total Time taken            :    3009 ms
    time_fillUpBoardRandomly    :     753 ms  25.02%
    time_dfs_Algo               :    2193 ms  72.88%
    time_tot - rand - pathalgos :      63 ms  2.09%
    
    Hex Board after 19 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    .    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: e4
    Running 102x1000 simulated trials
    Simulation trial 102000 of 102000
    
    Computer (O) picks f4
    Total Time taken            :    2790 ms
    time_fillUpBoardRandomly    :     727 ms  26.06%
    time_dfs_Algo               :    1989 ms  71.29%
    time_tot - rand - pathalgos :      74 ms  2.65%
    
    Hex Board after 20 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    .    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : f4
    Running 101x1000 simulated trials
    Simulation trial 101000 of 101000
    
    Computer (X) picks d10
    Total Time taken            :    2887 ms
    time_fillUpBoardRandomly    :     750 ms  25.98%
    time_dfs_Algo               :    2053 ms  71.11%
    time_tot - rand - pathalgos :      84 ms  2.91%
    
    Hex Board after 21 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: d10
    Running 100x1000 simulated trials
    Simulation trial 100000 of 100000
    
    Computer (O) picks c10
    Total Time taken            :    2832 ms
    time_fillUpBoardRandomly    :     698 ms  24.65%
    time_dfs_Algo               :    2073 ms  73.20%
    time_tot - rand - pathalgos :      61 ms  2.15%
    
    Hex Board after 22 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    .   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : c10
    Running 99x1000 simulated trials
    Simulation trial  99000 of  99000
    
    Computer (X) picks c11
    Total Time taken            :    2683 ms
    time_fillUpBoardRandomly    :     687 ms  25.61%
    time_dfs_Algo               :    1937 ms  72.20%
    time_tot - rand - pathalgos :      59 ms  2.20%
    
    Hex Board after 23 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: c11
    Running 98x1000 simulated trials
    Simulation trial  98000 of  98000
    
    Computer (O) picks b11
    Total Time taken            :    2758 ms
    time_fillUpBoardRandomly    :     705 ms  25.56%
    time_dfs_Algo               :    1967 ms  71.32%
    time_tot - rand - pathalgos :      86 ms  3.12%
    
    Hex Board after 24 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    .    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : b11
    Running 97x1000 simulated trials
    Simulation trial  97000 of  97000
    
    Computer (X) picks f3
    Total Time taken            :    2476 ms
    time_fillUpBoardRandomly    :     675 ms  27.26%
    time_dfs_Algo               :    1732 ms  69.95%
    time_tot - rand - pathalgos :      69 ms  2.79%
    
    Hex Board after 25 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: f3
    Running 96x1000 simulated trials
    Simulation trial  96000 of  96000
    
    Computer (O) picks g3
    Total Time taken            :    2376 ms
    time_fillUpBoardRandomly    :     656 ms  27.61%
    time_dfs_Algo               :    1656 ms  69.70%
    time_tot - rand - pathalgos :      64 ms  2.69%
    
    Hex Board after 26 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    .    O    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : g3
    Running 95x1000 simulated trials
    Simulation trial  95000 of  95000
    
    Computer (X) picks g2
    Total Time taken            :    2399 ms
    time_fillUpBoardRandomly    :     626 ms  26.09%
    time_dfs_Algo               :    1692 ms  70.53%
    time_tot - rand - pathalgos :      81 ms  3.38%
    
    Hex Board after 27 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    X    O    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    .    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: g2
    Running 94x1000 simulated trials
    Simulation trial  94000 of  94000
    
    Computer (O) picks h2
    Total Time taken            :    2301 ms
    time_fillUpBoardRandomly    :     639 ms  27.77%
    time_dfs_Algo               :    1589 ms  69.06%
    time_tot - rand - pathalgos :      73 ms  3.17%
    
    Hex Board after 28 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    X    O    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    O    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (O) entered last move as : h2
    Running 93x1000 simulated trials
    Simulation trial  93000 of  93000
    
    Computer (X) picks i1
    Total Time taken            :    2275 ms
    time_fillUpBoardRandomly    :     582 ms  25.58%
    time_dfs_Algo               :    1632 ms  71.74%
    time_tot - rand - pathalgos :      61 ms  2.68%
    
    Hex Board after 29 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    X    O    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   .    O    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   X    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    Computer (X) entered last move as: i1
    Running 92x1000 simulated trials
    Simulation trial  92000 of  92000
    
    Computer (O) picks h1
    Total Time taken            :    2216 ms
    time_fillUpBoardRandomly    :     593 ms  26.76%
    time_dfs_Algo               :    1547 ms  69.81%
    time_tot - rand - pathalgos :      76 ms  3.43%
    
    Hex Board after 30 moves:
    
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9   10   11
                  --   --   --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .    .    O   \  b
    
                  c  \   .    .    .    .    .    .    X    .    .    O    X   \  c
    
                     d  \   .    .    .    .    .    X    O    O    O    X    .   \  d
    
                        e  \   .    .    .    X    O    O    X    .    .    .    .   \  e
    
                           f  \   .    .    X    O    X    .    .    X    .    .    .   \  f
    
                              g  \   .    X    O    .    .    .    .    X    .    .    .   \  g
    
                                 h  \   O    O    .    .    O    O    O    X    .    .    .   \  h
    
                                    i  \   X    .    .    .    .    .    .    X    .    .    .   \  i
    
                                       j  \   .    .    .    .    .    .    O    X    .    .    .   \  j
    
                                          k  \   .    .    .    .    .    .    .    .    .    .    .   \  k
                                                 --   --   --   --   --   --   --   --   --   --   --
                                                   1    2    3    4    5    6    7    8    9   10   11
    
    
    
    Computer (O) Won!!!
    
    Game won in 30 moves!
    
    C:\Programming\3.C++forCProgrammers\Hex_Game>
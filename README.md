# Hex Game

Author: Prashant Kumar

Date: June 16th 2022

Program to Play Human vs Human or vs Computer or Computer vs Computer

Compile using:

g++ -std=c++11 -pthread -Wall -g main.cpp *.cc -o main.exe

Run main.exe

Tested on Windows Machine with Visual Studio 2022. Not tested on Linux Machine.

-------

## Program Highlights:

   - Implements inheritance
   
   - Runs Monte Carlo Simulations to find next best move for computer
   
   - uses shared_ptr
   
   - implements multithreading -> tested on Windows laptop with Visual Studio IDE
   
   - uses static functions and variables
   
   - overall 3 classes are there
   
     - HexBoard
	 
	 - GamePlayClass : HexBoard
	 
	 - SimulationHexBoard : HexBoard
	 
   - Implements Depth First Search to find game is won
   
   - Program output pasted below.
   
   - Time: On a 8 thread computer, runs over a million simulations on a 11x11 size hex board in under 4 seconds

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

   - Empty = '.',

   - PlayerA = 'X',

   - PlayerB = 'O',

5. HexBoard Class -> maintains hex board


6. GamePlayClass : HexBoard -> inherits HexBoard and runs game over it
							-> also makes Simulation HexBoards on which simulated runs are run to find best next move for computer
							-> implements multithreading -> tested on Windows 10, Visual Studio IDE

7. SimulationHexBoard: HexBoard -> inherits HexBoard and runs simulated runs over it to find best next move for computer

-------

## Pseudo Code (not updated with latest)

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
    
    Enter board size (default 11) (suffix with 'd' for debug mode): 9
    board size = 9
    
    Enter Player A (X) name if human or press enter to make it computer:
    Player A (X) is Computer
    
    Enter Player B (O) name if human or press enter to make it computer:
    Player B (O) is Computer
    nthreads = 8
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    .    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:81, playerA:0, playerB:0, other:0
    
    Running 810000 simulated trials
    .................................................................................
    
    (X) picks h2
    Total Time taken                              :    1792 ms
    time_copy_hex_board_to_simulation             :       2 us  0.11%
    Multi-threaded time_shuffle_and_fill_up_board :      42 ms  2.34%
    Multi-threaded time_who_won_using_dfs_algo    :    1729 ms  96.48%
    Threads used  : 8
    
    Hex Board after 1 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    .    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:80, playerA:1, playerB:0, other:0
    
    Computer (X) entered last move as: h2
    Running 800000 simulated trials
    ................................................................................
    
    (O) picks c7
    Total Time taken                              :    1410 ms
    time_copy_hex_board_to_simulation             :       2 us  0.14%
    Multi-threaded time_shuffle_and_fill_up_board :      31 ms  2.20%
    Multi-threaded time_who_won_using_dfs_algo    :    1361 ms  96.52%
    Threads used  : 8
    
    Hex Board after 2 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    .    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:79, playerA:1, playerB:1, other:0
    
    Computer (O) entered last move as: c7
    Running 790000 simulated trials
    ...............................................................................
    
    (X) picks d4
    Total Time taken                              :    1658 ms
    time_copy_hex_board_to_simulation             :       2 us  0.12%
    Multi-threaded time_shuffle_and_fill_up_board :      29 ms  1.75%
    Multi-threaded time_who_won_using_dfs_algo    :    1608 ms  96.98%
    Threads used  : 8
    
    Hex Board after 3 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    .    .    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:78, playerA:2, playerB:1, other:0
    
    Computer (X) entered last move as: d4
    Running 780000 simulated trials
    ..............................................................................
    
    (O) picks e4
    Total Time taken                              :    1433 ms
    time_copy_hex_board_to_simulation             :       2 us  0.14%
    Multi-threaded time_shuffle_and_fill_up_board :      32 ms  2.23%
    Multi-threaded time_who_won_using_dfs_algo    :    1380 ms  96.30%
    Threads used  : 8
    
    Hex Board after 4 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    .    O    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:77, playerA:2, playerB:2, other:0
    
    Computer (O) entered last move as: e4
    Running 770000 simulated trials
    .............................................................................
    
    (X) picks e3
    Total Time taken                              :    2087 ms
    time_copy_hex_board_to_simulation             :       3 us  0.14%
    Multi-threaded time_shuffle_and_fill_up_board :      38 ms  1.82%
    Multi-threaded time_who_won_using_dfs_algo    :    2030 ms  97.27%
    Threads used  : 8
    
    Hex Board after 5 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    .    .    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:76, playerA:3, playerB:2, other:0
    
    Computer (X) entered last move as: e3
    Running 760000 simulated trials
    ............................................................................
    
    (O) picks f3
    Total Time taken                              :    1575 ms
    time_copy_hex_board_to_simulation             :       3 us  0.19%
    Multi-threaded time_shuffle_and_fill_up_board :      36 ms  2.29%
    Multi-threaded time_who_won_using_dfs_algo    :    1517 ms  96.32%
    Threads used  : 8
    
    Hex Board after 6 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    .    O    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:75, playerA:3, playerB:3, other:0
    
    Computer (O) entered last move as: f3
    Running 750000 simulated trials
    ...........................................................................
    
    (X) picks f2
    Total Time taken                              :    1974 ms
    time_copy_hex_board_to_simulation             :       3 us  0.15%
    Multi-threaded time_shuffle_and_fill_up_board :      33 ms  1.67%
    Multi-threaded time_who_won_using_dfs_algo    :    1919 ms  97.21%
    Threads used  : 8
    
    Hex Board after 7 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   .    .    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:74, playerA:4, playerB:3, other:0
    
    Computer (X) entered last move as: f2
    Running 740000 simulated trials
    ..........................................................................
    
    (O) picks g2
    Total Time taken                              :    1496 ms
    time_copy_hex_board_to_simulation             :       3 us  0.20%
    Multi-threaded time_shuffle_and_fill_up_board :      44 ms  2.94%
    Multi-threaded time_who_won_using_dfs_algo    :    1425 ms  95.25%
    Threads used  : 8
    
    Hex Board after 8 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   .    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:73, playerA:4, playerB:4, other:0
    
    Computer (O) entered last move as: g2
    Running 730000 simulated trials
    .........................................................................
    
    (X) picks g1
    Total Time taken                              :    1913 ms
    time_copy_hex_board_to_simulation             :       3 us  0.16%
    Multi-threaded time_shuffle_and_fill_up_board :      29 ms  1.52%
    Multi-threaded time_who_won_using_dfs_algo    :    1859 ms  97.18%
    Threads used  : 8
    
    Hex Board after 9 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   .    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:72, playerA:5, playerB:4, other:0
    
    Computer (X) entered last move as: g1
    Running 720000 simulated trials
    ........................................................................
    
    (O) picks h1
    Total Time taken                              :    1401 ms
    time_copy_hex_board_to_simulation             :       4 us  0.29%
    Multi-threaded time_shuffle_and_fill_up_board :      24 ms  1.71%
    Multi-threaded time_who_won_using_dfs_algo    :    1349 ms  96.29%
    Threads used  : 8
    
    Hex Board after 10 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    .    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:71, playerA:5, playerB:5, other:0
    
    Computer (O) entered last move as: h1
    Running 710000 simulated trials
    .......................................................................
    
    (X) picks e5
    Total Time taken                              :    1801 ms
    time_copy_hex_board_to_simulation             :       3 us  0.17%
    Multi-threaded time_shuffle_and_fill_up_board :      10 ms  0.56%
    Multi-threaded time_who_won_using_dfs_algo    :    1767 ms  98.11%
    Threads used  : 8
    
    Hex Board after 11 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    .    .    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:70, playerA:6, playerB:5, other:0
    
    Computer (X) entered last move as: e5
    Running 700000 simulated trials
    ......................................................................
    
    (O) picks d5
    Total Time taken                              :    1618 ms
    time_copy_hex_board_to_simulation             :       4 us  0.25%
    Multi-threaded time_shuffle_and_fill_up_board : 4294967289 ms  265449152.60%
    Multi-threaded time_who_won_using_dfs_algo    :    1613 ms  99.69%
    Threads used  : 8
    
    Hex Board after 12 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    .    O    .    .   \  c
    
                     d  \   .    .    .    X    O    .    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:69, playerA:6, playerB:6, other:0
    
    Computer (O) entered last move as: d5
    Running 690000 simulated trials
    .....................................................................
    
    (X) picks c6
    Total Time taken                              :    1598 ms
    time_copy_hex_board_to_simulation             :       5 us  0.31%
    Multi-threaded time_shuffle_and_fill_up_board :      14 ms  0.88%
    Multi-threaded time_who_won_using_dfs_algo    :    1560 ms  97.62%
    Threads used  : 8
    
    Hex Board after 13 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    X    O    .    .   \  c
    
                     d  \   .    .    .    X    O    .    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:68, playerA:7, playerB:6, other:0
    
    Computer (X) entered last move as: c6
    Running 680000 simulated trials
    ....................................................................
    
    (O) picks d6
    Total Time taken                              :    1547 ms
    time_copy_hex_board_to_simulation             :      12 us  0.78%
    Multi-threaded time_shuffle_and_fill_up_board : 4294967286 ms  277632015.90%
    Multi-threaded time_who_won_using_dfs_algo    :    1542 ms  99.68%
    Threads used  : 8
    
    Hex Board after 14 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    X    O    .    .   \  c
    
                     d  \   .    .    .    X    O    O    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:67, playerA:7, playerB:7, other:0
    
    Computer (O) entered last move as: d6
    Running 670000 simulated trials
    ...................................................................
    
    (X) picks c8
    Total Time taken                              :    1472 ms
    time_copy_hex_board_to_simulation             :       4 us  0.27%
    Multi-threaded time_shuffle_and_fill_up_board :      14 ms  0.95%
    Multi-threaded time_who_won_using_dfs_algo    :    1432 ms  97.28%
    Threads used  : 8
    
    Hex Board after 15 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    .    .   \  b
    
                  c  \   .    .    .    .    .    X    O    X    .   \  c
    
                     d  \   .    .    .    X    O    O    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:66, playerA:8, playerB:7, other:0
    
    Computer (X) entered last move as: c8
    Running 660000 simulated trials
    ..................................................................
    
    (O) picks b8
    Total Time taken                              :    1550 ms
    time_copy_hex_board_to_simulation             :       4 us  0.26%
    Multi-threaded time_shuffle_and_fill_up_board : 4294967278 ms  277094663.10%
    Multi-threaded time_who_won_using_dfs_algo    :    1552 ms  100.13%
    Threads used  : 8
    
    Hex Board after 16 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    O    .   \  b
    
                  c  \   .    .    .    .    .    X    O    X    .   \  c
    
                     d  \   .    .    .    X    O    O    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:65, playerA:8, playerB:8, other:0
    
    Computer (O) entered last move as: b8
    Running 650000 simulated trials
    .................................................................
    
    (X) picks b9
    Total Time taken                              :    1338 ms
    time_copy_hex_board_to_simulation             :       3 us  0.22%
    Multi-threaded time_shuffle_and_fill_up_board :      16 ms  1.20%
    Multi-threaded time_who_won_using_dfs_algo    :    1305 ms  97.53%
    Threads used  : 8
    
    Hex Board after 17 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    .   \  a
    
               b  \   .    .    .    .    .    .    .    O    X   \  b
    
                  c  \   .    .    .    .    .    X    O    X    .   \  c
    
                     d  \   .    .    .    X    O    O    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:64, playerA:9, playerB:8, other:0
    
    Computer (X) entered last move as: b9
    Running 640000 simulated trials
    ................................................................
    
    (O) picks a9
    Total Time taken                              :    1586 ms
    time_copy_hex_board_to_simulation             :       4 us  0.25%
    Multi-threaded time_shuffle_and_fill_up_board : 4294967280 ms  270804998.74%
    Multi-threaded time_who_won_using_dfs_algo    :    1587 ms  100.06%
    Threads used  : 8
    
    Hex Board after 18 moves:
    
                              Hex Game
    
                    X  |  top-to-bottom  | Computer
                    O  |  left-to-right  | Computer
    
    
                  1    2    3    4    5    6    7    8    9
                  --   --   --   --   --   --   --   --   --
            a  \   .    .    .    .    .    .    .    .    O   \  a
    
               b  \   .    .    .    .    .    .    .    O    X   \  b
    
                  c  \   .    .    .    .    .    X    O    X    .   \  c
    
                     d  \   .    .    .    X    O    O    .    .    .   \  d
    
                        e  \   .    .    X    O    X    .    .    .    .   \  e
    
                           f  \   .    X    O    .    .    .    .    .    .   \  f
    
                              g  \   X    O    .    .    .    .    .    .    .   \  g
    
                                 h  \   O    X    .    .    .    .    .    .    .   \  h
    
                                    i  \   .    .    .    .    .    .    .    .    .   \  i
                                           --   --   --   --   --   --   --   --   --
                                             1    2    3    4    5    6    7    8    9
    
    SQUARES OWNERSHIP empty:63, playerA:9, playerB:9, other:0
    
    
    Computer (O) Won!!!
    
    Game won in 18 moves!
    
    
    Calling destructors...
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~SimulationHexBoard()
    ~HexBoard() owner: SimulationHexBoard()
    ~GamePlayClass()
    ~HexBoard() owner: GamePlayClass()
    
    C:\Programming\3.C++forCProgrammers\Hex_Game\x64\Release\Hex_Game.exe (process 18004) exited with code 0.
    Press any key to close this window . . .

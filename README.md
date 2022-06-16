<h1>Hex Game</h1>

Author: Prashant Kumar
Date: June 16th 2022

<h2>Representation:</h2>
A size 5 hex board has 5x5 squares. Squares have 3 types – PlayerA, PlayerB or Empty. Every Square acts as a node for path algorithms. Nodes have sequential ids from 0 to n x n - 1. For path algorithm purpose, an imaginary start and end node is created. Start and end nodes have the same id for PlayerA and PlayerB. Start node is given id -2 and end node -3. Nodes from one side are connected to start node and other side to end node as shown in representation below.

![Screenshot](Representation.png)

<h2>Program Structure</h2>
•	Game Constants
o	Player A is X (top to bottom), Player B is O (left to right)
o	Player Types – Human/Computer
o	Board Size
•	Functions
o	Check game won by a player (using Dijkstra’s for now, A star later)
o	Randomly Fill up Whole Board
o	Take User Input Move
o	Print Hex Board
•	Game Play
o	Hex Board with Current Positions
o	Best_next_move() Trial function to try out all legal moves 1000 times and classify each move with win loss ratio – return move with best win loss ratio
	Vector of empty squares
	For every square 1000 trials of randomly filling up board, noting who won and adding it to PlayerA or PlayerB
	Returning best next move for PlayerA or PlayerB

<h2>Class Structure</h2>
1.	Square: char
a.	playerA = 'X',
b.	playerB = 'O',
c.	empty = '.',
2.	Node
a.	int id = kNullId;
b.	int nearest_node_id = kNullId;
c.	int distance = 1;    //distance to every node is 1 for hex game
d.	static const int kNullId = -1;    //Node ids will be whole numbers
e.	static const int graph_start_id = -2;    //an imaginary node id to start player's hex board graph from
f.	static const int graph_end_id = -3;    //an imaginary node id to end player's hex board graph to
3.	Game_Class
a.	playerA_type 0 – human /1 - computer
b.	playerB_type 0 – human /1 – computer
c.	playerA_name
d.	playerB_name
e.	board_size – 5 for testing, 11 for production
f.	hex_board – pointer to pointer of Square
g.	empty_squares_vector – all squares have an id, we maintain an empty ids list to pick from
h.	Functions:
i.	game_won (using Dijkstra’s for now, A star later), return -1 for none, 0 for PlayerA, 1 for PlayerB
ii.	fill_board_randomly(bool turn_of_player), return randomly filled up board
iii.	take_user_input(), return node_id
iv.	best_next_move(bool player), return node_id
v.	print_hex_board()
4.	enum class PlayerType
a.	Human = 0,
b.	Computer = 1,
5.	enum class Square : char
a.	PlayerA = 'X',
b.	PlayerB = 'O',
c.	Empty = '.',

<h2>Pseudo Code</h2>
1.	Load Game Constants
2.	RunGame
a.	If player == human
i.	Take user input
b.	Else player == computer
i.	For each entry of list of empty squares run a simulation 1000 times
1.	Fill all squares randomly
2.	Check who won the game
3.	Note win or loss for this simulation
4.	Assign the entry with win/loss ratio
ii.	Return the entry with best win/loss ratio
c.	Check if game is won, if yes then break else run the above for the other player

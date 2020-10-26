#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Windows.h>
using namespace std;

//This class is used to store player turn sequence
template <class T>
class Queue
{
	int Front;
	int Back;
	T* turns;
	int players;

public:

	//constructor
	Queue()
	{
		turns = NULL;
		players = 2;
		Front = Back = -1;
	}

	//return the element in front
	T front() {
		return turns[Front] ;
	}

	//return the element in back
	T back() {
		return turns[Back];
	}

	//check if queue is empty
	bool is_empty()
	{
		if (Front == back)
			return true;
	
		return false;
	}

	//set no of players
	void setPlayers(int n)
	{
		players = n;
		turns = new T[n];
	}

	//reverses the queue
	void reverse()
	{
		int i = Front;
		int j;

		cout << "\tPREVIOUS TURN SEQUENCE : ";
		for (int k = 0; k < players; k++)
		{
			cout << "P" << turns[i] << " ";
			i = (i+1) % players;
		}
		cout << endl;

		T* temp = new T[players];
		i = Front;
		j = Back;

		for ( int k = 0 ; k < players; k++ )
		{
			temp[i] = turns[j];
			i = (i + 1) % players;

			if ((j - 1) < 0)
				j = players - 1;

			else
				j--;
		}

		turns = temp;

		i = Front;
		cout << "\tNEW TURN SEQUENCE : ";
		for (int k = 0; k < players; k++)
		{
			cout << "P" << turns[i] << " ";
			i = (i + 1) % players;
		}
		cout << endl;
	}

	//used to remove front element from queue and decrease queue size
	void removefront()
	{
		T* temp = new T[players-1];
		
		int j = (Front + 1) % players;

		for (int k = 0; k < players-1 ;  k++)
		{
			temp[k] = turns[j];
			j = (j + 1) % players;
		}

		players--;
		
		turns = temp;
		Front = 0;
		Back = players - 1;

		cout << "\tNEW TURN SEQUENCE : ";
		for (int k = 0; k < players; k++)
			cout << "P" << turns[k] << " ";
		cout << endl;
	}

	//pushes element at back of queue
	void enqueue(T pos)
	{
		if (Front == -1)
		{
			Front = (Front + 1) % players;
			Back = (Back + 1) % players;
			turns[Front] = pos;
		}

		else
		{
			Back = (Back+1) % players;
			turns[Back] = pos;
		}
	}

	//removes element from front
	T dequeue()
	{
		T temp = turns[Front];
		Front = (Front + 1) % players;
		return temp;
	}

	//emptys the queue
	void empty()
	{
		delete[]turns;

		Front = -1;
		Back = -1;
	}

	//destructor
	~Queue()
	{
		if ( (Front != -1) && (Back != -1) )
			delete[]turns;
		Front = Back = -1;
	}
};

//used to store player position
struct Players
{
	int position;
};

//Used to create linked list of Stack
struct Node
{
	int data;
	Node* next;
};

//Implement a stack for your dice roll operations
class RollStack
{
	Node *Top;

public:

	RollStack()
	{
		Top = NULL;
	}

	//Add a roll on top of the stack
	void push_roll(int value)
	{
		if (Top == NULL)
		{
			Top = new Node;
			Top->next = NULL;
			Top->data = value;
		}
		
		else
		{
			Node* temp = new Node;
			temp->next = Top;
			temp->data = value;
			Top = temp;
		}
	}

	//return the value on top of stack
	int top() {
		return Top->data;
	}

	//pops the top of stack
	void pop() {
		Node* temp = new Node;
		temp = Top;
		Top = Top->next;
		delete temp;
	}

	//reverses the stack
	void reverse()
	{
		Node* Top2 = NULL;
		int value;

		while (!is_empty())
		{
			value = top();
			pop();

			if (Top2 == NULL)
			{
				Top2 = new Node;
				Top2->next = NULL;
				Top2->data = value;
			}

			else
			{
				Node* temp = new Node;
				temp->next = Top2;
				temp->data = value;
				Top2 = temp;
			}
		}

		Top = Top2;
	}

	//return true if stack is empty
	bool is_empty() {
		if(Top == NULL)
			return true;
		return false;
	}

	//emptys the stack
	void empty() {
		while (!is_empty()) {
			pop();
		}
	}

	//Deallocate the memory
	~RollStack()
	{
		empty();
		Top = NULL;
	}
};

//It represents the box position
struct Tile
{
	Tile* next, * previous, * up, * down;
	
	//Check to see if snake head is present or ladder tail is present
	bool snake;
	bool ladder;

	//Stores its own index
	int index;
};

//It contains Board Linked List
class Board
{
	Tile *Start;
	Tile *End;

	public:

	Board()
	{
		Start = NULL;
		End = NULL;
	}

	//initializes the board with tiles
	void Initialize()
	{
		Start = new Tile;
		Start->previous = NULL;

		Tile* curr = Start;
		Tile* prev = NULL;
		
		for (int i = 1; i <= 100; i++)
		{
			curr->index = i;
			curr->snake = false;
			curr->ladder = false;

			if ( (i % 10 == 0) && (i != 100) )
			{
				curr->next = NULL;
				curr->previous = prev;
				curr->down = NULL;
				curr->up = new Tile;

				prev = curr;
				curr = curr->up;
			}

			else if ( (i % 10) == 1 )
			{
				curr->next = new Tile;
				curr->up = NULL;
				curr->down = prev;
				curr->previous = NULL;

				prev = curr;
				curr = curr->next;
			}

			else
			{
				if (i != 1)
					curr->previous = prev;

				if (i != 100)
					curr->next = new Tile;

				curr->up = NULL;
				curr->down = NULL;

				prev = curr;

				if(i != 100)
					curr = curr->next;
			}
		}

		End = curr;
		End->next = NULL;
	}

	//sets ladders and snakes pos from file
	void setSnakesLadders(ifstream &INPUT)
	{
		//Creating Stack to Push Ladder and Snake Positions
		RollStack snakes;
		RollStack ladders;

		//Reading Positions from File
		string word;
		int line = 10;
		int count = 0;
		int pos = 100;
		bool reverse = false;
		bool nosnake = true;
		bool noladder = true;

		while (pos > 0)
		{
			//emptying word buffer
			word = '\0';

			//Fetch a word and increase word count
			INPUT >> word;
			count++;

			//Snake is present
			if (word[0] == 'S')
			{
				snakes.push_roll(pos);
				nosnake = false;
			}

			//Ladder is present
			if (word[0] == 'L')
			{
				ladders.push_roll(pos);
				noladder = false;
			}

			//counter to decrement line variable value
			if (count == 10)
			{
				count = 0;

				//there was no snake in this line so push -1 in stack which ensures differentiability of next snake sequence
				if (nosnake)
					snakes.push_roll(-1);

				//there was no ladder in this line so push -1 in stack which ensures differentiability of next ladder sequence
				if (noladder)
					ladders.push_roll(-1);

				nosnake = true;
				noladder = true;

				line--;
			}

			//if line is even i.e pos counting will be decreased
			if ((line % 2 == 0) && (reverse == true))
			{
				reverse = false;
				pos -= 10;
			}

			//line is odd, then switch reverse counter
			else if ((line % 2 != 0) && (reverse == false))
			{
				pos -= 10;
				reverse = true;
			}

			//if line is odd, then pos counting will be increased
			else if (reverse == true)
				pos++;
			else
				pos--;
		}

		Tile* curr;
		Tile* next;
		noladder = true;	//used to find ladder bottom
		
		//Setting Ladder Tiles at Finded Positions
		while (!ladders.is_empty())
		{
			pos = ladders.top();
			ladders.pop();

			//ignore stack case
			if (pos == -1)
			{
				noladder = true;
				continue;
			}

			line = ladders.top();
			ladders.pop();
		
			curr = getTile(pos);

			//ladderbottom is not found
			if (noladder == true)
			{
				curr->ladder = true;
				noladder = false;
			}

			//ladder top is not reached
			while ((line != -1) && (!ladders.is_empty()))
			{
				next = getTile(line);

				curr->up = next;
				curr = next;

				line = ladders.top();
				ladders.pop();
			}

			if (ladders.is_empty())
			{
				next = getTile(line);

				curr->up = next;
				curr = next;
			}
		}

		//reverse the snakes stack
		snakes.reverse();

		nosnake = true;	//used for snake head

		//Setting Snake Tiles at Finded Positions
		while (!snakes.is_empty())
		{
			pos = snakes.top();
			snakes.pop();

			//ignore stack case
			if (pos == -1)
			{
				nosnake = true;
				continue;
			}

			line = snakes.top();
			snakes.pop();

			curr = getTile(pos);

			//snaketop is not found
			if (nosnake == true)
			{
				curr->snake = true;
				nosnake = false;
			}

			//snake bottom is not reached
			while ( (line != -1) && (!snakes.is_empty()) )
			{
				next = getTile(line);

				curr->down = next;
				curr = next;

				line = snakes.top();
				snakes.pop();
			}

			if (snakes.is_empty())
			{
				next = getTile(line);

				curr->down = next;
				curr = next;
			}
		}
	}

	//Returns a Tile present at pos
	Tile* getTile(int pos)
	{
		Tile* temp = NULL;

		for (int i = 1; i <= pos; i++)
		{
			if (i == 1)
				temp = Start;

			else if ((i % 10) == 1)
				temp = temp->up;

			else
				temp = temp->next;
		}

		return temp;
	}

	//returns if ladder is at position
	bool isLadder(int pos)
		{
			Tile* temp = getTile(pos);
			return temp->ladder;
		}

	//returns if snake is at position
	bool isSnake(int pos)
		{
			Tile* temp = getTile(pos);
			return temp->snake;
		}

	//clears the board
	void clear()
		{
			if ((Start == NULL) && (End == NULL))
				return;

			Tile* curr = new Tile;

			for (int i = 1; i <= 100; i++)
			{
				curr = Start;

				if ((i % 10 == 0) && (i != 100))
					Start = Start->up;

				else
					Start = Start->next;

				delete curr;
			}

			Start = NULL;
			End = NULL;
		}

	//destructor
	~Board()
		{
			clear();
		}
};

//Main Class
class Game
{
	Queue<int> turnQueue;
	RollStack dicerolls;
	Board Ludo;

	Players* players;
	int numberofplayers;
	int currplayer;

public:

	//Initialize the game board from the given file and setup players
	Game(const std::string& filename, int num_players)
	{
		//random no seeder
		srand(time(0));

		//Initialize the no of players
		turnQueue.setPlayers(num_players);
	
		players = new Players[num_players];

		//setting their initial position to -1
		for (int i = 0; i < num_players; i++)
			players[i].position = -1;

		//setting no off players
		numberofplayers = num_players;

		//setting initial player no to 1
		currplayer = 0;

		//Give them starting turn sequence
		for (int i = 1; i <= num_players; i++)
			turnQueue.enqueue(i);
		
		//Creating ifstream obj for taking input
		ifstream input;
		input.open(filename);

		if (!input)
			EXIT_FAILURE;
			
		//Creating Game Board
		Ludo.Initialize();

		//Set Snakes and Ladders Positions
		Ludo.setSnakesLadders(input);
	
		//closes the file
		input.close();
	}

	/* Return your player turn queue */
	Queue<int>& GetTurnQueue()
	{
		return turnQueue;
	}

	/* returns the Tile at the given position (head, bottom left, is at pos 1) */
	Tile* GetTile(int pos)
	{
		return Ludo.getTile(pos);
	}

	/* returns true if there is a ladder tail at 'pos' */
	bool IsLadder(int pos)
	{
		return Ludo.isLadder(pos);
	}

	/* returns true if there is a snake head at 'pos' */
	bool IsSnake(int pos)
	{
		return Ludo.isSnake(pos);
	}

	/*Traverse the board and return the resulting position
	  beginning from 'current_pos' using the roll stack*/
	int TraverseBoard(int current_pos, RollStack& stack)
	{
		if (current_pos == -1)
			return -1;
	
		int total = current_pos;
		int temp2 = 0;
		Tile* temp = GetTile(total);

		while (!stack.is_empty())
		{
			temp2 = stack.top();

			if (total + temp2 > 100)
				return total;

			total += temp2;
			temp = GetTile(total);

			stack.pop();

			if (temp->ladder == true)
			{
				cout << "\tLADDER ENCOUNTERED AT " << temp->index << endl;

				while (temp->up != NULL)
					temp = temp->up;

				cout << "\tYOU HAVE MOVED UP THE LADDER" << endl;

				total = temp->index;
			}

			else if (temp->snake == true)
			{
				cout << "\tSNAKE ENCOUNTERED AT " << temp->index << endl;

				while (temp->down != NULL)
					temp = temp->down;

				cout  << "\tYOU HAVE MOVED DOWN THE SNAKE" << endl;

				total = temp->index;
			}
		}

		return total;
	}

	/* Add a roll for the current player, update turn queue accordingly */
	void RollDice(int value)
	{
		int temp;

		//player has rolled 1 or 6 and is entering the board
		if ( ( (value == 6) || (value == 1) ) && (players[currplayer].position == -1))
		{
			cout << "\tYOU HAVE ENTERED THE BOARD" << endl;

			players[currplayer].position = 1;
			temp = turnQueue.dequeue();
			turnQueue.enqueue(temp);
			currplayer = turnQueue.front() - 1;
		}

		//player has rolled sum which is divisble by 3 so queue will be reversed
		else if ( (value % 3 == 0) && (players[currplayer].position != -1) ) 
		{
			turnQueue.reverse();
			cout << "\tPLAYERS TURNS HAVE BEEN REVERSED" << endl;
			currplayer = turnQueue.front() - 1;
		}

		//player has not entered the board
		else if (players[currplayer].position == -1)
		{
			cout << "\tROLL 1 OR 6 TO ENTER THE BOARD" << endl;

			temp = turnQueue.dequeue();
			turnQueue.enqueue(temp);
			currplayer = turnQueue.front() - 1;
		}

		//player will play its turn
		else
		{
			temp = turnQueue.dequeue();
			turnQueue.enqueue(temp);
			currplayer = turnQueue.front() - 1;
		}
	}
	
	//Main Game Canvas Function
	void Play()
	{
		int dice = 0;
		int count = 0;
		int refresh = 0;
		int turn = currplayer;

		int totalplayers = numberofplayers;
		int temp = numberofplayers;	//for refresh function
		bool end = false;
		int pos = 1;

		int enter;
		cin.ignore();

		while (!end)
		{
			//clear screen after all players turns
			if (refresh >= temp)
			{
				cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl ;
				cout << endl << "\t\t\tPRESS ENTER TO PROCEED" << endl;
				enter = cin.get();
				refresh = 0;
				system("cls");
			}

			count = 0;
			refresh++;
			turn = currplayer;
			dicerolls.empty();

			cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << endl << "PLAYER " << turn + 1 << " : " << endl;
			cout << "\tPRESS ENTER TO ROLL THE DICE" << endl;
			enter = cin.get();
			cout << "\tPREVIOUS POSITION : ";
			
			if (players[turn].position == -1)
				cout << "NOT ENTERED THE BOARD" << endl;
			else
				cout << players[turn].position << endl;

			cout << "\tDICE ROLL : ";

			//rolling dice
			do
			{
				dice = (rand() % 6) + 1;
				dicerolls.push_roll(dice);

				cout << dice << " ";

				if(dice == 6)
					count++;

			} while ( (players[turn].position != -1) && (dice == 6) );
			
			cout << endl;

			//player has won
			if ( ( (players[turn].position + dice) == 100) && (count == 0) )
			{
				//removing player from turnqueue
				if(totalplayers != 2)
					turnQueue.removefront();

				//changing current player
				currplayer = turnQueue.front() - 1;

				temp--;

				cout << endl << "\t\t\tPLAYER " << turn + 1 << " HAS WON THE GAME WITH POSITION " << pos << endl;
				pos++;

				if (totalplayers == 2)
					end = true;

				else if ((totalplayers == 3) && (pos > 2))
					end = true;

				else if ((totalplayers > 3) && (pos > 3))
					end = true;

				cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
				cout << endl << "\t\t\tPRESS ENTER TO PROCEED" << endl;
				enter = cin.get();
				refresh = 0;
				system("cls");
			}

			//three consecutive sixes, player loses its turn
			else if (count == 3)
			{
				cout << "\tYOU HAVE LOST TOUR TURN DUE TO 3 CONSECUTIVE SIXES" << endl;

				RollDice(dice);
				continue;
			}

			//four consecutive sixes next player loses turn
			else if (count == 4)
			{
				players[turn].position = TraverseBoard(players[turn].position, dicerolls);
				RollDice(dice);
				RollDice(dice);
				
				cout << "\tNEW POSITION : ";

				if (players[turn].position == -1)
					cout << "NOT ENTERED THE BOARD" << endl;
				else
					cout << players[turn].position << endl;

				cout << "\tNEXT PLAYER HAS LOST ITS TURN DUE TO 4 CONSECUTIVE SIXES" << endl;
				
				continue;
			}

			//player has rolled normal dice
			else
			{
				players[turn].position = TraverseBoard(players[turn].position, dicerolls);
				RollDice(dice);
				cout << "\tNEW POSITION : ";
				
				if (players[turn].position == -1)
					cout << "NOT ENTERED THE BOARD" << endl;
				else
					cout << players[turn].position << endl;
			
				if ( (dice == 3) && (players[turn].position != -1) )
				{
					cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
					cout << endl << "\t\t\tPRESS ENTER TO PROCEED" << endl;
					enter = cin.get();
					refresh = 0;
					system("cls");
				}
			}
		}
	}

	//deallocates the memory
	~Game()
	{
		dicerolls.empty();
		Ludo.clear();
		turnQueue.empty();
		delete[] players;
	}
};
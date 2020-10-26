#include<iostream>
#include"../SNAKEANDLADDER/SnakesAndLadders.h"
using namespace std;

int main()
{
	int players;

	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "!!!!!!!!!!!!!WELCOME TO SNAKES AND LADDERS GAME!!!!!!!!!!" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "!!!!!!!!!HOW MANY PLAYERS ARE GOING TO PLAY >= 2!!!!!!!!!" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cin >> players;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	
	if (players < 2)
	{
		cout << "!!!!!!!!!!!!!!!SORRY YOU CANT PLAY ALONE!!!!!!!!!!!!!!!!!" << endl;
		return 0;
	}

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!LETS START!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "!!!!!!!!!YOU ARE ADVISED TO FULLSCREEN THE WINDOW!!!!!!!!" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;

	Sleep(1500);
	system("cls");

	Game game("map.txt", players);

	game.Play();

	system("cls");
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "!!!!!!!!!THANKS FOR PLAYING SNAKES AND LADDERS!!!!!!!!!!!" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << endl;

	return 0;
}
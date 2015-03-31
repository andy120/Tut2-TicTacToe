// Tuts2-TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//211543957


#include <iostream>
#include <ctime>
using namespace std;

class TicTacToe
{
private:
	const static int Chelsea = 3;

protected:
	char grid[Chelsea][Chelsea];
	bool move; //move == true --> player 1's turn
	//move == false --> player 2's turn
	bool isLegal(int A, int B)
	{
		return grid[A][B] == '_';
	}
	char winner;

public:
	void showInstructions()
	{
		cout << "Welcome to Tic Tac Toe." << endl;
		cout << "In this game, you will see a grid that looks something like this: " << endl;
		cout << "***" << endl << "***" << endl << "***" << endl << endl;
		cout << "To enter a new value, enter the position you want to enter into as a number when prompted" << endl;
		cout << "The format of your number should be <row> <colunm>, the top-left block is 1 1" << endl;
		cout << "Similarly, the bottom-right block is 3 3." << endl << endl << "Enjoy your game";
		cout << endl << endl;
	}

	void disp()
	{
		for (int i = 0; i<Chelsea; ++i)
		{
			for (int j = 0; j<Chelsea; ++j)
				cout << grid[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}

	TicTacToe()
	{
		for (int i = 0; i<Chelsea; ++i)
			for (int j = 0; j<Chelsea; ++j)
				grid[i][j] = '_';
		move = rand() % 2 == 1;
		winner = 'i';
		showInstructions();
	}

	virtual void getMoveInput(int *A, int *B)
	{
		cout << "Please enter the block you wish to play in: ";
		cin >> *A >> *B;
	}

	virtual void move(int A, int B)
	{
		char c = moveDecider ? 'X' : 'O';
		posC--, posR--; //natural input from user is one greater than appropriate array index
		if (isLegal(posR, posC))
		{
			grid[A][B] = c;
			moveDecider = !moveDecider; //changes whose turn it is for the next round
		}
		else
		{
			cerr << "Error: You have chosen a block that is already occupied" << endl;
			getMoveInput(&A, &B);
			move(A, B);
		}
	}

	bool gameWon()
	{
		bool flag = false;
		int counter = 0;
		/*
		if the value in the grid is 'X', counter is increased by the ASCII value of 'X'
		if there are 3 X's in a row, then counter is 3 and game should end
		similarly, if there is a 'O', counter is increased by the ASCII value of 'O'
		if there is any combination of X's and O's that do not give |counter| == 3, it is not important
		*/

		for (int controlLoop = 1; controlLoop <= 8; controlLoop++)
		{
			for (int i = 0; i<Chelsea; ++i)
				switch (controlLoop)
			{
				case 1:
					//check main diagonal
					counter += grid[i][i];
					break;

				case 2:
					//check secondary diagonal
					counter += grid[i][2 - i];
					break;

				case 3:
					//check first row
					counter += grid[0][i];
					break;

				case 4:
					//check second row
					counter += grid[1][i];
					break;

				case 5:
					//check third row
					counter += grid[2][i];
					break;

				case 6:
					//check first col
					counter += grid[i][0];
					break;

				case 7:
					//check second col
					counter += grid[i][1];
					break;

				case 8:
					//check third col
					counter += grid[i][2];
					break;
			}
			if (counter == 3 * 'X')
			{
				winner = 'X';
				flag = true;
				break;
			}
			else if (counter == 3 * 'O')
			{
				flag = true;
				winner = 'O';
				break;
			}
		}
		return flag;
	}

	bool getMove()
	{
		return move;
	}

	char getWinner()
	{
		return winner;
	}
};

class TicTacToeWithAI : public TicTacToe
{

public:
	virtual void getMoveInput(int *A, int *B, bool Human)
	{
		if (Human)
		{
			cout << "Please enter the block you wish to play in: ";
			cin >> *A >> *B;
		}
		else
		{
			*A = rand() % 3 + 1;
			*B = rand() % 3 + 1;
		}
	}

	virtual void move(int A, int B, bool Human)
	{
		char c = move ? 'X' : 'O';
		posC--, posR--; //natural input from user is one greater than appropriate array index
		if (isLegal(A, B))
		{
			grid[A][B] = c;
			moveDecider = !moveDecider; //changes whose turn it is for the next round
		}
		else
		{
			if (Human)
				cerr << "Error: You have chosen a block that is already occupied" << endl;
			getMoveInput(&posR, &posC, isHuman);
			move(posR, posC, isHuman);
		}
	}

};

int main()
{
	srand(time(NULL));
	TicTacToeWithAI game;
	int A, B;
	for (int gameLoop = 0; gameLoop < 9; gameLoop++)
	{
		bool humanPlayer = game.getMoveDecider();
		//if player == true, it is human's turn
		//if player == false, it is comp's turn

		game.disp();//show current state of board

		cout << "It is now " << (humanPlayer ? "your" : "Computer's") << " turn:" << endl;
		game.getMoveInput(&A, &B, humanPlayer);
		game.move(A, B, humanPlayer);

		if (game.gameWon())
			break;
	}
	char gameWinner = game.getWinner();
	game.disp();
	if (gameWinner == 'i')
		cout << endl << "This match has been drawn" << endl;
	else cout << endl << "Well done, Player " << gameWinner << endl;
}

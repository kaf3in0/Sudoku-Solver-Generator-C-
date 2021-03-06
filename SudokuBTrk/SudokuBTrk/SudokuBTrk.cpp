 //SudokuBTrk.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "Color.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>

using namespace std;

struct number
{
	int value = 0;
	bool fixed = false;  // Fixed means it can not change this value
};
number board[9][9];
Color color;


void printFile()
{
	ofstream out("Sudoku_solved");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			out << " " << board[i][j].value << " ";
			if (j % 3 == 2)
				out << "|";
		}
		out << endl;
		if (i % 3 == 2)
			out << "------------------------------\n";
	}
}
void printConsole()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			color.white();
			if (board[i][j].fixed)
				color.lightRed();
			cout << board[i][j].value << " ";

			if (j % 3 == 2)
				cout << " ";
		}
		cout << endl;
		if (i % 3 == 2)
			cout << endl;
	}
}
// We know we solved the puzzle when it goes out of scope
bool isSolution(int posX, int posY) { return posX < 9 && posY < 9; }
//bool isBorder(int posX, int posY) { return posY == 8; }
bool isValid(int posX, int posY, int value) 
{
	int nposX = posX - posX % 3;
	int nposY = posY - posY	 % 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			if (board[i + nposX][j + nposY].value == value) return false;

	}
	for (int i = 0; i < 9; i++)
	{
		// Check Col and Row
		if (board[i][posY].value == value || board[posX][i].value == value) return false;

	}
	return true;
}
bool solve(int row, int col)
{
	if (isSolution(row, col))
	{

		if (board[row][col].fixed)
		{
			if ((col + 1) < 9) return solve(row, col + 1);
			else if ((row + 1) < 9) return solve(row + 1, 0);
			else return true; // The board is full => solution
		}
		else if (!board[row][col].fixed)
		{
			for (int i = 1; i <= 9; i++)
			{
				if (isValid(row, col, i))
				{
					board[row][col].value = i;
					if ((col + 1)<9)
					{
						if (solve(row, col + 1))
							return true;
						else
							board[row][col].value = 0;
					}
					else if ((row + 1) < 9)
					{
						if (solve(row + 1, 0))
							return true;
						else
							board[row][col].value = 0;
					}
					
					else return true;
				}
			}

		}

		return false;
	}
	else return true;
}
void generatePuzzle()
{
	mt19937 RandomGenerator(time(NULL));
	uniform_int_distribution<int> genPosition(0, 8);
	uniform_int_distribution<int> genNum(1, 9);

	int fixedRemaining = 17; // A valid sudoku needs at least 16 numbers to begin with
	while (fixedRemaining)
	{
		int posX = genPosition(RandomGenerator);
		int posY = genPosition(RandomGenerator);
		int value = genNum(RandomGenerator);


		if (board[posX][posY].value == 0 &&
			isValid(posX, posY, value))
		{
			board[posX][posY].value = value;
			board[posX][posY].fixed = true;
		}
		else
		{
			// If the position is already filled try new positions
			continue;
		}
		fixedRemaining--;
	}
}
void verifyInput()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int value = board[i][j].value;
			board[i][j].value = 0;
			if ((!isValid(i, j, value) && value != 0))
			{
				cout << "ERROR ON LINE: " << i + 1 << endl;
				cout << "ERROR ON COL: " << j + 1 << endl;
				cout << "VALUE: " << value << endl;
				system("PAUSE");
			}
			else board[i][j].value = value;

			if (board[i][j].value > 0)
			{
				board[i][j].fixed = true;
			}

		}
	}
}
void inputPuzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> board[i][j].value;
		}
	}
	verifyInput();
}

int main()
{
	int input;
	cout << "WHAT WOULD YOU LIKE TO DO ?\n1.Generate random puzzle\n2.Input your own sudoku to resolve\n";
	while (cin >> input)
	{
		if (input < 0 || input > 3)
		{
			cout << "INVALID CHOICE";
			continue;
		}
		else if (input == 1)
		{
			generatePuzzle();
			break;
		}
		else if (input == 2)
		{
			inputPuzzle();
			break;
		}
	}
	printConsole();
	
	if (solve(0, 0))
	{
		printConsole();
		printFile();
		
	}
	system("PAUSE");
    return 0;
}

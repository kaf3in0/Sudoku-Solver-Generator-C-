#pragma once
//This will not work if you are not running windows
#include <Windows.h>
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Color
{
public:
	//Constructor
	Color();

	void blue() { SetConsoleTextAttribute(hConsole, 1); }
	void green() { SetConsoleTextAttribute(hConsole, 2); }
	void aqua() { SetConsoleTextAttribute(hConsole, 3); }
	void red() { SetConsoleTextAttribute(hConsole, 4); }
	void purpule() { SetConsoleTextAttribute(hConsole, 5); }
	void yellow() { SetConsoleTextAttribute(hConsole, 6); }
	void white() { SetConsoleTextAttribute(hConsole, 7); }
	void grey() { SetConsoleTextAttribute(hConsole, 8); }
	void lightBlue() { SetConsoleTextAttribute(hConsole, 9); }
	void lightGreen() { SetConsoleTextAttribute(hConsole, 10); }
	void lightAqua() { SetConsoleTextAttribute(hConsole, 11); }
	void lightRed() { SetConsoleTextAttribute(hConsole, 12); }
	void lightPurpule() { SetConsoleTextAttribute(hConsole, 13); }
	void lightYellow() { SetConsoleTextAttribute(hConsole, 14); }
	void lightWhite() { SetConsoleTextAttribute(hConsole, 15); }
};




#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <string>
#include "utils.h"
#include "consts.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

bool isANumber(std::string num)
{
	for (char const& c : num) 
	{
		if (std::isdigit(c) == 0) 
			return false;
	}
	return true;
}

void clrscr()
{
	system("cls");
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool isDigit(int num)
{
	if (num >= 0 && num < 10)
		return true;
	return false;
}

void cleanBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int setMode(int argc, char* argv[])
{
	if (argc < 2 || argc > 3)
	{
		printError();
	}
	if (!strcmp(argv[1], "-save"))
	{
		return SAVE;
	}
	else if (!strcmp(argv[1], "-load"))
	{
		if (argc > 2)
		{
			if (!strcmp(argv[2], "[-silent]"))
			{
				return SILENT;
			}
			printError();
		}
		return LOAD;
	}
	else
	{
		printError();
	}
}

void printError()
{
	system("cls");
	std::cout << "invalid input!";
	exit(1);
}


std::string getName(int entity, int stageNum)
{
	std::string fileName;
	switch (entity)
	{
	case PACMAN:
		fileName = "pacmanMove";
		break;
	case FRUIT:
		fileName = "fruitMove";
		break;
	case FRUIT_DATA:
		fileName = "fruitData";
		break;
	case GHOST1:
		fileName = "ghostMove1";
		break;
	case GHOST2:
		fileName = "ghostMove2";
		break;
	case GHOST3:
		fileName = "ghostMove3";
		break;
	case GHOST4:
		fileName = "ghostMove4";
		break;
	}
	fileName.append("_");
	fileName.append(std::to_string(stageNum));
	fileName.append(".txt");
	return fileName;
}

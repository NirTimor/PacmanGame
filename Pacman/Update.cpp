#include <iostream>
#include <Windows.h>
#include "Update.h"
#include "Point.h"
#include "utils.h"

void Update::printDiffXY(Update& newPos, Board& board, bool color, bool alive, int ghostSize)
{
	if (!pacPoint.cmpPoint(newPos.pacPoint))
	{
		gotoxy(pacPoint.x, pacPoint.y);
		std::cout << ' ';
	}
	if (color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	}
	gotoxy(newPos.pacPoint.x, newPos.pacPoint.y);
	std::cout << '@';
	if ((!fruit.cmpPoint(newPos.fruit)) && (!fruit.cmpPoint({ 0,0 })))
	{
		gotoxy(fruit.x, fruit.y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << board.whatInBoardXY(fruit.x, fruit.y);
	}
	if (!alive)
	{
		gotoxy(fruit.x, fruit.y);
		if (color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
	}
	else
	{
		if(color)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	gotoxy(newPos.fruit.x, newPos.fruit.y);
	if (alive)
	{
		std::cout << (int)newPos.fruitFig;
	}
	else
	{
		std::cout << WALL;
	}

	for (int i = 0; i < ghostSize; i++)
	{
		if (!ghostPoint[i].cmpPoint(newPos.ghostPoint[i]))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			gotoxy(ghostPoint[i].x, ghostPoint[i].y);
			std::cout << board.whatInBoardXY(ghostPoint[i].x, ghostPoint[i].y);
		}
		if (color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 3);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		gotoxy(newPos.ghostPoint[i].x, newPos.ghostPoint[i].y);
		std::cout << '$';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void Update::printScore(Point legend)
{
	gotoxy(legend.y, legend.x);
	std::cout << "Score: " << score;
}

void Update::printLives(Point legend)
{
	gotoxy(legend.y+11, legend.x);
	std::cout << "Lives: " << lives;
}

void Update::setGhostsPoint(std::vector<Ghost> newGhost, int i)
{
	for (int j = 0; j < i; j++)
	{
		ghostPoint[j] = newGhost[j].getXY();
	}
}

void Update::printFirstXY(Board& board, bool isColored, int ghostSize)
{
	if (isColored)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	}
	gotoxy(pacPoint.x, pacPoint.y);
	std::cout << '@';
	if (isColored)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	gotoxy(fruit.x, fruit.y);
	std::cout << (int)fruitFig;

	for (int i = 0; i < ghostSize; i++)
	{
		gotoxy(ghostPoint[i].x, ghostPoint[i].y);
		if (isColored)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 3);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		gotoxy(ghostPoint[i].x, ghostPoint[i].y);
		std::cout << '$';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
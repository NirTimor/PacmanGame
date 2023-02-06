#include "Fruit.h"
#include <fstream>
#include <string>

void Fruit::initFruit(unsigned char Board[MAX_ROWS][MAX_COLS], int rows, int cols, int numStage)
{
	do
	{
		cord.x = rand() % rows;
		cord.y = rand() % cols;
	} while ((Board[cord.y][cord.x] != FOOD ) && (Board[cord.y][cord.x] != ' '));
	
	figure = 5 + (rand() % 5);
	dir = rand() % 4;
	state = true;
	std::string fileName("fruitData_");
	fileName.append(std::to_string(numStage));
	fileName.append(".txt");

	std::ofstream fruitData(fileName, std::ofstream::app);
	
	fruitData << figure << " " << cord.x << " " << cord.y << " ";
}

void Fruit::initLoadedFruit(int rows, int cols, int dir, int fig, bool isAlive)
{
	cord.x = rows;
	cord.y = cols;
	figure = fig;
	dir = dir;
	state = isAlive;
}


void Fruit::setFruitDir(unsigned char Board[MAX_ROWS][MAX_COLS])
{
	Point temp = getFruitXY();
	do
	{
		cord = temp;
		dir = rand() % 4;
		setNextXY();
	} while ((Board[cord.y][cord.x] != FOOD) && (Board[cord.y][cord.x] != ' '));
}
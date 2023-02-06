#pragma once
#include <stdlib.h>
#include "consts.h"
#include "GameObject.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class Fruit : public GameObject
{
	int figure;
	bool state;
public:
	Fruit()
	{
		cord = { PACX,PACY };
		dir = STOP;
	};
	Point getFruitXY() { return getXY(); }
	bool getState() const { return state; }
	void initFruit(unsigned char Board[MAX_ROWS][MAX_COLS], int rows, int cols, int numStage);
	int getFigure() { return figure; }
	void setNewXY(Point newPos) { cord.x = newPos.x; cord.y = newPos.y; }
	void setFruitDir(unsigned char Board[MAX_ROWS][MAX_COLS]);
	void setFig() { figure = WALL; }
	void setLoadedFig(int fig) { figure = fig; }
	void setState(bool newState) { state = newState; }
	bool isOutOfBoundaries(Point fruit, int rows, int cols);
	void initLoadedFruit(int rows, int cols, int dir, int fig, bool isAlive);
	void setLoadedFruitDir();
};


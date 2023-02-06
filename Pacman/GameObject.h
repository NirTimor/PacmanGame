#pragma once
#include <string>
#include "consts.h"
#include "Point.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class GameObject
{
protected:
	Point cord;
	int dir;
public:
	Point getXY() { Point curr; curr.x = cord.x; curr.y = cord.y; return curr; } //gets pacman cordinates
	int getDir() { return dir; }
	Point setNextXY(); // sets object next cordinates
	void setNewDir(int newDir) { dir = newDir; }
	void setXY(Point pos);
	std::string getDirString();
};
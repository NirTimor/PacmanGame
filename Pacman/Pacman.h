#pragma once
#include "Point.h"
#include "consts.h"
#include "GameObject.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class Pacman : public GameObject
{
	int score = SCORE;
public:
	Pacman() 
	{
		cord = { PACX,PACY };
		dir = STOP;
	};

	Point getXY() const{ Point curr; curr.x = cord.x; curr.y = cord.y; return curr; } //gets pacman cordinates
	int getDir() const{ return dir; } //gets pacman direction
	void eat(int num) { score+=num; } // adjust score if pacman ate a breadcrumb
	void setDir(int newDir) { dir = newDir; }; // sets new direction using newDir
	void setPac() { cord = { PACX,PACY }; dir = INVALID; } //sets pacman original cordinates
	int getScore() const{ return score; } // gets pacman score
	void setNorth() { cord.x = NORTHX, cord.y = NORTHY; } //sets pacman after entering the south tunnel
	void setSouth() { cord.x = SOUTHX, cord.y = SOUTHY; } //sets pacman after entering the north tunnel
	void setWest() { cord.x = WESTX, cord.y = WESTY; } //sets pacman after entering the east tunnel
	void setEast() { cord.x = EASTX, cord.y = EASTY; } //sets pacman after entering the west tunnel
	int getPacDir() const{ return dir; }
	Pacman getPacman() { return *this; }
};
#pragma once
#include "Board.h"
#include "Point.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Game.h"
#include "consts.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class Update
{
	Point pacPoint = { 0,0 };
	Point ghostPoint[GHOSTS] = { {0,0} ,{0,0} ,{0,0} ,{0,0} };
	Point fruit;
	char fruitFig;
	int score;
	int lives;

public:
	void printDiffXY(Update& newPos, Board& board,bool color, bool alive, int ghostSize); //prints the new cordiantes and erases the old ones 
	void setPacPoint(Point newPac) { pacPoint = newPac; } //set pacman cordinates
	void setGhostsPoint(std::vector<Ghost> ghosts, int i); //set ghosts cordinates, i is the iterator
	void printScore(Point legend); //prints the score
	void setPacScore(int newScore) { score = newScore; } //sets pacman score
	Point getPacPoint() const{ return pacPoint; } //gets pacman cordinate 
	Point getGhostPoint(int i) const{ return ghostPoint[i]; } // get ghosts cordinates, i is the iterator
	void printLives(Point legend); //prints lives
	void updateCurrLives() { lives--; } //updates current lives
	void setFruitPoint(Point newFruit) { fruit = newFruit; }
	void setFruitFig(char fig) { fruitFig = fig; }
	void printFirstXY(Board& board, bool isColored,int ghostSize);
	Update() :
		lives(3),score(DEFAULT){};
};
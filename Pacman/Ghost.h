#pragma once
#include <iostream>
#include "Point.h"
#include "consts.h"
#include "utils.h"
#include "GameObject.h"
#include "Game.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class Ghost : public GameObject
{
	bool ghostMove = true;
	int ghostPotDir[4] = { 0,0,0,0 };
public:
	//Point getGhostXY() const{ return gCord; } //gets ghost cordinates
	int getDir() const{ return dir; } //gets ghost current direction
	//void setGhostXY(); // sets ghost to original cordinates
	void getNewGDir(int ghost,Point pacLocation); //gets the new dir
	void setNewGDir(int ghost, Point pacLocation) { getNewGDir(ghost, pacLocation); } //sets the new direction
	void setGhostPotArr(int dir, bool b) { ghostPotDir[dir] = b; } //sets the ghostPotDir array using dir as the index and b as the boolean
	void updateMoveState() { ghostMove ? ghostMove = false : ghostMove = true; } //switches ghostMove from false to true and vice versa
	bool getMoveState() const{ return ghostMove; } //returns the current ghostMove
	void setGhost() { cord = { GHOSTX,GHOSTY }, ghostMove = true, dir = UP; } //sets the ghost to its original state
	void keepForward(unsigned char board[MAX_ROWS][MAX_COLS]);
	bool twoOrMoreDir();
	void cancelBackwards();
	const bool isValidDir(int dir) const { return ghostPotDir[dir]; }
	void setStupidGhostDir(int newDir) { dir = newDir; }
	int initGDirArr(unsigned char board[MAX_ROWS][MAX_COLS], int tmpDir);
	void writeNewDirToFile(int i, int dir,int numStage);
};


#pragma once
#include "Ghost.h"
#include "Pacman.h"
#include "consts.h"
#include "GameObject.h"
#include "Fruit.h"
#include <vector>
#include "Tunnel.h"
class Fruit;
class Pacman;
class Board;
class Game;
class Update;
class GameObjects;
class Board
{
	unsigned char pacmanBoard[MAX_ROWS][MAX_COLS];
	int logicCols = DEFAULT;
	int logicRows = DEFAULT;
	Pacman pacman;
	Point legend;
	std::vector <Ghost> ghost;
	int ghostCount = DEFAULT;
	Fruit fruit;
	int timer = INVALID;
	std::vector <Tunnel> tunnels;
public:
	void printBoard(bool isColored); //prints the board
	bool isValidMove(); //returns true if pacman next move is valid
	int updatePac(int& victory); //update pacman cordinates,calls a function to check if theres breadcrumbs on the new cordinates and returns his score
	void updateDir(int dir) { pacman.setDir(dir); } //updates pacman direction with dir
	void updateGDir(int i, Point pacLocation);// { ghost[i].setNewGDir(i, pacLocation); } //updates ghost direction, i is the iterator
	void setGhostDirArr(int i, bool stupid); //sets the ghostdirarr based on open paths around the ghost, i is the iterator
	void updateGhost(int i);// {ghost[i].GameObject::setNextXY(); }//sets ghost cordinates, i is the iterator
	unsigned char whatInBoardXY(int x, int y)const { return pacmanBoard[y][x]; } //checks whats inside board[x][y]
	std::vector<Ghost> getGhostArr();// { return ghost; } //returns a pointer to ghost array
	const Point getPacXY() const{return pacman.getXY(); } //gets pacman current cordinates
	void updateGhostMove(int i);// { ghost[i].updateMoveState(); } //updates the ghostmove from true to false and vice versa, i is the the iterator
	bool getGhostMoveState(int i)const; //{ return ghost[i].getMoveState(); } //returns the ghost move state, i is the iterator
	void reset(int mode); //resets the board after death
	void setPac(); //sets pac in his original position
	void setGhost(int i); //sets ghosts in their original position, i is the iterator
	const int getPacScore() const{ return pacman.getScore(); } //gets pacman score
	bool tunnelCheck(int& victory); //checks if next move is a tunnel and returns true if it is
	void adjustPac(Tunnel tun); //adjust pacman incase he has walked into a tunnel
	int getPacmanDir() const{ return pacman.getDir(); }
	void evaluateNewDir(int i);// { ghost[i].keepForward(pacmanBoard); }
	bool isNextMoveAWall(int i);
	bool isNextMoveATunnel(int i);
	void goBackwards(int i);
	int getTimer() const { return timer; }
	void setTimer(int newTime);
	bool getFruitState() const { return fruit.getState(); }
	void setFruitFig() { fruit.setFig(); }
	void setLoadedFruitFig(int fig) { fruit.setLoadedFig(fig); }
	void setFruitXY() { fruit.setNewXY({ 0,0 }); }
	void changeFruitDir() { fruit.setFruitDir(pacmanBoard); }
	void setNewFruit(int numStage) { fruit.initFruit(pacmanBoard, logicRows, logicCols, numStage); }
	Point getFruitXY() { return fruit.getFruitXY(); }
	int getFruitFig() { return fruit.getFigure(); }
	void setFruitState(bool newState) { fruit.setState(newState); }
	Point getGhostXY(int i);// { return ghost[i].getXY(); }
	void randomizeGhostsMove();
	void readNewBoard(std::string file, int& pointsToWin);
	int findMaxRow(unsigned char board[MAX_ROWS][MAX_COLS]);
	int findMaxCol(unsigned char board[MAX_ROWS][MAX_COLS]);
	const Point getLegend() const { return legend; }
	void setLegend(int x, int y) { legend.x = x, legend.y = y; }
	void setLogicRow(int rows) { logicRows = rows; }
	void setLogicCols(int cols) { logicCols = cols; }
	void createTunnelVector();
	int isOutOfBoard(Point nextMove);
	void fixLocation(int side);
	int getGhostSize();// { return ghost.size(); }
	void resetBoard(std::string file, int mode);
	bool isJunction(int i);// { return ghost[i].twoOrMoreDir(); }
	void initPacBoard();
	void restart();
	bool isTunnel(int i, int j);
	bool passTunnel(int dir, Tunnel& t);
	void setNewLoadedFruit(std::vector<int>const(&fruitInfo)[MAX_ENTITIES], int i, int currFruit);
	void setFruitDir(int newDir) { fruit.GameObject::setNewDir(newDir); }
	void setLoadedFruitXY(int x, int y) { fruit.GameObject::setXY({ x,y }); }
	void setFruitNextMove();
	bool isNextMoveAWall();
	bool isNextMoveATunnel();
	int getLogicRows() { return logicRows; }
	int getLogicCols() { return logicCols; }
	void setGhostDir(int i, int newDir);// { ghost[i].setStupidGhostDir(newDir); }
	Pacman& getPac() { return pacman; }
	Fruit& getFruit() { return fruit; }
};
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "utils.h"
#include "Board.h"
#include "Pacman.h"
#include <string>
#include <fstream>
using std::cout;
void Board::readNewBoard(std::string file, int& pointsToWin)
{
	int i, j;
	char curr, prev;
	std::ifstream f;
	f.open(file);
	i = j = 0;
	curr = prev = NULL;
	bool isPacAlive, isLegend;
	isPacAlive = isLegend = false;
	while (f.get(curr))
	{
		switch (curr)
		{
			case '@':
			{
				if (isPacAlive)
				{
					printError();
				}
				pacman.GameObject::setXY({ j,i });
				pacmanBoard[i][j] = ' ';
				isPacAlive = true;
				break;
			}
			case '$':
			{
				if (ghostCount >= GHOSTS)
				{
					break;
				}
				Ghost newGhost;
				newGhost.GameObject::setXY({ j,i });
				pacmanBoard[i][j] = ' ';
				ghost.push_back(newGhost);
				ghostCount++;
				break;
			}
			case '#':
			{
				pacmanBoard[i][j] = WALL;
				break;
			}
			case '%':
			{
				pacmanBoard[i][j] = ' ';
				break;
			}
			case '&':
			{
				if (isLegend)
				{
					printError();
				}
				setLegend(i, j);
				isLegend = true;
				break;
			}
			case ' ':
			{
				pacmanBoard[i][j] = FOOD;
				pointsToWin++;
				break;
			}
			case '\n':
			{
				if (logicCols == 0)
				{
					setLogicCols(j);
				}
				i++;
				j = -1;
				break;
			}
			default:
			{
				pacmanBoard[i][j] = ' ';
				break;
			}
		}
		j++;
	}
	setLogicRow(i);
	createTunnelVector();
}

void Board::resetBoard(std::string file, int mode)
{
	reset(mode);
	int i, j;
	char curr, prev;
	std::ifstream f;
	f.open(file);
	i = j = 0;
	curr = prev = NULL;
	while (f.get(curr))
	{
		switch (curr)
		{
			case '@':
			{
				pacman.GameObject::setXY({ j,i });
				pacmanBoard[i][j] = ' ';
				break;
			}
			case '$':
			{
				if (ghostCount >= GHOSTS)
				{
					break;
				}
				Ghost newGhost;
				newGhost.GameObject::setXY({ j,i });
				pacmanBoard[i][j] = ' ';
				ghost.push_back(newGhost);
				ghostCount++;
				break;
			}
			case '#':
			{
				pacmanBoard[i][j] = WALL;
				break;
			}
			case '%':
			{
				pacmanBoard[i][j] = ' ';
				break;
			}
			case '&':
			{
				setLegend(i, j);
				break;
			}
			case ' ':
			{
				if (pacmanBoard[i][j] == FOOD)
					pacmanBoard[i][j] = FOOD;
				else
					pacmanBoard[i][j] = ' ';
				break;
			}
			case '\n':
			{
				i++;
				j = -1;
				break;
			}
		}
		j++;
	}
}

void Board::printBoard(bool isColored)
{
	for (int i = 0; i < logicRows; i++)
	{
		for (int j = 0; j < logicCols; j++)
		{
			if (pacmanBoard[i][j] == WALL)
			{
				if (isColored) 
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
				}
			}
			else if (pacmanBoard[i][j] == TUNNEL)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);
				
			}
			else if (pacmanBoard[i][j] == FOOD)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			if (!isColored && pacmanBoard[i][j] != TUNNEL)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			cout << pacmanBoard[i][j];
		}
		cout << '\n';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

bool Board::isValidMove()
{
	int dir = pacman.getDir();
	Point curr = pacman.getXY();
	unsigned char whatsOnBoard = NULL;
	switch (dir)
	{
		case(UP):
		{
			whatsOnBoard = pacmanBoard[curr.y - 1][curr.x];
			break;
		}
		case(DOWN):
		{
			whatsOnBoard = pacmanBoard[curr.y + 1][curr.x];
			break;
		}
		case(RIGHT):
		{
			whatsOnBoard = pacmanBoard[curr.y][curr.x + 1];
			break;
		}
		case(LEFT):
		{
			whatsOnBoard = pacmanBoard[curr.y][curr.x - 1];
			break;
		}
		default:
			whatsOnBoard = pacmanBoard[curr.y][curr.x];
			break;
	}
	if (whatsOnBoard == WALL)
	{
		return false;
	}
	return true;
}

void Board::setGhostDirArr(int i, bool stupid)
{
	Point curr = ghost[i].getXY();
	((pacmanBoard[(curr.y) - 1][curr.x] != WALL))? ghost[i].setGhostPotArr(UP, true) : ghost[i].setGhostPotArr(UP, false);
	((pacmanBoard[(curr.y) + 1][curr.x] != WALL))? ghost[i].setGhostPotArr(DOWN, true) : ghost[i].setGhostPotArr(DOWN, false);
	((pacmanBoard[(curr.y)][(curr.x) + 1] != WALL))? ghost[i].setGhostPotArr(RIGHT, true) : ghost[i].setGhostPotArr(RIGHT, false);
	((pacmanBoard[(curr.y)][(curr.x) - 1] != WALL))? ghost[i].setGhostPotArr(LEFT, true) : ghost[i].setGhostPotArr(LEFT, false);
	
	if ((ghost[i].twoOrMoreDir()) && (!stupid))
	{
		ghost[i].cancelBackwards();
	}
}

int Board::updatePac(int& victory)
{
	if(!tunnelCheck(victory))
		pacman.GameObject::setNextXY();
	Point curr;
	curr = pacman.getXY();
	if (pacmanBoard[curr.y][curr.x] == FOOD)
	{
		pacmanBoard[curr.y][curr.x] = ' ';
		pacman.eat(1);
		victory--;
	}
	if (pacman.getXY().cmpPoint(fruit.getFruitXY()))
	{
		pacman.eat(fruit.getFigure());
		fruit.setState(0);
		fruit.setNewXY({ 0,0 });
	}
	return pacman.getScore();
}

void Board::setFruitNextMove()
{
	if (isNextMoveAWall() || isNextMoveATunnel() || whatInBoardXY(fruit.GameObject::getXY().x, fruit.GameObject::getXY().y) == WALL)
	{
		return;
	}
	else
	{
		fruit.setNextXY();
	}
}

void Board::reset(int mode)
{
	system("cls");
	gotoxy(DEFAULT_MSG, DEFAULT_MSG);
	if (mode != SILENT)
	{
		cout << "You have been eaten :(";
	}
	Sleep(2000);
	pacman.setPac();
	ghost.clear();
	ghostCount = 0;
	system("cls");
}
void Board::initPacBoard()
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
			pacmanBoard[i][j] = NULL;
	}
}

void Board::createTunnelVector()
{
	int i, j;
	for (i = 0, j = 0; j < logicCols; j++)
	{
		if (isTunnel(i, j))
		{
			Tunnel newTunnel;
			newTunnel.setTunnel({ j, i }, { j,logicRows - 1 });
			tunnels.push_back(newTunnel);
		}
	}
	for (j = 0; i < logicRows; i++)
	{
		if (isTunnel(i, j))
		{
			Tunnel newTunnel;
			newTunnel.setTunnel({ j, i }, { logicCols - 1, i });
			tunnels.push_back(newTunnel);
		}
	}
}

bool Board::tunnelCheck(int& victory)
{
	Point curr = pacman.getXY();
	for (auto& n : tunnels)
	{
		if ((curr.cmpPoint(n.getTunnel()[0])) || (curr.cmpPoint(n.getTunnel()[1])))
		{
			if (passTunnel(pacman.getDir(), n))
			{
				adjustPac(n);
				return true;
			}
		}
	}
	return false;
}

void Board::adjustPac(Tunnel tun)
{
	Point* tmp = tun.getTunnel();
	int dir = pacman.getDir();
	Point pac = pacman.getXY();
	switch (dir)
	{
		case(UP):
		{
			pacman.setXY(tmp[1]);
			break;
		}
		case(DOWN):
		{
			pacman.setXY(tmp[0]);
			break;
		}
		case(RIGHT):
		{
			pacman.setXY(tmp[0]);
			break;
		}
		case(LEFT):
		{
			pacman.setXY(tmp[1]);
			break;
		}
		case(STOP):
		{
			if(pac.cmpPoint(tmp[0]))
				pacman.setXY(tmp[1]);
			else
				pacman.setXY(tmp[0]);
			break;
		}
	}
}

bool Board::isNextMoveAWall(int i)
{
	int dir = ghost[i].GameObject::getDir();
	Point temp = ghost[i].GameObject::getXY();
	switch (dir)
	{
		case UP:
		{
			temp.y--;
			break;
		}
		case DOWN:
		{
			temp.y++;
			break;
		}
		case LEFT:
		{
			temp.x--;
			break;
		}
		case RIGHT:
		{
			temp.x++;
			break;
		}
	}
	return whatInBoardXY(temp.x, temp.y) == WALL;
}

bool Board::isNextMoveAWall()
{
	int dir = fruit.GameObject::getDir();
	Point temp = fruit.GameObject::getXY();
	switch (dir)
	{
	case UP:
	{
		temp.y--;
		break;
	}
	case DOWN:
	{
		temp.y++;
		break;
	}
	case LEFT:
	{
		temp.x--;
		break;
	}
	case RIGHT:
	{
		temp.x++;
		break;
	}
	}
	return whatInBoardXY(temp.x, temp.y) == WALL;
}

void Board::restart()
{
	initPacBoard();
	setLogicCols(DEFAULT);
	setLogicRow(DEFAULT);
	ghost.clear();
	tunnels.clear();
	timer = DEFAULT;
	ghostCount = DEFAULT;
	pacman.setDir(STOP);
	setTimer(DEAD);
}

bool Board::isNextMoveATunnel(int i)
{
	int dir = ghost[i].GameObject::getDir();
	Point temp = ghost[i].GameObject::getXY();
	int tunnelSize = tunnels.size();
	switch (dir)
	{
		case UP:
		{
			temp.y--;
			break;
		}
		case DOWN:
		{
			temp.y++;
			break;
		}
		case LEFT:
		{
			temp.x--;
			break;
		}
		case RIGHT:
		{
			temp.x++;
			break;
		}
	}

	for (int j = 0; j < tunnelSize; j++)
	{
		if (temp.cmpPoint(tunnels[j].getTunnel()[0]) || temp.cmpPoint(tunnels[j].getTunnel()[1]))
		{
			return true;
		}
	}
	return false;
}

bool Board::isNextMoveATunnel()
{
	int dir = fruit.getDir();
	Point temp = fruit.getXY();
	int tunnelSize = tunnels.size();
	switch (dir)
	{
	case UP:
	{
		temp.y--;
		break;
	}
	case DOWN:
	{
		temp.y++;
		break;
	}
	case LEFT:
	{
		temp.x--;
		break;
	}
	case RIGHT:
	{
		temp.x++;
		break;
	}
	}

	for (int j = 0; j < tunnelSize; j++)
	{
		if (temp.cmpPoint(tunnels[j].getTunnel()[0]) || temp.cmpPoint(tunnels[j].getTunnel()[1]))
		{
			return true;
		}
	}
	return false;
}

void Board::goBackwards(int i)
{
	int dir = ghost[i].getDir();
	switch (dir)
	{
		case UP:
		{
			ghost[i].setGhostPotArr(DOWN, true);
			ghost[i].setGhostPotArr(UP, false);
			break;
		}
		case DOWN:
		{
			ghost[i].setGhostPotArr(UP, true);
			ghost[i].setGhostPotArr(DOWN, false);
			break;
		}
		case LEFT:
		{
			ghost[i].setGhostPotArr(RIGHT, true);
			ghost[i].setGhostPotArr(LEFT, false);
			break;
		}
		case RIGHT:
		{
			ghost[i].setGhostPotArr(LEFT, true);
			ghost[i].setGhostPotArr(RIGHT, false);
			break;
		}
	}
}

void Board::setTimer(int newTime)
{
	if (newTime == DEAD)
	{
		timer = DEAD;
	}
	else if (newTime == RESET)
	{
		timer = ALIVE;
	}
	timer++;
}

void Board::randomizeGhostsMove()
{
	int ghostSize = getGhostSize();
	for (int i = 0; i < ghostSize; i++)
	{
		int dir = ghost[i].getDir();
		int temp = dir;
		do
		{
			setGhostDirArr(i, true);
			dir = rand() % 4;
		} while (!ghost[i].isValidDir(dir));
		ghost[i].setStupidGhostDir(dir);
	}
}

int Board::isOutOfBoard(Point nextMove)
{
	Point pac = pacman.getXY();
	if (pac.x < 0)
	{
		return LEFT;
	}
	else if (pac.x >= logicCols - 1)
	{
		return RIGHT;
	}
	else if (pac.y < 0)
	{
		return UP;
	}
	else if (pac.y >= logicRows - 1)
	{
		return DOWN;
	}
	else
	{
		return INVALID;
	}
}

void Board::fixLocation(int side)
{
	Point pac = pacman.getXY();
	switch (side)
	{
	case UP:
	{
		pacman.setXY({ pac.x , pac.y + logicRows - 1 });
		break;
	}
	case DOWN:
	{
		pacman.setXY({ pac.x, pac.y - logicRows + 1 });
		break;
	}
	case LEFT:
	{
		pacman.setXY({ pac.x + logicCols - 1, pac.y });
		break;
	}
	case RIGHT:
	{
		pacman.setXY({ pac.x - logicCols + 1, pac.y });
		break;
	}
	default:
		break;
	}
}
bool Board::isTunnel(int i, int j)
{
	bool res = false;
	if(i==0)
	{ 
		if ((pacmanBoard[i][j] == ' ' || pacmanBoard[i][j] == FOOD) && (pacmanBoard[logicRows - 1][j] == ' ' || pacmanBoard[logicRows - 1][j] == FOOD))
			res = true;
	}
	else
	{
		if (((pacmanBoard[i][j] == ' ') || (pacmanBoard[i][j] == FOOD)) && ((pacmanBoard[i][logicCols - 1] == ' ') || (pacmanBoard[i][logicCols - 1] == FOOD)))
		res = true;
	}
	return res;
}
bool Board::passTunnel(int dir, Tunnel& t)
{
	Point curr = pacman.getXY();
	switch (dir)
	{
	case UP:
		if (curr.y == 0)
			return true;
		break;
	case DOWN:
		if (curr.y == logicRows - 1)
			return true;
		break;
	case RIGHT:
		if (curr.x == logicCols - 1)
			return true;
		break;
	case LEFT:
		if (curr.x == 0)
			return true;
		break;
	}
	return false;
}

void Board::setNewLoadedFruit(std::vector<int>const(&fruitInfo)[MAX_ENTITIES], int i, int currFruit)
{
	if (i % RESET > DEAD)
	{
		setFruitState(false);
		setLoadedFruitFig(DEFAULT);

	}
	else
	{
		setFruitState(true);
		setLoadedFruitFig(fruitInfo[FRUIT_DATA][currFruit]);
	}
	Point initFruitPoint;
	initFruitPoint.x = fruitInfo[FRUIT_DATA][currFruit + 1];
	initFruitPoint.y = fruitInfo[FRUIT_DATA][currFruit + 2];
	fruit.setNewXY(initFruitPoint);
}

void Board::setGhostDir(int i, int newDir) { ghost[i].setStupidGhostDir(newDir); }
int Board::getGhostSize() { return ghost.size(); }
bool Board::isJunction(int i) { return ghost[i].twoOrMoreDir(); }
Point Board::getGhostXY(int i) { return ghost[i].getXY(); }
void Board::evaluateNewDir(int i) { ghost[i].keepForward(pacmanBoard); }
void Board::updateGDir(int i, Point pacLocation) { ghost[i].setNewGDir(i, pacLocation); } //updates ghost direction, i is the iterator
void Board::updateGhost(int i) { ghost[i].GameObject::setNextXY(); }//sets ghost cordinates, i is the iterator
std::vector<Ghost> Board::getGhostArr() { return ghost; } //returns a pointer to ghost array
void Board::updateGhostMove(int i) { ghost[i].updateMoveState(); } //updates the ghostmove from true to false and vice versa, i is the the iterator
bool Board::getGhostMoveState(int i) const { return ghost[i].getMoveState(); } //returns the ghost move state, i is the iterator

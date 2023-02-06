#include <stdlib.h>

#include "Ghost.h"
#include "Board.h"

void Ghost::getNewGDir(int ghost,Point pacLocation)
{
	int newDir;
	double minimumDist = 0;
	double currDist = INVALID;
	bool doOnce = 0;
	for (int i = 0; i < 4; i++)
	{
		Point temp = getXY();
		if (!ghostPotDir[i])
		{
			continue;
		}
		switch (i)
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
		currDist = temp.dist(pacLocation);

		if ((currDist <= minimumDist) || (doOnce == 0))
		{
			minimumDist = currDist;
			newDir = i;
			doOnce = 1;
		}
	}
	dir = newDir;
}

void Ghost::writeNewDirToFile(int i, int dir, int numStage)
{
	std::string name = getName(GHOST1 + i, numStage);
	std::ofstream result(name, std::ofstream::app);
	std::string dirStr;

	dirStr = getDirString();
	result << " " << dirStr;
}

void Ghost::keepForward(unsigned char board[MAX_ROWS][MAX_COLS])
{
	Point temp = getXY();
	int tmpDir = getDir();
	setGhostPotArr(tmpDir, false);
	int newDir = 0;
	while ((!ghostPotDir[newDir]) && (newDir < STOP))
	{
		newDir++;
	}
	if (newDir == STOP)
	{
		newDir = initGDirArr(board,tmpDir);
	}
	dir = newDir;
}

int Ghost::initGDirArr(unsigned char board[MAX_ROWS][MAX_COLS],int tmpDir)
{
	int newDir = 0;
	(board[(cord.y) - 1][cord.x] != WALL) ? setGhostPotArr(UP, true) : setGhostPotArr(UP, false);
	(board[(cord.y) + 1][cord.x] != WALL) ? setGhostPotArr(DOWN, true) : setGhostPotArr(DOWN, false);
	(board[(cord.y)][(cord.x) + 1] != WALL) ? setGhostPotArr(RIGHT, true) : setGhostPotArr(RIGHT, false);
	(board[(cord.y)][(cord.x) - 1] != WALL) ? setGhostPotArr(LEFT, true) : setGhostPotArr(LEFT, false);
	
	setGhostPotArr(tmpDir, false);
	while ((!ghostPotDir[newDir]))
	{
		newDir++;
	}
	return newDir;
}

bool Ghost::twoOrMoreDir()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (ghostPotDir[i])
		{
			count++;
		}
	}
	return count >= 2 ? true : false;
}

void Ghost::cancelBackwards()
{
	switch (dir)
	{
		case UP:
		{
			ghostPotDir[DOWN] = false;
			break;
		}
		case DOWN:
		{
			ghostPotDir[UP] = false;
			break;
		}
		case LEFT:
		{
			ghostPotDir[RIGHT] = false;
			break;
		}
		case RIGHT:
		{
			ghostPotDir[LEFT] = false;
			break;
		}
	}
}

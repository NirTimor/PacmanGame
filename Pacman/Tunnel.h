#pragma once
#include "Point.h"
#include "Pacman.h"
class Fruit;
class Pacman;
class Ghost;
class Board;
class Game;
class Update;
class GameObjects;
class Tunnel 
{
	Point tunnel[2];

public:
	void setTunnel(Point a, Point b) { tunnel[0] = a, tunnel[1] = b; }
	Point* getTunnel() { return tunnel; }
};


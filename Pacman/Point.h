#pragma once
#include <math.h>

struct Point
{
	int x;
	int y;
	bool cmpPoint(const Point& toCompare) const{ return (x == toCompare.x && y == toCompare.y); } //compare to points
	double dist(Point pac) const{ return sqrt((pac.x - x) * (pac.x - x) + (pac.y - y) * (pac.y - y)); }
};
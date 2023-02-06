#include "GameObject.h"

Point GameObject::setNextXY()
{
	switch (dir)
	{
	case(UP):
	{
		cord.y--;
		break;
	}
	case(DOWN):
	{
		cord.y++;
		break;
	}
	case(LEFT):
	{
		cord.x--;
		break;
	}
	case(RIGHT):
	{
		cord.x++;
		break;
	}
	default:
		break;
	}
	return cord;
}

void GameObject::setXY(Point pos)
{
	cord.x = pos.x;
	cord.y = pos.y;
}

std::string GameObject::getDirString()
{
	switch (dir)
	{
	case(UP):
	{
		return "UP";
	}
	case(DOWN):
	{
		return "DOWN";
	}
	case(LEFT):
	{
		return "LEFT";
	}
	case(RIGHT):
	{
		return "RIGHT";
	}
	case(STOP):
	{
		return "STOP";
	}
	}
}

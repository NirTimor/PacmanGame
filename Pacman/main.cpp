#pragma once
#include "Game.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include "utils.h"

int main(int argc, char* argv[])
{
	Game theGame;
	theGame.setLoadedGame(setMode(argc, argv));
	if (theGame.getIsLoaded() == SAVE)
	{
		while (theGame.startGame());
	}
	else if (theGame.getIsLoaded() == LOAD || theGame.getIsLoaded() == SILENT)
	{
		theGame.playLoadedGame();
	}
	return 0;
}
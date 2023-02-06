#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include <filesystem>
#include "utils.h"
#include "Update.h"
#include "consts.h"
#include <vector>
#include <fstream>   
#include <sstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <algorithm>
class Fruit;
class Pacman;
class Ghost;
class Board;
class Update;
class GameObjects;
using namespace std::filesystem;

class Game
{
	int flag; //get back from instructions to main menu
	int choice; //the player choice from the menu
	int pacLives; //the lives of the pacman
	bool isGameStarted;  //flag to know if game has started
	int newDir; //new direction recieved from user
	int victory;
	char level;
	int timer;
	std::vector <std::string> files;
	std::vector <std::string> stepsFile;
	std::string fileName;
	bool playFromFile;
	int winCondition;
	int isLoadedFile;
	int moves;
public:
	Game();
	int getMoves() { return moves; }
	bool startGame(); //starts the game and returns false if player chooses to quit
	void PrintMenu(); //prints the menu
	void PlayGame(bool isColored); //the game main function, isColored determines wether the game is colored or not
	void GameOver(); //ends games and returns to main menu
	void Victory(); //if players eats all the breadcrumbs he is victorious and returns to main menu
	int checkValidInput(char dir); //checks if the player entered a valid input and returns enum DIRECTION
	void pause(); //pauses the game until ESC is pressed again
	int getPacLives() const{ return pacLives; } //gets pacman lives
	bool isDead(Update& curr, Update& prev); //returns true if pacman hits a ghost
	void updateGameLives() { pacLives--; } //updates pacman lives incase of death
	void initGame(); //init game variables after gameover/victory
	void printInstructions(); //prints the instructions
	void endGame(const char* msg, int score); //ends the game with msg sended
	void gameStart(Board& board, Update& curr, Update& prev, bool isColored); //prints the game for the first time and runs until player inserts a valid key
	bool updateValidInput(Board& board); //updates a valid input and moves pacman accordingly, returns true if player is victorious
	bool getNewInput(Board& board, bool isColored); //gets new input from user and pauses if its ESC returns true if player wants to exit pause mode
	void setNewGhostsDir(Board& board); //sets and updates the ghosts directions and cordintes
	void printChanges(Board& board, Update& curr, Update& prev, bool isColored); //prints the new data
	bool checkIfDead(Board& board, Update& curr, Update& prev); //checks if pacman is dead returns true if its game over
	void fruitCycle(Board& board);
	int chooseGhostLevel();
	void adjustGhostByLevel(Board& board);
	void changeGhostDir(Board& board);// { board.randomizeGhostsMove(); }
	void getFileVector();
	void getFileName();
	void initBetweenScreen(Board& board);
	void setLoadedGame(int b) { isLoadedFile = b; }
	int getIsLoaded() { return isLoadedFile; }
	void playLoadedGame();
	void getStepsFileVector();
	void getObjectsSteps(std::vector<int>(&steps)[MAX_ENTITIES], int i);
	void loadedGameStart(Board& board, Update& curr, Update& prev, std::vector<int>const(&steps)[MAX_ENTITIES], int fruitCycle);
	int getAmountOfElements(std::string line);
	void stringToMovesArr(std::string line, std::vector<int>&arr);
	void fruitInitFromFile(std::string line, std::vector<int>&arr);
	void updateNewInput(std::vector<int>const(&steps)[MAX_ENTITIES],int fruitCycle,  Board& board);
	bool updateLoadedValidInput(Board& board);
	void setNewLoadedGhostsDir(Board& board, std::vector<int>const(&steps)[MAX_ENTITIES], int move);
	void writeToResFile(int condition);
	void generateMoveFile(Board& board);
	void mergeMovesToStepFile(Board& board);
	void emptyMoveFile(Board& board);
	void printLeaderBoard();
	void addToLeaderBoard(int score);
	void insertNewHighScore(std::vector<std::string> &leaders, int i, std::string name, int score);
};


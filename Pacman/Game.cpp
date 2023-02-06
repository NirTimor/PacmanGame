#include "Game.h"
#include "Board.h"

Game::Game() //game ctor
{
	initGame();
	srand(time(NULL));
	ShowConsoleCursor(false);
	getFileVector();
	getStepsFileVector();
}

bool Game::startGame()
{
	while (isLoadedFile == SAVE)
		{
			PrintMenu();
			scanf("%d", &choice);
			cleanBuffer();
			if (!isDigit(choice))
				choice = INVALID;
			switch (choice)
			{
			case(PLAY_WITH_COLORS):
			{
				PlayGame(WITH_COLORS);
				break;
			}
			case(PLAY):
			{
				PlayGame(NO_COLORS);
				break;
			}
			case(LEADER_BOARD):
			{
				printLeaderBoard();
				break;
			}
			case(INSTRUCTIONS):
			{
				printInstructions();
				break;
			}
			case(PLAY_BY_FNAME):
			{
				if (playFromFile)
				{
					playFromFile = false;
					break;
				}
				getFileName();
				break;
			}
			case(EXIT):
			{
				system("cls");
				std::cout << "GoodBye!" << std::endl;
				return false;
			}
			default:
				std::cout << " Please enter a valid choice!\n" << std::endl;
				Sleep(2000);
				system("cls");
				break;
			}
		}
}

void Game::printLeaderBoard()
{
	system("cls");
	std::ifstream leaders("leaderboard.txt");
	std::string line;
	int i = 0;
	while (std::getline(leaders, line))
	{
		gotoxy(40, 8 + i);
		std::cout << i + 1 << ") ";
		std::cout << line;
		i++;
	}
	gotoxy(0, DEFAULT_MSG);
	std::cout << " To go back to the menu , press any key" << std::endl;
	while (!_kbhit());
	system("cls");
}

void Game::addToLeaderBoard(int score)
{
	std::vector<std::string> leaders;
	std::fstream leaderBoard("leaderboard.txt");
	std::string currLine;
	std::string name;
	int count, i;
	count = i = 0;
	while (std::getline(leaderBoard, currLine))
	{
		leaders.push_back(currLine);
		count++;
	}
	if (count == 0)
	{
		gotoxy(DEFAULT_MSG, DEFAULT_MSG);
		std::cout << "you've reached the highscores! enter your name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		insertNewHighScore(leaders, 1, name, score);
		system("cls");
		return;
	}
	for (int i = 0; i < count; i++)
	{
		int pos = leaders[i].find_last_of(" ");
		if (isANumber(leaders[i].substr(pos + 1, leaders[i].size())))
		{
			if (std::stoi(leaders[i].substr(pos, leaders[i].size()).c_str()) < score)
			{
				gotoxy(DEFAULT_MSG, DEFAULT_MSG);
				std::cout << "you've reached the highscores! enter your name: ";
				std::cin.ignore();
				std::getline(std::cin, name);
				insertNewHighScore(leaders, i + 1, name, score);
				system("cls");
				return;
			}
		}
	}
	if (leaders.size() < MAX_HIGHSCORES)
	{
		gotoxy(DEFAULT_MSG, DEFAULT_MSG);
		std::cout << "you've reached the highscores! enter your name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		insertNewHighScore(leaders, leaders.size(), name, score);
		system("cls");
		return;
	}

}

void Game::insertNewHighScore(std::vector<std::string> &leaders, int i, std::string name, int score)
{
	std::string newHighScore(name);
	newHighScore.append(" ");
	newHighScore.append(std::to_string(score));
	int leadersSize = leaders.size();
	int index;
	if (leadersSize == MAX_HIGHSCORES)
	{
		leaders[leadersSize - 1].clear();
	}

	leaders.push_back(newHighScore);
	index = leaders.size();
	while (index > i)
	{
		leaders[index - 1].swap(leaders[index - 2]);
		index--;
	}

	std::ofstream leaderBoard("leaderboard.txt", std::ofstream::out | std::ios::trunc);
	for (int j = 0; j < leaders.size(); j++)
	{
		leaderBoard << leaders[j] << std::endl;
	}
}

void Game::PrintMenu()
{
	gotoxy(40, 8);
	std::cout << "Welcome!" << std::endl;
	gotoxy(40, 9);
	std::cout << "Please enter your choice:" << std::endl;
	gotoxy(40, 10);
	std::cout << "1)Start a new colored game." << std::endl;
	gotoxy(40, 11);
	std::cout << "2)Start a new uncolored game." << std::endl;
	gotoxy(40, 12);
	if (!playFromFile)
	{
		std::cout << "3)Start a game from a specific file." << std::endl;
	}
	else
	{
		std::cout << "3)Cancel a game from a specific file." << std::endl;
	}
	gotoxy(40, 13);
	std::cout << "4)Leaderboards." << std::endl;
	gotoxy(40, 14);
	std::cout << "8)Present instructions and keys." << std::endl;
	gotoxy(40, 15);
	std::cout << "9)Exit." << std::endl;
}

int Game::checkValidInput(char dir)
{
	if (dir == 'W' || dir == 'w')
		return UP;
	if (dir == 'X' || dir == 'x')
		return DOWN;
	if (dir == 'A' || dir == 'a')
		return LEFT;
	if (dir == 'D' || dir == 'd')
		return RIGHT;
	if (dir == 'S' || dir == 's')
		return STOP;
	if (dir == ESC)
		return ESC;
	else
		return INVALID;
}

void Game::playLoadedGame()
{
	if (stepsFile.size() != files.size())
	{
		printError();
	}
	system("cls");
	Board board;
	Update curr, prev;
	int vecSize = files.size();
	std::vector<int> gameObjects[MAX_ENTITIES];
	for (int i = 0; i < vecSize; i++)
	{
		fileName = files[i];
		bool prevState = false;
		int fruitCycle = 0;
		board.readNewBoard(fileName, victory);
		for (int j = 0; j < MAX_ENTITIES; j++)
		{
			gameObjects[j].clear();
		}
		getObjectsSteps(gameObjects, i);
		while (getPacLives())
		{
			if (!isGameStarted)
			{
				loadedGameStart(board, curr, prev, gameObjects, fruitCycle);
			}
			if (isLoadedFile != SILENT)
				Sleep(PAC_PACE);
			updateNewInput(gameObjects,fruitCycle, board);
			if (board.getFruitState() && !prevState)
			{
				if (gameObjects[FRUIT_DATA][fruitCycle + 1] < board.getLogicCols() && gameObjects[FRUIT_DATA][fruitCycle + 2] < board.getLogicRows() && board.whatInBoardXY(gameObjects[FRUIT_DATA][fruitCycle + 1], gameObjects[FRUIT_DATA][fruitCycle + 2]) != WALL)
				{
					board.setLoadedFruitXY(gameObjects[FRUIT_DATA][fruitCycle + 1], gameObjects[FRUIT_DATA][fruitCycle + 2]);
				}
				else
				{
					board.setFruitFig();
				}

				fruitCycle += 3;
				prevState = true;
				if (gameObjects[FRUIT_DATA].size() <= fruitCycle)
				{
					fruitCycle = 0;
				}
			}
			if ((moves % FRUIT_PACE == 0) && (board.getFruitState()))
			{
				board.setFruitNextMove();
			}
			if (updateLoadedValidInput(board))
			{
				break;
			}
			setNewLoadedGhostsDir(board, gameObjects, moves);

			prev = curr;
			printChanges(board, curr, prev, false);

			if (checkIfDead(board, curr, prev))
			{
				i = vecSize;
				break;
			}
			if (!board.getFruitState())
			{
				prevState = false;
			}
			moves++;
		}
	}
}

void Game::updateNewInput(std::vector<int>const(&gameObjects)[MAX_ENTITIES], int fruitCycle, Board& board)
{
	board.updateDir(gameObjects[PACMAN][moves % gameObjects[PACMAN].size()]);
	for (int i = 0; i < board.getGhostSize(); i++)
	{
		board.setGhostDirArr(i, false);
		if (board.isNextMoveAWall(i) || board.isNextMoveATunnel(i))
		{
			board.evaluateNewDir(i);
			continue;
		}
		board.getGhostArr()[i].GameObject::setNewDir(gameObjects[i + GHOST1][moves % gameObjects[i + GHOST1].size()]);
	}
	if (((moves % RESET) >= DEAD) && board.getFruitState())
	{
		board.setFruitState(false);
		board.setFruitXY();
		board.setFruitFig();
	}
	else if (moves % RESET < DEAD)
	{
		if (!board.getFruitState())
		{
			board.setFruitState(true);
			board.setLoadedFruitFig(gameObjects[FRUIT_DATA][fruitCycle]);
		}
		board.setFruitDir(gameObjects[FRUIT][moves % gameObjects[FRUIT].size()]);
	}
}

void Game::getObjectsSteps(std::vector<int>(&steps)[MAX_ENTITIES], int i)
{
	std::ifstream stepFile(stepsFile[i]);
	int count = 0;
	for (std::string line; std::getline(stepFile, line); )
	{
		if (count != FRUIT_DATA)
			stringToMovesArr(line, steps[count]);
		else
			fruitInitFromFile(line, steps[count]);
		count++;
	}
	if (steps[FRUIT_DATA].size() % 3 != 0)
	{
		printError();
	}
}

void Game::fruitInitFromFile(std::string line, std::vector<int>&arr)
{
	std::string curr;
	std::istringstream out(line);
	while (out >> curr)
	{
		arr.push_back(stoi(curr));
	}
}

void Game::stringToMovesArr(std::string line, std::vector<int>&arr)
{
	std::string curr;
	std::istringstream out(line);
	int i = 0;
	
	while (out >> curr)
	{
		if (!curr.compare("UP"))
		{
			arr.push_back(UP);
		}
		else if (!curr.compare("DOWN"))
		{
			arr.push_back(DOWN);
		}
		else if (!curr.compare("RIGHT"))
		{
			arr.push_back(RIGHT);
		}
		else if (!curr.compare("LEFT"))
		{
			arr.push_back(LEFT);
		}
		else if (!curr.compare("STOP"))
		{
			arr.push_back(STOP);
		}
		else
		{
			printError();
		}
	}
}

int Game::getAmountOfElements(std::string line)
{
	int elemCount;
	int i;
	i = elemCount = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			elemCount++;
		i++;
	}
	return elemCount + 1;
}

void Game::PlayGame(bool isColored)
{
	system("cls");
	Board board;
	Update curr, prev;
	level = chooseGhostLevel();
	int vecSize = files.size();
	for (int i = 0; i < vecSize; i++)
	{
		if (!playFromFile)
		{
			fileName = files[i];
		}

		board.readNewBoard(fileName, victory);
		emptyMoveFile(board);

		while (getPacLives())
		{
			fruitCycle(board);
			gameStart(board, curr, prev, isColored);
			Sleep(PAC_PACE);
			if (getNewInput(board, isColored))
			{
				continue;
			}
			if (updateValidInput(board))
			{
				break;
			}
			adjustGhostByLevel(board);
			prev = curr;
			printChanges(board, curr, prev, isColored);

			if (checkIfDead(board, curr, prev))
			{
				i = vecSize;
				break;
			}
			moves++;
		}
		moves = DEFAULT;
	}
}

void Game::emptyMoveFile(Board& board)
{
	std::ofstream moveFile;
	std::string name;
	for(int i = 0 ;i < board.getGhostSize() + 3; i++)
	{
		name = getName(i, std::distance(files.begin(), std::find(files.begin(), files.end(), fileName)));
		moveFile.open(name, std::ofstream::out | std::ofstream::trunc);
		moveFile.close();
	}
}

void Game::pause()
{
	system("cls");
	gotoxy(DEFAULT_MSG, DEFAULT_MSG);
	std::cout << "Game is paused, press ESC to continue";
	while (_getch() != ESC);
	system("cls");
}

bool Game::isDead(Update& curr, Update& prev)
{
	Point pacCurr,pacPrev;
	pacCurr = curr.getPacPoint();
	pacPrev = prev.getPacPoint();

	for (int i = 0; i < GHOSTS; i++)
	{
		if (pacCurr.cmpPoint(curr.getGhostPoint(i)))
			return true;
		if ((pacPrev.cmpPoint(curr.getGhostPoint(i)))&&(pacCurr.cmpPoint(prev.getGhostPoint(i))))
			return true;
	}
	return false;
}

void Game::initGame()
{
	choice = DEFAULT;
	flag = DEFAULT;
	pacLives = LIVES;
	newDir = INVALID;
	isGameStarted = false;
	victory = DEFAULT;
	level = INVALID;
	timer = DEFAULT;
	playFromFile = DEFAULT;
	winCondition = DEFAULT;
	isLoadedFile = DEFAULT;
	moves = DEFAULT;
}

void Game::endGame(const char* msg, int score)
{
	system("cls");
	gotoxy(DEFAULT_MSG, DEFAULT_MSG);
	std::cout << msg;
	Sleep(3000);
	system("cls");
	if (isLoadedFile == SAVE)
	{
		addToLeaderBoard(score);
	}
	initGame();
}

void Game::printInstructions()
{
	system("cls");
	std::cout << "Instructions are as following : \n" << std::endl;
	std::cout << " Guide Pacman around the maze and eat all the breadcrumbs while avoiding those nasty ghosts.\n" << std::endl;
	std::cout << "Sometimes, a fruit appears which gives you a bonus score when eaten.\n" << std::endl;
	std::cout << "Be aware of the ghosts ! if you get eaten by them you will lose a life !\n" << std::endl;
	std::cout << "Keys are as following : A for Left , D for right , W for up , X for down , and S for staying in your place.\n" << std::endl;
	std::cout << "That's it , Good Luck ! " << std::endl;
	std::cout << " To go back to the menu , press any key" << std::endl;
	while (!_kbhit());
	system("cls");
}

void Game::gameStart(Board& board, Update& curr, Update& prev,bool isColored)
{
	while ((newDir == INVALID) || (!isGameStarted))
	{
		if (!isGameStarted)
		{
			board.setNewFruit(std::distance(files.begin(),std::find(files.begin(),files.end(),fileName)));
			int ghostSize = board.getGhostSize();
			bool alive = board.getFruitState();
			Point pacPoint = board.getPacXY();
			curr.setPacPoint(pacPoint);
			curr.setGhostsPoint(board.getGhostArr(),board.getGhostSize());
			curr.setFruitPoint(board.getFruitXY());
			curr.setFruitFig(board.getFruitFig());
			board.printBoard(isColored);
			curr.printFirstXY(board, isColored, ghostSize);
			curr.setPacScore(board.getPacScore());
			curr.printScore(board.getLegend());
			curr.printLives(board.getLegend());
			isGameStarted = true;
		}
		if (_kbhit())
		{
			newDir = checkValidInput(_getch());
		}
		if (newDir != -1)
		{
			board.updateDir(newDir);
		}
	}
}

void Game::loadedGameStart(Board& board, Update& curr, Update& prev, std::vector<int>const(&gameObjects)[MAX_ENTITIES], int fruitCycle)
{
	board.setNewLoadedFruit(gameObjects, moves, fruitCycle);
	int ghostSize = board.getGhostSize();
	bool alive = board.getFruitState();
	Point pacPoint = board.getPacXY();
	curr.setPacPoint(pacPoint);
	curr.setGhostsPoint(board.getGhostArr(), board.getGhostSize());
	curr.setFruitPoint(board.getFruitXY());
	curr.setFruitFig(board.getFruitFig());
	curr.setPacScore(board.getPacScore());
	if (isLoadedFile != SILENT)
	{
		board.printBoard(false);
		curr.printFirstXY(board,false, ghostSize);
		curr.printScore(board.getLegend());
		curr.printLives(board.getLegend());
	}
	isGameStarted = true;
}

bool Game::updateValidInput(Board& board)
{
	if (newDir != -1)
	{
		if (newDir == ESC)
		{
			board.updateDir(board.getPacmanDir());
		}
		else
		{
			board.updateDir(newDir);
		}
	}
	if (board.isValidMove())
	{
		board.updatePac(victory);
		if (victory == 0)
		{
			writeToResFile(WIN_FILE);
			generateMoveFile(board);
			mergeMovesToStepFile(board);
			winCondition++;
			if (playFromFile)
			{
				endGame("You are victorious!!!", board.getPacScore());
			}
			else
			{
				if (winCondition == files.size())
				{
					endGame("You are victorious!!!", board.getPacScore());
				}
			}
			initBetweenScreen(board);
			moves = DEFAULT;
			return true;
		}
	}
	return false;
}

void Game::mergeMovesToStepFile(Board& board)
{
	std::ofstream stepsFile;
	std::ifstream moveFile;
	std::string name = fileName;
	std::string objectMove;
	int pos = name.find(".");
	name.replace(pos + 1, 6, "steps");
	stepsFile.open(name, std::ofstream::out | std::ios::trunc);

	for (int i = 0; i < board.getGhostSize() + 3; i++)
	{

		name = getName(i, std::distance(files.begin(), std::find(files.begin(), files.end(), fileName)));
		moveFile.open(name);
		std::getline(moveFile, objectMove);
		objectMove[objectMove.size() - 1] = '\n';
		stepsFile << objectMove;
		moveFile.close();
	}
}

void Game::writeToResFile(int condition)
{
	std::string name = fileName;
	int pos = fileName.find(".");
	name.replace(pos+1, 6, "result");

	std::ofstream result(name, std::ofstream::app);
	switch (condition)
		{
		case DIED:
		{
			result << "you died after  " << moves << " moves" << std::endl;
			break;
		}
		case WIN_FILE:
		{
			result << "screen finished after  " << moves << " moves" << std::endl;
			break;
		}
	}
}

bool Game::updateLoadedValidInput(Board& board)
{
	if (board.isValidMove())
	{
		board.updatePac(victory);
		if (victory == 0)
		{
			winCondition++;
			writeToResFile(WIN_FILE);
			if (winCondition == files.size())
			{
				if (isLoadedFile != SILENT)
				{
					endGame("You are victorious!!!", board.getPacScore());
				}
			}
			moves = DEFAULT;
			initBetweenScreen(board);
			return true;
		}
		else
			return false;
	}
}

void Game::initBetweenScreen(Board& board)
{
	system("cls");
	isGameStarted = false;
	board.restart();
}

bool Game::getNewInput(Board& board, bool isColored)
{
	if (_kbhit())
	{
		newDir = checkValidInput(_getch());
		if (newDir == ESC)
		{
			pause();
			board.printBoard(isColored);
			return true;
		}
	}
	return false;
}

void Game::setNewGhostsDir(Board& board)
{
	Point temp;
	int ghostSize = board.getGhostSize();
	for (int i = 0; i < ghostSize; i++)
	{
		if (board.getGhostMoveState(i))
		{
			temp = board.getGhostXY(i);
			board.setGhostDirArr(i,false);
				if (board.isJunction(i))
				{
					board.updateGDir(i, board.getPacXY());
				}
			if (board.isNextMoveAWall(i) || board.isNextMoveATunnel(i))
			{
				board.evaluateNewDir(i);
			}
			board.updateGhost(i);
		}
		board.updateGhostMove(i);
	}
}

void Game::setNewLoadedGhostsDir(Board& board, std::vector<int>const(&gameObjects)[MAX_ENTITIES], int move)
{
	int ghostSize = board.getGhostSize();
	for (int i = 0; i < ghostSize; i++)
	{
		if (board.getGhostMoveState(i))
		{
			board.setGhostDir(i, gameObjects[GHOST1 + i][move % gameObjects[GHOST1 + i].size()]);
			if (board.isNextMoveAWall(i) || board.isNextMoveATunnel(i))
			{
				continue;
			}
			board.updateGhost(i);
		}
		board.updateGhostMove(i);
	}
}

void Game::printChanges(Board& board, Update& curr, Update& prev, bool isColored)
{
	bool alive = board.getFruitState();
	int ghostSize = board.getGhostSize();
	curr.setFruitPoint(board.getFruitXY());
	curr.setFruitFig(board.getFruitFig());
	curr.setPacPoint(board.getPacXY());
	curr.setGhostsPoint(board.getGhostArr(), ghostSize);
	curr.setPacScore(board.getPacScore());
	if (isLoadedFile != SILENT)
	{
		prev.printDiffXY(curr, board, isColored, alive,ghostSize);
		curr.printScore(board.getLegend());
	}
	if (isLoadedFile == SAVE)
	{
		generateMoveFile(board);
	}
}

void Game::generateMoveFile(Board& board)
{
	std::string dirStr;
	std::string name;
	auto stage = std::find(files.begin(), files.end(), fileName);
	name = getName(PACMAN, std::distance(files.begin(), stage));
	std::ofstream result(name, std::ofstream::app);
	dirStr = board.getPac().getDirString();
	result << dirStr << " ";
	result.close();
	name = getName(FRUIT, std::distance(files.begin(), stage));
	result.open(name, std::ofstream::app);
	dirStr = board.getFruit().getDirString();
	result << dirStr << " ";
	result.close();
	for (int i = 0; i < board.getGhostSize(); i++)
	{
		name = getName(GHOST1 + i, std::distance(files.begin(), stage));
		result.open(name, std::ofstream::app);
		dirStr = board.getGhostArr()[i].getDirString();
		result << dirStr << " ";
		result.close();
	}
}

bool Game::checkIfDead(Board& board, Update& curr, Update& prev)
{
	if (isDead(curr, prev))
	{
		writeToResFile(DIED);
		updateGameLives();
		curr.updateCurrLives();
		newDir = INVALID;
		if (getPacLives())
		{
			board.resetBoard(fileName,isLoadedFile);
			isGameStarted = false;
		}
		else
		{
			if (isLoadedFile != SILENT)
				endGame("Gameover!!!", board.getPacScore());
			return true;
		}
	}
	return false;
}

void Game::fruitCycle(Board& board)
{
	int fruitTimer = board.getTimer();
	bool alive = board.getFruitState();
	int ghostSize = board.getGhostSize();
	if (!isGameStarted || fruitTimer == RESET)
	{
		board.setFruitState(true);
		if (fruitTimer == INVALID || fruitTimer == RESET)
		{
			board.setTimer(RESET);
			board.setNewFruit(std::distance(files.begin(), std::find(files.begin(), files.end(), fileName)));
			return;
		}
	}
	for (int i = 0; i < ghostSize; i++)
	{
		if (board.getFruitXY().cmpPoint(board.getGhostXY(i)))
		{
			board.setFruitState(false);
			board.setFruitXY();
		}
	}
	if (fruitTimer < DEAD && alive)
	{
		if (fruitTimer % 10 == 0)
		{
			board.changeFruitDir();
		}
	}
	else if (alive && fruitTimer >= DEAD)
	{
		board.setFruitState(false);
		board.setFruitFig();
		board.setFruitXY();
	}
	else if (!alive && fruitTimer <= DEAD)
	{
		board.setFruitState(false);
		board.setTimer(DEAD);
	}
	board.setTimer(ALIVE);
}

int Game::chooseGhostLevel()
{
	system("cls");
	gotoxy(40, 7);
	std::cout << "choose a level:";
	gotoxy(40, 8);
	std::cout << "a) BEST";
	gotoxy(40, 9);
	std::cout << "b) GOOD";
	gotoxy(40, 10);
	std::cout << "c) NOVICE\n";

	while (true)
	{
		std::cin >> level;
		switch (level)
		{
			case 'a':
			{
				system("cls");
				return BEST;
			}
			case 'b':
			{
				system("cls");
				return GOOD;
			}
			case 'c':
			{
				system("cls");
				return NOVICE;
			}
			default:
			{
				std::cout << "invalid input!\n";
				cleanBuffer();
				break;
			}
		}
	}
}

void Game::adjustGhostByLevel(Board &board)
{
	int ghostsSize = board.getGhostSize();
	switch (level)
	{
		case BEST:
		{
			setNewGhostsDir(board);
			break;
		}
		case GOOD:
		{
			if (timer < 20)
			{
				setNewGhostsDir(board);
			}
			else if ((timer >= 20) && (timer != 25))
			{
				if (timer == 20)
				{
					changeGhostDir(board);
				}
				for (int i = 0; i < ghostsSize; i++)
				{
					if (!board.isNextMoveAWall(i) && !board.isNextMoveATunnel(i))
					{
						if (board.getGhostMoveState(i))
						{
							board.updateGhost(i);
						}
					}
					board.updateGhostMove(i);
				}
			}
			else if (timer == 25)
			{
				setNewGhostsDir(board);
				timer = 0;
			}
			break;
		}
		case NOVICE:
		{
			if (timer == 20)
			{
				timer = 0;
				changeGhostDir(board);
			}
			for (int i = 0; i < ghostsSize; i++)
			{
				if (!board.isNextMoveAWall(i) && !board.isNextMoveATunnel(i))
				{
					if (board.getGhostMoveState(i))
					{
						board.updateGhost(i);
					}
				}
				board.updateGhostMove(i);
			}
			break;
		}
	}
	timer++;
}

void Game::getFileVector()
{
	const path projPath = current_path();

	for (const auto& entry : directory_iterator(projPath)) 
	{
		auto fileName = entry.path().filename().string();
		if (entry.is_regular_file())
			if (fileName.find(".screen") != std::string::npos)
				files.push_back(static_cast<std::string>(fileName));
	}
	sort(files.begin(), files.end());
}

void Game::getStepsFileVector()
{
	const path projPath = current_path();

	for (const auto& entry : directory_iterator(projPath))
	{
		auto fileName = entry.path().filename().string();
		if (entry.is_regular_file())
			if (fileName.find(".steps") != std::string::npos)
				stepsFile.push_back(static_cast<std::string>(fileName));
	}
	sort(stepsFile.begin(), stepsFile.end());
}

void Game::getFileName()
{
	std::cin >> fileName;
	if (find(files.begin(), files.end(), fileName) != files.end())
	{
		playFromFile = true;
	}
	else
	{
		std::cout << "Couldnt find the file!";
		Sleep(2000);
		system("cls");
	}
}

void Game::changeGhostDir(Board& board) { board.randomizeGhostsMove(); }

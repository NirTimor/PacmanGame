#pragma once

/*
header file for all game constants and enums
*/
#define PAC_FILES pacman_*.screen
enum MENU_OPTIONS { INVALID = -1, DEFAULT = 0, PLAY_WITH_COLORS = 1, PLAY = 2, PLAY_BY_FNAME = 3, LEADER_BOARD = 4, INSTRUCTIONS = 8, EXIT = 9, ESC = 27 };
enum PAC_CORD { PACX = 15, PACY = 15 };
enum NORTH_TUNNEL { NORTHX = 14, NORTHY = 0 };
enum SOUTH_TUNNEL { SOUTHX = 14, SOUTHY = 30 };
enum EAST_TUNNEL { EASTX = 28, EASTY = 14 };
enum WEST_TUNNEL { WESTX = 0, WESTY = 14 };
enum DIRECTION { UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3, STOP = 4 };
enum GHOST_CORD { GHOSTX = -1, GHOSTY = -1 };
enum COLORS { BLACK = 0, BLUE = 1, GREEN = 2, RED = 4, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15 };
enum PLAY_COLORED { NO_COLORS, WITH_COLORS  };
enum GHOST_NAMES { BLINKY, PINKY, STINKY, KINKY };
enum FRUIT_STATES { ALIVE = 0, DEAD = 100, RESET = 150 };
enum GHOSTS_LEVEL {BEST,GOOD,NOVICE};
enum MODE {SAVE = 0 , LOAD = 1 , SILENT = 2};
enum STEPS { PACMAN, FRUIT, FRUIT_DATA, GHOST1, GHOST2, GHOST3, GHOST4 };
enum PACE { FRUIT_PACE = 5, PAC_PACE = 100};
enum CONDITION {DIED, WIN_FILE};
static const unsigned char FOOD = 249;
static const unsigned char WALL = 219;
static const unsigned char TUNNEL = ' ';
static const int LIVES = 3;
static const int VICTORY = 306;
static const int DEFAULT_MSG = 15;
static const int GHOSTS = 4;
static const int MAX_ROWS = 80;
static const int MAX_COLS = 80;
static const int SCORE = 0;
static const int JUNCTIONS = 35;
static const int MAX_ENTITIES = 7;
static const int MAX_HIGHSCORES = 5;
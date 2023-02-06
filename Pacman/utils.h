#pragma once

/*
global functions that arent a part of any class
*/
void gotoxy(int x, int y);
void clrscr();
void ShowConsoleCursor(bool showFlag);
bool isDigit(int num);
void cleanBuffer();
bool isANumber(std::string num);
bool isDigit(char dig);
int setMode(int argc, char* argv[]);
void printError();
std::string getName(int entity, int stageNum);
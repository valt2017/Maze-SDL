#pragma once

const char CURSOR = 'O';
const char CIEL = 'C';
const char STENA = '#';
const char VOLNA = ' ';
const char BOMBA = 'B';

class Maze
{
	enum Fiels {};
	char ** pIn;
	int SizeX;
	int SizeY;
	int CursorX;
	int CursorY;
	int ExitX;
	int ExitY;
	
public:
	static const int CELL_SIZE = 20;
	Maze();
	Maze(char * File);
	void ToString();
	int GetSizeX();
	int GetSizeY();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	char GetField(int X, int Y);
	bool Find(char Item, int & X, int & Y);
	bool ExitReached();
	virtual ~Maze();
};


#pragma once

class Maze
{
	char ** pIn;
	int SizeX;
	int SizeY;
	int CursorX;
	int CursorY;
	int ExitX;
	int ExitY;
	
public:
	static const char CURSOR = 'O';
	static const char CIEL = 'C';
	static const char STENA = '#';
	static const char VOLNA = ' ';
	static const char BOMBA = 'B';
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
	void PlaceBomb();
	void DetonateBombs();
	char GetField(int X, int Y);
	bool Find(char Item, int & X, int & Y);
	bool ExitReached();
	virtual ~Maze();
};


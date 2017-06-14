#include "Maze.h"

#include <iostream>
#include <fstream>

Maze::Maze()
{
	SizeX = 0;
	SizeY = 0;
	CursorX = 0;
	CursorY = 0;
	ExitX = 0;
	ExitY = 1;
	pIn = NULL;
}

Maze::Maze(char * File)
{
	int i = 0, iRozX = 0, iRozY = 0;
	std::ifstream pFin(File);

	if (!pFin) {
		std::cout << "Error opening file: " << File << std::endl;
		return;
	}
	pFin >> iRozX >> iRozY;
	while (pFin.get() != '\n')
		continue;
	SizeX = iRozX;
	SizeY = iRozY;
	pIn = new char*[iRozY * sizeof(char*)];
	if (pIn == NULL) {
		std::cout << "Error allocating matrix" << std::endl;
		pFin.close();
		return;
	}
	for (i = 0; i < iRozY; i++)
	{
		pIn[i] = new char[(iRozX + 2) * sizeof(char)]; // '\n'+ '\0'
		if (pIn[i] == NULL)	{
			std::cout << "Error allocating matrix" << std::endl;
			pFin.close();
		}
		pFin.getline(pIn[i], iRozX + 2); // '\n'+ '\0'
		pIn[i][iRozX] = '\0';
	}
	// Cursor position
	if (!Find(CURSOR, CursorX, CursorY)) {
		std::cout << "Start position not found." << std::endl;
		CursorX = 0;
		CursorY = 0;
	}
	// Exit position
	if (!Find(CIEL, ExitX, ExitY)) {
		std::cout << "Exit position not found." << std::endl;
		ExitX = 0;
		ExitY = 0;
	}
	pFin.close();
}

char Maze::GetField(int X, int Y)
{
	if (X < SizeX && Y < SizeY)
		return(pIn[Y][X]);
	return 0;
}

bool Maze::Find(char Item, int & X, int & Y) {
	for (int j = 0; j < SizeY; j++)
		for (int i = 0; i < SizeX; i++)
			if (pIn[j][i] == Item)	{
				X = i;
				Y = j;
				return true;
			}
	return false;
}

int Maze::GetSizeX() {
	return SizeX;
}

int Maze::GetSizeY() {
	return SizeY;
}

void Maze::MoveUp() {
	if (pIn[CursorY - 1][CursorX] != STENA) {
		if(pIn[CursorY][CursorX] != BOMBA)
			pIn[CursorY][CursorX] = VOLNA;
		pIn[--CursorY][CursorX] = CURSOR;
	}
}

void Maze::MoveDown() {
	if (pIn[CursorY + 1][CursorX] != STENA) {
		if (pIn[CursorY][CursorX] != BOMBA)
 		  pIn[CursorY][CursorX] = VOLNA;
		pIn[++CursorY][CursorX] = CURSOR;
	}
}

void Maze::MoveLeft() {
	if (pIn[CursorY][CursorX - 1] != STENA) {
		if (pIn[CursorY][CursorX] != BOMBA)
			pIn[CursorY][CursorX] = VOLNA;
		pIn[CursorY][--CursorX] = CURSOR;
	}
}

void Maze::MoveRight() {
	if (pIn[CursorY][CursorX + 1] != STENA) {
		if (pIn[CursorY][CursorX] != BOMBA)
			pIn[CursorY][CursorX] = VOLNA;
		pIn[CursorY][++CursorX] = CURSOR;
	}
}

void Maze::PlaceBomb(){
	pIn[CursorY][CursorX] = BOMBA;
}

void Maze::DetonateBombs() {
	for (int j = 0; j < SizeY; j++)
		for (int i = 0; i < SizeX; i++)
			if (pIn[j][i] == BOMBA) {
				pIn[j][i] = VOLNA;
				if (i > 1)  
					pIn[j][i-1] = VOLNA;
				if (j > 1)  
					pIn[j-1][i] = VOLNA;
				if (i < SizeX-2)  
					pIn[j][i+1] = VOLNA;
				if (j < SizeY-2)  
					pIn[j+1][i] = VOLNA;

			}
}

void Maze::ToString()
{
	for (int i = 0; i < SizeY; i++)
		std::cout << pIn[i] << std::endl;
}

bool Maze::ExitReached() {
	if (CursorY == ExitY && CursorX == ExitX)
		return true;
	return false;
};

Maze::~Maze()
{
	for (int i = 0; i < SizeY; i++)
		delete pIn[i];
	delete pIn;
}

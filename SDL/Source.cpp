
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <map>
#include "Maze.h"

int main(int argc, char ** argv) {
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	std::map<const char, SDL_Texture *> Textures;
	std::map<const char, std::string> Bitmaps;

	if (argc != 2)	{
		std::cout << "File with level not found.";
		exit(EXIT_FAILURE);
	}
	Maze Bludisko(argv[1]);
	Bludisko.ToString();
	int posX = 100, posY = 100, width = Bludisko.GetSizeX()*Maze::CELL_SIZE, height = Bludisko.GetSizeY()*Maze::CELL_SIZE;
	// Error checks
	std::cout << "SDL init start" << std::endl;
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow(argv[1], posX, posY, width, height, 0);
	if (win == NULL) {
		std::cout << "SDL_CreateWindow error"<<std::endl;
	}
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "SDL_CreateRenderer error" << std::endl;
	}
	// Load bitmaps
	Bitmaps[STENA] = "img/brick.bmp";
	Bitmaps[CURSOR] = "img/cursor.bmp";
	Bitmaps[CIEL] = "img/exit.bmp";
	Bitmaps[BOMBA] = "img/bomb.bmp";
	// Create textures from bitmaps
	for (auto bitmap : Bitmaps) {
		SDL_Surface * bitmapSurface = SDL_LoadBMP(bitmap.second.c_str());
		Textures[bitmap.first] = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
		if (Textures[bitmap.first] == NULL) {
			std::cout << bitmap.first <<" SDL_CreateTextureFromSurface error" << std::endl;
		}
		SDL_FreeSurface(bitmapSurface);
	}
    // One item of the maze
	SDL_Rect DestR;
	DestR.x = 0;
	DestR.y = 0;
	DestR.w = Maze::CELL_SIZE;
	DestR.h = Maze::CELL_SIZE;

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || Bludisko.ExitReached()) {
				break;
			}
			/* Look for a keypress */
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					Bludisko.MoveLeft();
					break;
				case SDLK_RIGHT:
					Bludisko.MoveRight();
					break;
				case SDLK_UP:
					Bludisko.MoveUp();
					break;
				case SDLK_DOWN:
					Bludisko.MoveDown();
					break;
				default:
					std::cout << "Key not supported" << std::endl;
					break;
				}
			}
		}
		// Render textures according maze items
		SDL_RenderClear(renderer);
		for (int j = 0; j < Bludisko.GetSizeY(); j++) {
			for (int i = 0; i < Bludisko.GetSizeX(); i++) {
				auto texture = Textures.find(Bludisko.GetField(i, j));
				if (texture != Textures.end()) {
					DestR.x = i*Maze::CELL_SIZE;
					DestR.y = j*Maze::CELL_SIZE;
					SDL_RenderCopy(renderer, texture->second, NULL, &DestR);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	for (auto texture : Textures) {
		SDL_DestroyTexture(texture.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
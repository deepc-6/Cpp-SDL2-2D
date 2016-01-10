#include "Main.h"

bool Main::onInit()
{
	//Initializing window and renderer
	SDL_Init(SDL_INIT_VIDEO);

	window = nullptr;
	renderTarget = nullptr;

	window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return true;
}